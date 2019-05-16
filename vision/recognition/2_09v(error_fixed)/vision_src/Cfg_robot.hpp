#pragma once
#include "SendData_Control.hpp"

/*assign armours for robots*/
static void armour_assign(std::vector<bbox_t> detect_Data, VisionDataset& dataset) {
	//two process are possible one is based on distance 
	//but we can use the labeled nember
	//before run this function we must do KCF traker
	//number of detection must be more than 1

	short index = 0;
	int number_of_armer = 0;
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
			if ((i.obj_id == Number1) || (i.obj_id == Number2) ) {

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


/*detecting enemy robot and configure number of robot*/
static bool configure_number_robot(VisionDataset data) {  
	// find max confidence data > and Lank them 
	short number_of_1 = 0;
	short numner_of_2 = 0;
	short index;
	short index2;
	double confidence_of_1 = 0;
	double confidence_of_2 = 0;
	double old_confidence_1 = 0;
	double old_confidence_2 = 0;

	bool number1_assigned = false;
	bool number2_assigned = false;


	short Center_X[3] = { 0,0,0 };  // this dataset can store maximun 3 robot
	short Center_Y[3] = { 0,0,0 };
	double height[3] = { 0,0,0 };
	double width[3] = { 0,0,0 };
	armour_data armour[3];
	
	bool restore_num[3] = {false, false, false};


	//store the temp data
	for (index = 0; index < 3; index++) {
		armour_initialize(armour[index]);
		Center_X[index] = data.Center_X[index];
		Center_Y[index] = data.Center_Y[index];
		height[index] = data.height[index];
		width[index] = data.width[index];
		armour[index] = data.armour[index];
	}
	// except number of armour initalize

	for (index = 1; index < 3; index++) {
		data.Center_X[index] = 0;
		data.Center_Y[index] = 0;
		data.height[index] = 0;
		data.width[index] = 0;
		for (index2 = 0; index2 < 6; index2++) {
			data.armour[index].armour_type[index2] = 0;
			data.armour[index].armour_confidence[index2] = 0;
			data.armour[index].Center_x[index2] = 0;
			data.armour[index].Center_y[index2] = 0;
			data.armour[index].width[index2] = 0;
			data.armour[index].height[index2] = 0;
			data.armour[index].distance[index2] = 0;
		}
	}


	for (index = 1; index < 3; index++) {
		if (data.armour[index].number_of_armer == 0) {
			data.armour[index].number_of_armer = 1;
			restore_num[index] = true;
		}
	}

	
	for (index = 1; index < 3; index++) {
		
		for (index2 = 0; index2 < 6; index2++) {
			if (data.armour[index].armour_type[i] == Number1) {
				number_of_1++;
				confidence_of_1 = confidence_of_1 + data.armour[index].armour_confidence[i];
			}
			if (data.armour[index].armour_type[i] == Number2) {
				number_of_2++;
				confidence_of_2 = confidence_of_2 + data.armour[index].armour_confidence[i];
			}
		}
		if (number_of_1 > number_of_2 && number1_assigned == false) {
		//if this condition this robot`s number is 1
		data.Center_X[1] = Center_X[index];
		data.Center_Y[1] = Center_Y[index];
		data.height[1] = height[index];
		data.width[1] = width[index];
		data.armour[1] = armour[index];
		number1_assigned = true;

		}
		else if (number_of_2 > number_of_1 && number2_assigned == false) {
		//if this condition this robot`s number is 2
		data.Center_X[2] = Center_X[index];
		data.Center_Y[2] = Center_Y[index];
		data.height[2] = height[index];
		data.width[2] = width[index];
		data.armour[2] = armour[index];
		number2_assigned = true;
		} 
		else if(number1_assigned == true) {  //second loop
			if ((old_confidence_1 / data.armour[index - 1].number_of_armer) > (confidence_of_1 / data.armour[index].number_of_armer)) {
				//old data have more confidence
				data.Center_X[2] = Center_X[index];
				data.Center_Y[2] = Center_Y[index];
				data.height[2] = height[index];
				data.width[2] = width[index];
				data.armour[2] = armour[index];
			}
			else if ((old_confidence_1 / data.armour[index - 1].number_of_armer) < (confidence_of_1 / data.armour[index].number_of_armer)) {
				data.Center_X[1] = Center_X[index];
				data.Center_Y[1] = Center_Y[index];
				data.height[1] = height[index];
				data.width[1] = width[index];
				data.armour[1] = armour[index];

				data.Center_X[2] = Center_X[index-1];
				data.Center_Y[2] = Center_Y[index-1];
				data.height[2] = height[index-1];
				data.width[2] = width[index-1];
				data.armour[2] = armour[index-1];
			}
		}
		else if (number2_assigned == true) {//second loop
			if ((old_confidence_2 / data.armour[index - 1].number_of_armer) > (confidence_of_2 / data.armour[index].number_of_armer)) {
				//old data have more confidence
				data.Center_X[1] = Center_X[index];
				data.Center_Y[1] = Center_Y[index];
				data.height[1] = height[index];
				data.width[1] = width[index];
				data.armour[1] = armour[index];
			}
			else if ((old_confidence_2 / data.armour[index - 1].number_of_armer) < (confidence_of_2 / data.armour[index].number_of_armer)) {
				data.Center_X[2] = Center_X[index];
				data.Center_Y[2] = Center_Y[index];
				data.height[2] = height[index];
				data.width[2] = width[index];
				data.armour[2] = armour[index];
				data.Center_X[1] = Center_X[index - 1];
				data.Center_Y[1] = Center_Y[index - 1];
				data.height[1] = height[index - 1];
				data.width[1] = width[index - 1];
				data.armour[1] = armour[index - 1];
			}
		}
		else if(confidence_of_1 / data.armour[index].number_of_armer > confidence_of_2 / data.armour[index].number_of_armer && number1_assigned == false){
			data.Center_X[1] = Center_X[index];
			data.Center_Y[1] = Center_Y[index];
			data.height[1] = height[index];
			data.width[1] = width[index];
			data.armour[1] = armour[index];
			number1_assigned = true;
		}
		else if (confidence_of_1 / data.armour[index].number_of_armer < confidence_of_2 / data.armour[index].number_of_armer && number2_assigned == false) {
			data.Center_X[2] = Center_X[index];
			data.Center_Y[2] = Center_Y[index];
			data.height[2] = height[index];
			data.width[2] = width[index];
			data.armour[2] = armour[index];
			number2_assigned = true;
		}
		else { //if number of 1 and 2 is same, and confidence is same >> 99.99% there are no data
			number1_assigned = true;
			number2_assigned = true;
		}
		number_of_1 = 0;
		number_of_2 = 0;
		old_confidence_1 = confidence_of_1;
		old_confidence_2 = confidence_of_2;
		}




	}
	
	for (index = 1; index < 3; index++) {
		if (restore_num[index] == true) {
			data.armour[index].number_of_armer = 0;
		}
	}



	return true;
}

