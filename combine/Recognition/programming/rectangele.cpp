// he342.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <string.h>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;






int main(int argc, char * argv[]) try
{
	// Declare depth colorizer for pretty visualization of depth data
	rs2::colorizer color_map;

	// Declare RealSense pipeline, encapsulating the actual device and sensors
	rs2::pipeline pipe;
	// Start streaming with default recommended configuration
	pipe.start();

	
	int num = 0;
	const auto window_name = "Display Image";
	namedWindow(window_name, WINDOW_AUTOSIZE);
	vector<vector<Point> > squares;
	while (waitKey(1) < 0 && cvGetWindowHandle(window_name))
	{
		rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
		rs2::frame depth = data.get_depth_frame().apply_filter(color_map);
		rs2::frame color = data.get_color_frame();


		// Query frame size (width and height)
		const int w = depth.as<rs2::video_frame>().get_width();
		const int h = depth.as<rs2::video_frame>().get_height();

		const int wc = color.as<rs2::video_frame>().get_width();
		const int hc = color.as<rs2::video_frame>().get_height();

		// Create OpenCV matrix of size (w,h) from the colorized depth data
		Mat depthp(Size(w, h), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);
		Mat colorp(Size(wc, hc), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
		/*
		Mat gray;
		Mat depth_gray;
		cv::cvtColor(colorp, gray, cv::COLOR_RGB2GRAY);
		cv::cvtColor(depthp, depth_gray , cv::COLOR_RGB2GRAY);
		Mat mask;
		cv::threshold(gray, mask, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		int biggestContourIdx = -1;
		float biggestContourArea = 0;

		cv::Mat drawing = cv::Mat::zeros(mask.size(), CV_8UC3);
		
			for (int i = 0; i < contours.size(); i++)
			{
				cv::Scalar color = cv::Scalar(0, 100, 0);
				drawContours(drawing, contours, i, color, 1, 8, hierarchy, 0, cv::Point());

				float ctArea = cv::contourArea(contours[i]);
				if (ctArea > biggestContourArea)
				{
					biggestContourArea = ctArea;
					biggestContourIdx = i;
				}
			}
		
		cv::RotatedRect boundingBox = cv::minAreaRect(contours[biggestContourIdx]);
		cv::Point2f corners[4];
		boundingBox.points(corners);
		/*
		cv::line(drawing, corners[0], corners[1], cv::Scalar(255, 255, 255));
		cv::line(drawing, corners[1], corners[2], cv::Scalar(255, 255, 255));
		cv::line(drawing, corners[2], corners[3], cv::Scalar(255, 255, 255));
		cv::line(drawing, corners[3], corners[0], cv::Scalar(255, 255, 255));

		cv::line(colorp, corners[0], corners[1], cv::Scalar(255, 255, 255));
		cv::line(colorp, corners[1], corners[2], cv::Scalar(255, 255, 255));
		cv::line(colorp, corners[2], corners[3], cv::Scalar(255, 255, 255));
		cv::line(colorp, corners[3], corners[0], cv::Scalar(255, 255, 255));

		cout << corners[0].x << "/" << corners[1].x << "/" << corners[2].x << "/" << corners[3].x << endl;
		*/
		/*
		float min_x =640 ;
		for (int i = 0; i < 4; i++) {
			if (min_x > corners[i].x)
			{
				min_x = corners[i].x;
			}
		}
		float max_x =0;
		for (int i = 0; i < 4; i++) {
			if (max_x < corners[i].x)
			{
				max_x = corners[i].x;
			}
		}
		float min_y = 640;
		for (int i = 0; i < 4; i++) {
			if (min_y > corners[i].y)
			{
				min_y = corners[i].y;
			}
		}
		float max_y = 0;
		for (int i = 0; i < 4; i++) {
			if (max_y < corners[i].y)
			{
				max_y = corners[i].y;
			}
		}
		cout << min_x << "/" << max_x << "/" << min_y << "/" << max_y << endl;
		*/
		
		/*

		try
		{
			int x = min_x;
			int y = min_y;
			int w = (max_x - min_x);
			int h = (max_y - min_y);
			cv::Mat ROI(colorp, Rect(x-50,y-50,w+100,h+100));
			cv::Mat cropped;
			ROI.copyTo(cropped);
			imshow("powerful2", cropped);
			std:ostringstream name;
			name << "teehan_" << num << ".png";
			num= num+1;
			cv::imwrite(name.str(), cropped);


		}
		catch (const std::exception&)
		{
			cout << "notdetcted" << endl;
		}

		*/
		cvtColor(colorp, colorp, COLOR_BGR2RGB);
		std:ostringstream name;
		name << "teehan_" << num << ".jpg";
		num = num + 1;
		cv::imwrite(name.str(), colorp);


		//imshow(window_name, drawing);
		imshow("powerful", colorp);
		
	}

	return EXIT_SUCCESS;
}
catch (const rs2::error & e)
{
	std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
}



