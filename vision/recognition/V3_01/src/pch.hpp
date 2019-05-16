//v3.01
#pragma once 
#ifndef PCH_HPP
#define PCH_HPP

#define OPENCV // using for yolo_class.hpp


//cpp basic header file
//#include <filesystem>  //for c++17
//#include <experimental/filesystem>  //for c++14

#include <sys/stat.h>
#include <unistd.h>

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
#include <condition_variable>


#include "yolo_class.hpp" //need to include it 
//#include "/home/nvidia/robomaster_extra/darknet/include/yolo_v2_class.hpp"

#ifdef VIRTUAL
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#endif



//deeplearning and opencv basic header file (opencv version 3.4.5)
#include <opencv2/opencv.hpp>
#include <opencv2/core/version.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#ifdef MAKEING_IMG
#include <opencv2/videoio/videoio.hpp>
#endif //!MAKEING_IMG

#ifndef VIRTUAL
#include <opencv2/tracking.hpp>  //need to install opencv_contrib 
#include <opencv2/core/ocl.hpp>
#endif

//realsense header file
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>

//basic structure management 

/*robot info*/
struct Sendinfo {  //gimbal.Pixel_X

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

// send_.sendingo[2].Pixel_X

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
const unsigned int dead_id = 2;
const unsigned int Number1 = 3; 
const unsigned int Number2 = 4; 
const unsigned int wheel = 5;
const unsigned int hp_bar = 6;
// for labeling blue = 0 / red = 1/ dead = 2 


#endif
