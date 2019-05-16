#pragma once
#include "Data_Control.hpp"


static std::vector<std::string> classes;
/*함수들*/
using namespace cv;     //opencv 관련 함수 사용
using namespace dnn;    //dnn함수 사용
using namespace std;    //cpp기본 함수 라이브러리 사용

/*함수간 종속관계 해소*/
static void postprocess(const vector<Mat>& outs, VisionDataset& dataset);
static void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);
static vector<String> getOutputsNames(const Net& net);


/*
void postprocess(VisionDataset dataset, const vector<Mat> &outs , Mat& detectimg)
{


	int index;

	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<Rect> boxes;




	for (size_t i = 0; i < outs.size(); ++i)
	{
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		float* data = (float*)outs[i].data;
		for (static int j = 0, index = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);


			if (confidence > confThreshold || index < 3)
			{
				int centerX = (int)(data[0] * detectimg.cols);
				int centerY = (int)(data[1] * detectimg.rows);
				int width = (int)(data[2] * detectimg.cols);
				int height = (int)(data[3] * detectimg.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, width, height));


			}
		}
	}

	// Perform non maximum suppression to eliminate redundant overlapping boxes with
	// lower confidences
	std::vector<int> indices;
	NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0, index = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];



		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, detectimg);
		//박스그리는 함수는 제거함. 이미지 원본 홰손 방지용

		dataset.Center_X[index] = (box.x + box.width*0.5);
		dataset.Center_Y[index] = (box.y + box.height*0.5);

		dataset.height[index] = (double)box.height;
		dataset.width[index] = (double)box.width;
		index++;   //겹치는 애들 처리한후에 그 데이터를 가져온다. 단 3개만 받아옴

		dataset.number_of_detection = index;

	}
	VisionDataset_KCFCORMaker(dataset); //kcf용 좌표계 변환 코드도 여기서 조정한다.
}

*/

void postprocess( const vector<Mat>& outs, VisionDataset& dataset)
{
	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		/*찾아낸 모든 박스들을 채크한다.*/
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > confThreshold)
			{
				int centerX = (int)(data[0] * (dataset.detectimg).cols);
				int centerY = (int)(data[1] * (dataset.detectimg).rows);
				int width = (int)(data[2] * (dataset.detectimg).cols);
				int height = (int)(data[3] * (dataset.detectimg).rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, width, height));
			}


		}
	}

	/* 겹치는 것들을 모두 확인한다. */
	vector<int> indices;
	NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];

		/*박스 그리는 함수. 나중에 제거해야한다. 원본 이미지를 더럽힌다.*/ 
		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, (dataset.display));

			

		dataset.Center_X[idx] = (box.x + box.width*0.5);
		dataset.Center_Y[idx] = (box.y + box.height*0.5);

		dataset.height[idx] = (double)box.height;
		dataset.width[idx] = (double)box.width;
		//겹치는 애들 처리한후에 그 데이터를 가져온다. 단 3개만 받아옴

		dataset.number_of_detection = idx + 1;

	}

	VisionDataset_KCFCORMaker(dataset); //kcf용 좌표계 변환 코드도 여기서 조정한다.
}

// Draw the predicted bounding box
void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
	//Draw a rectangle displaying the bounding box
	rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);

	//Get the label for the class name and its confidence
	string label = format("%.2f", conf);
	if (!classes.empty())
	{
		CV_Assert(classId < (int)classes.size());
		label = classes[classId] + ":" + label;
	}

	//Display the label at the top of the bounding box
	int baseLine;
	Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
	top = max(top, labelSize.height);
	rectangle(frame, Point(left, top - round(1.5*labelSize.height)), Point(left + round(1.5*labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
	putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
}

// Get the names of the output layers
vector<String> getOutputsNames(const Net& net)
{
	static vector<String> names;
	if (names.empty())
	{
		//Get the indices of the output layers, i.e. the layers with unconnected outputs
		vector<int> outLayers = net.getUnconnectedOutLayers();

		//get the names of all the layers in the network
		vector<String> layersNames = net.getLayerNames();

		// Get the names of the output layers in names
		names.resize(outLayers.size());
		for (size_t i = 0; i < outLayers.size(); ++i)
			names[i] = layersNames[outLayers[i] - 1];
	}
	return names;
}


/*

static void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
	//Draw a rectangle displaying the bounding box
	rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);

	//Get the label for the class name and its confidence
	string label = format("%.2f", conf);
	if (!classes.empty())
	{
		CV_Assert(classId < (int)classes.size());
		label = classes[classId] + ":" + label;
	}

	//Display the label at the top of the bounding box
	int baseLine;
	Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
	top = max(top, labelSize.height);
	rectangle(frame, Point(left, top - round(1.5*labelSize.height)), Point(left + round(1.5*labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
	putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
}


static std::vector<String> getOutputsNames(const Net& net)
{
	static std::vector<String> names;
	if (names.empty())
	{
		//Get the indices of the output layers, i.e. the layers with unconnected outputs
		std::vector<int> outLayers = net.getUnconnectedOutLayers();

		//get the names of all the layers in the network
		std::vector<String> layersNames = net.getLayerNames();

		// Get the names of the output layers in names
		names.resize(outLayers.size());
		for (size_t i = 0; i < outLayers.size(); ++i)
			names[i] = layersNames[outLayers[i] - 1];
	}
	return names;
}

*/