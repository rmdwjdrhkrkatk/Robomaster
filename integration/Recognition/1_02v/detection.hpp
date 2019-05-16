// 첫번째 코드
#pragma once
#include "pch.hpp"


static std::vector<std::string> classes;
/*함수들*/
using namespace cv;     //opencv 관련 함수 사용
using namespace dnn;    //dnn함수 사용
using namespace std;    //cpp기본 함수 라이브러리 사용

/*함수간 종속관계 해소*/
static void postprocess(Mat &frame, const vector<Mat> &outs, int X[], int Y[], double height_ext[], double width_ext[]);
static void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);
static vector<String> getOutputsNames(const Net& net);



void postprocess(Mat &frame, const vector<Mat> &outs,int X[],int Y[] , double height_ext[], double width_ext[] )
{
	/*지역변수*/

	float confThreshold = 0.7; // detect 지정 값
	float nmsThreshold = 0.4;  // non-maxima 지정값  1일경우, 하나의 물체를 여러개로 인식, 0.1일경우 겹쳐있는 물체 인식불가
	int inpWidth = 416;   //network 이미지 너비 입력값
	int inpHeight = 416;  //network 이미지 높이 입력값
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
		for (static int j = 0, index = 0 ; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > confThreshold || index < 3 )
			{
				int centerX = (int)(data[0] * frame.cols);
				int centerY = (int)(data[1] * frame.rows);
				int width = (int)(data[2] * frame.cols);
				int height = (int)(data[3] * frame.rows);
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
	for (size_t i = 0, index = 0 ; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];


		/*
		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, frame);
			*/ //박스그리는 함수는 제거함. 이미지 원본 홰손 방지용

		X[index] = (box.x + box.width*0.5);
		Y[index] = (box.y + box.height*0.5 );

		height_ext[index] = (double)box.height;
		width_ext[index] = (double)box.width;
		index++;   //곂치는 애들 처리한후에 그 데이터를 가져온다. 단 3개만 받아옴

	}
}

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

std::vector<String> getOutputsNames(const Net& net)
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