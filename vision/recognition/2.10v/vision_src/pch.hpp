// lib integrated header File

#ifndef PCH_HPP
#define PCH_HPP


/* header management */


//darknet.h heder file
#include "/home/nvidia/robomaster_extra/darknet/include/yolo_v2_class.hpp"


//cpp basic header file
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
#include <thread>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <cstring>     // using for KCF tracker
#include <exception>
#include <math.h> // for calculate detection anlge control


//deeplearning and opencv basic header file (opencv version 3.4.5)
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

//KCFtraking header file
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>  //need to install opencv_contrib 
#include <opencv2/core/ocl.hpp>


//realsense header file
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>

/* structure management*/

/*armer info*/
struct armour_data {
	// if you learning, you should do max labeling obliqued label
	short number_of_armer = 0;
	short armour_type[6] = {0, 0, 0, 0, 0, 0};
	double armour_confidence[6] = {0, 0, 0, 0, 0, 0};
	short Center_x[6] = {0, 0, 0, 0, 0, 0};
	short Center_y[6] = {0, 0, 0, 0, 0, 0};
	short width[6] = {0, 0, 0, 0, 0, 0};
	short height[6] = {0, 0, 0, 0, 0, 0};
	double distance[6] = {0, 0, 0, 0, 0, 0};

};


//the most used struct for this program (it contain w,h and center data, img, distance)
struct VisionDataset {

	bool Detection;

	cv::Mat detectimg;  //opencv color img 
	cv::Mat afterimg;
#ifdef DISPLAY
	cv::Mat display;
#endif
	short number_of_detection = 0;  
	short how_old = 0;
	short Center_X[3] = { 0,0,0 };  // this dataset can store maximun 3 robot
	short Center_Y[3] = { 0,0,0 };

	double height[3] = { 0,0,0 };
	double width[3] = { 0,0,0 };

	double KCF_X[3] = { 0,0,0 };
	double KCF_Y[3] = { 0,0,0 };

	double distance[3] = { 0,0,0 };

	double KCF_X_old[3] = { 0,0,0 };  
	double KCF_Y_old[3] = { 0,0,0 };

	short trakcer_data[3] = {4,4,4};
	armour_data armour[3];

};

/*robot info*/
struct Sendinfo {

	bool infochecker = false;
	short angle_hori = 0;   // based on center line left is minus, righet is pluse
	short angle_verti = 0;   // based on center line upper is plus lower is minus  
	short Pixel_X = 0;  //center_X
	short Pixel_Y = 0;  //center_Y
	short Pixel_width = 0;     //pixel coordinate`s width 
	short Pixel_height = 0;    //pixel coordinate`s height
	short real_width = 0;  // real width
	short real_height = 0; // real height
	float distance = 0;  //it is based on meter 
	short assinged_number = 0;

};



/*dataset for send to ROS*/
struct sendDataset {

	short number_of_detection = 0;
	Sendinfo sendinfo[3];

};

/* static value managemnet*/
const float PI = 3.141592;

const float confThreshold = 0.3; // Confidence threshold
const float nmsThreshold = 0.4;  // Non-maximum suppression threshold
const int inpWidth = 416;  // Width of network's input image
const int inpHeight = 416; // Height of network's input image


/*currently 0:blue 1:red */
const unsigned int enemy_id = 0;   //enemy ID     0 is blue //  1 is red
const unsigned int alliance_id = 1; 
const unsigned int Number1 = 2;  //not deep learned
const unsigned int Number2 = 3;  //need to ckeck out

#endif