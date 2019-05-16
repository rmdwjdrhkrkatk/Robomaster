#pragma once
#include "Data_Control.hpp"


static std::vector<std::string> classes;
/*namespaces*/
using namespace cv;     //opencv function 
using namespace dnn;    //dnn function
using namespace std;    //cpp basic function

/*release function`s dependancy*/
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
		

		dataset.Center_X[index] = (box.x + box.width*0.5);
		dataset.Center_Y[index] = (box.y + box.height*0.5);

		dataset.height[index] = (double)box.height;
		dataset.width[index] = (double)box.width;
		index++;   

		dataset.number_of_detection = index;

	}
	VisionDataset_KCFCORMaker(dataset); 
}

*/  //old version (this version`s Vison dataset does not contain img info

/* delete overraped detection .It is based on "pch.hpp"`s  nmsThreshold value */
void postprocess( const vector<Mat>& outs, VisionDataset& dataset)
{
	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		/*check all data of detection*/
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

	/* configure overraped objects */
	vector<int> indices;
	NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];

		/* draw rectangure it must be deleted later because it damage image*/
#ifdef DISPLAY
		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, (dataset.display));
#endif
			

		dataset.Center_X[idx] = (box.x + box.width*0.5);
		dataset.Center_Y[idx] = (box.y + box.height*0.5);

		dataset.height[idx] = (double)box.height;
		dataset.width[idx] = (double)box.width;
		// after deldete overraped objects, get robot`s info (it can hanle max 3 robot at the same time)

		dataset.number_of_detection = idx + 1;

	}

	VisionDataset_KCFCORMaker(dataset); // corrdinate of KCF and Yolo is different so this function control it.
}

/*Draw ractinagure funtion*/
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

/* assign name for objects*/
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