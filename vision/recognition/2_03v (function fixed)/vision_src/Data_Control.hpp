#pragma once
#include "pch.hpp"




/*dealing about function`s dependancy*/
static void VisionDataset_avoid_zero(VisionDataset& dataset, rs2::depth_frame depth_frame, int index);
static bool VisionDataset_avoid_fail_KCF(VisionDataset& dataset);

/*vision dataset initialize funtion*/
static void VisionDataset_initialize(VisionDataset& dataset) {
	//delete detection information from frame 

	dataset.number_of_detection = 0;

	for (int index = 0; index < 3; index++) {

		dataset.Center_X[index] = 0;
		dataset.Center_Y[index] = 0;
		dataset.height[index] = 0;
		dataset.width[index] = 0;
		dataset.KCF_X[index] = 0;
		dataset.KCF_Y[index] = 0;
		dataset.distance[index] = 0;



	}
}
/* yamiinfo dataset initialize*/
static void yamiinfo_initialize(yamiinfo& data){
	data.infochecker = false;
	data.angle_hori = 0;
	data.angle_verti = 0;
	data.distance = 0;
	data.enemy = 0;
	data.Pixel_width = 0;
	data.Pixel_height = 0;
	data.Pixel_X = 0;
	data.Pixel_Y = 0;
}   // real opperating funtion. 

/* send Dataset intitalize */
static void sendDataset_initialize(sendDataset& dataset) {
	dataset.number_of_detection = 0;
	yamiinfo_initialize(dataset.data_1);
	yamiinfo_initialize(dataset.data_2);
	yamiinfo_initialize(dataset.data_3);

}



/*if detecting is falied, for next loop detect again */
static bool VisionDataset_checker(int numberofdetection) {
	// if there are no detection return true

	if (numberofdetection <= 0)
	{
		return true;
	}

	return false;

}


/*
static bool VisionDataset_checker(VisionDataset& dataset) {
	// if there are no detection retun true

	if (
		dataset.Center_X[0] <= 0 && dataset.Center_Y[0] <= 0 &&
		dataset.Center_X[1] <= 0 && dataset.Center_Y[1] <= 0 &&
		dataset.Center_X[2] <= 0 && dataset.Center_Y[2] <= 0
		)
	{
		return true;
	}

	return false;

}

*/


/*The coordination of KCF and YOLO is different, match it */
static void VisionDataset_KCFCORMaker(VisionDataset& dataset)
{
	static int index;
	for (index = 0; index < 3; index++) {
		if (!dataset.Center_X[index] == 0 && !dataset.Center_Y[index] == 0) {
			dataset.KCF_X[index] = (dataset.Center_X[index]) - ((dataset.width[index]) * 0.5);
			dataset.KCF_Y[index] = (dataset.Center_Y[index]) - ((dataset.height[index]) * 0.5);
		}
	}
}

/*get distance funtion*/
static void VisionDataset_getDepth(VisionDataset& dataset, rs2::depth_frame depth_frame) {
	
	/*�Ÿ��� ����*/
	for (int index = 0; index < 3; index++) {
		if (dataset.Center_X[index] > 0 && dataset.Center_Y[index] > 0) {
			dataset.distance[index] = depth_frame.get_distance(dataset.Center_X[index], dataset.Center_Y[index]);
			VisionDataset_avoid_zero(dataset, depth_frame, index);
			// std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  // we don`t need it reight now.
		}
	}

}

/*if distance data get zero value(it beacues headware limitance) check next pixel`s distance*/
static void VisionDataset_avoid_zero(VisionDataset& dataset, rs2::depth_frame depth_frame, int index) {
	int average[5];
	int truenumber = 0;
	if (dataset.distance[index] <= 0) {
		average[0] = depth_frame.get_distance((dataset.Center_X[index] + 1), dataset.Center_Y[index]);
		average[1] = depth_frame.get_distance(dataset.Center_X[index],( dataset.Center_Y[index] + 1));
		average[2] = depth_frame.get_distance((dataset.Center_X[index] - 1), dataset.Center_Y[index]);
		average[3] = depth_frame.get_distance(dataset.Center_X[index], (dataset.Center_Y[index] - 1));

		for (int i = 0; i < 4; i++)
			if (average[i] != 0) {
				truenumber += 1;
				average[4] += average[i];
			}

		if (truenumber > 0) {
			average[4] = average[4] / truenumber;
		}
		else {
			average[4] = 0;
			dataset.number_of_detection = 0;
		}

		dataset.distance[index] = average[4];

	}

}

/*for KCF tracking new img become next base of tracking img*/
static void VisionDataset_continueTraking(VisionDataset& dataset) {
	dataset.detectimg = dataset.afterimg; 
	// copy new img to old img 
	
}

/*if output is same more then 5 time detect again*/
static bool VisionDataset_avoid_fail_KCF(VisionDataset& dataset) {
	int index = 0;
	int oldindex[3] = { 0,0,0 };
	for (index = 0; index < 3; index++) {


		if (dataset.KCF_X[index] == dataset.KCF_X_old[index] && dataset.KCF_X[index] > 0 && dataset.KCF_X_old[index] > 0 &&
			dataset.KCF_Y[index] == dataset.KCF_Y_old[index] && dataset.KCF_Y[index] > 0 && dataset.KCF_Y_old[index] > 0) {
		
			oldindex[index] = 1;
			
		}
	}

	if ((oldindex[0] + oldindex[1] + oldindex[2]) == dataset.number_of_detection) {
		dataset.how_old = dataset.how_old +1;
	}

	if (dataset.how_old > 5) {
		dataset.Detection = true;
		dataset.how_old = 0;
		std::cout << "Vision: data is un acceptable (configure how old)" << std::endl;
		return true;
	}
}

/* the funtion " VisionDataset_avoid_fail_KCF" , store old X and Y coordination*/
static void VisionDataset_KCF_old_control(VisionDataset& dataset) {
	int index = 0;
	for (index = 0; index < 3; index++) {
		dataset.KCF_X_old[index] = dataset.KCF_X[index];
		dataset.KCF_Y_old[index] = dataset.KCF_Y[index];
	}

}