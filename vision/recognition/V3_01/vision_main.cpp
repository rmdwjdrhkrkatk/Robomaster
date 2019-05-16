// Vision_3.01v 
// Kwak Donghwan


//////////////////////////preprocesser define////////////////////////////
#define BASIC_FUNCTION  //this is for basic function (using ROS)
#define DISPLAY  // control opencv_ imshow function 
//#define DEBUG  //show what function start and worked

#ifdef BASIC_FUNCTION
//#define VIRTUAL  // for mechine learning code with object detection  (must run with BASIC_FUNCTION)
#endif

//#define VISION_DATACHECK //show visoin output data such as number of detection
#define ZIMBAL_DATACHECK //show zimbal`s output data such as angle
 
#ifndef BASIC_FUNTION
#define MAKEING_IMG //this fucntion is making a img

#ifdef MAKEING_IMG 
//#define ADD_DEEPLEARNING  //makeing image while using object detection
#endif

#endif

#include "src/all.hpp"

int main(int argc, char **argv) {
	
	ros::init(argc, argv, "vision_node");
	ros::NodeHandle nh;  //ros node init

	std::string  names_file = "/home/nvidia/CLionProjects/vision_dev/yolo/yolo3.names";
	std::string  cfg_file = "/home/nvidia/CLionProjects/vision_dev/yolo/yolov3.cfg";
	std::string  weights_file = "/home/nvidia/CLionProjects/vision_dev/yolo/yolov3-tiny.backup";

	darknet::Detector detector_yolo(cfg_file, weights_file); //yolo detector
	
	data_control CT_data; //define basic data class
	vision_camera camera(nh); //camera class initialize
	vision_detector detector(detector_yolo); //object detector class setup
	
	while (true) {

		camera.vision_camera_run(CT_data);  //get camera_color_image
		detector.vision_detector_run(camera, CT_data, detector_yolo);  //run object detector and assign output data
		camera.making_img(CT_data); //this is for makeing img for labeling, and if #MAKEING_IMG is not define than, nothing happen

	}

}
