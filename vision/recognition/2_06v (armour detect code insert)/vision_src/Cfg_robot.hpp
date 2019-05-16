#pragma once
#include "SendData_Control.hpp"

/*assign armours for robots*/
static void armour_assign(std::vector<bbox_t> detect_Data, VisionDataset& dataset) {
	//two process are possible one is based on distance 
	//but we can use the labeled nember
	//before run this function we must do KCF traker
	//number of detection must be more than 1

	short index = 0;

	/*
	//define tempary data
	short Center_X[3] = { 0,0,0 };  
	short Center_Y[3] = { 0,0,0 };
	double height[3] = { 0,0,0 };
	double width[3] = { 0,0,0 };

	//assign data to tempary data

	for (index = 0; index < 3; index++) {
		Center_X[index] = dataset.Center_X[index];
		Center_Y[index] = dataset.Center_Y[index];
		height[index] = dataset.height[index];
		width[index] = dataset.width[index];
	}
	*/   // it is not needed, if number 1 and number 2 can`t configure clearly .
	

	for (auto &i : detect_Data) {
		//cv::Scalar color = obj_id_to_color(i.obj_id);
		//cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 2);  // doesn`t used
		if (i.prob > confThreshold) {
			if ((i.obj_id == Number1) or (i.obj_id == Number2) ) {

				for (index = 1; index < 3; index++) {   //first we check the detected robot data and check only ememy
					if (dataset.Center_X[index] > 0 && dataset.Center_Y[index] > 0) {  //if there are no data, check next data
						if (dataset.KCF_X[index] < (i.x + 0.5*(i.w)) && dataset.KCF_Y[index] < (i.y + 0.5*(i.h)) &&  (i.x + 0.5*(i.w)) < (dataset.KCF_X[index] + dataset.width[index]) && (i.y + 0.5*(i.h)) < ( dataset.KCF_X[index] + dataset.height[index]) ) {
							dataset.armour[index].Center_x[number_of_armer] = i.x + 0.5*(i.w);
							dataset.armour[index].Center_y[number_of_armer] = i.y + 0.5*(i.h);
							dataset.armour[index].width[number_of_armer] = i.w;
							dataset.armour[index].height[number_of_armer] = i.h;
							dataset.armour[index].armour_type[number_of_armer] = i.obj_id;        //next using this data,configure enemy`s Id
							dataset.armour[index].armour_confidence[number_of_armer] = i.prob;

							dataset.armour[index].number_of_armer++;
							
						}
					}	
				}	
			}

			/*  // configureation of number is not clear 
			else if (i.obj_id == Number2) {
				for (index = 1; index < 3; index++) {   //first we check the detected robot data and check only ememy
					if (dataset.Center_X[index] > 0 && dataset.Center_Y[index] > 0) {
						if (dataset.KCF_X[index] < i.x && dataset.KCF_Y[index] < i.y &&i.x < dataset.KCF_X[index] + dataset.width[index] && i.y < dataset.KCF_X[index] + dataset.height[index]) {
							//this is number 1 robot 


							assign_armour++;
						}
					}
					assign_armour = 0;
				}
			}
			*/
		}
	}

}


/*detecting enemy robot*/
static bool configure_number_robot(VisionDataset data) {  




	return true;
}

