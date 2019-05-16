#pragma once
#include "pch.hpp"




/*dealing about function`s dependancy*/
static float VisionDataset_avoid_zero(short x, short y, rs2::depth_frame depth_frame);
static bool VisionDataset_avoid_fail_KCF(VisionDataset& dataset);
static void armour_initialize(armour_data& armour);

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

		for (int i = 0; i < 3; i++) {
			armour_initialize(dataset.armour[index]);
		}
	}
#ifdef DEBUG
	std::cout << "(VisionDataset_initialize)_is worked" << std::endl;
#endif

}
static void armour_initialize(armour_data& armour) {
	armour.number_of_armer = 0;
	int index = 0;
	for (index = 0; index < 6; index++) {
		armour.armour_type[index] = 0;
		armour.armour_confidence[index] = 0;
		armour.Center_x[index] = 0;
		armour.Center_y[index] = 0;
		armour.width[index] = 0;
		armour.height[index] = 0;
		armour.distance[index] = 0;
	}
}


/* yamiinfo dataset initialize*/
static void yamiinfo_initialize(Sendinfo& data){
	data.infochecker = false;
	data.angle_hori = 0;
	data.angle_verti = 0;
	data.distance = 0;
	data.Pixel_width = 0;
	data.Pixel_height = 0;
	data.Pixel_X = 0;
	data.Pixel_Y = 0;
}   // real opperating funtion. 

/* send Dataset intitalize */
static void sendDataset_initialize(sendDataset& dataset) {
	dataset.number_of_detection = 0;
	yamiinfo_initialize(dataset.sendinfo[0]);
	yamiinfo_initialize(dataset.sendinfo[1]);
	yamiinfo_initialize(dataset.sendinfo[2]);

#ifdef DEBUG
	std::cout << "(sendDataset_initialize)_is worked" << std::endl;
#endif

}



/*if detecting is falied, for next loop detect again */
static bool VisionDataset_checker(int numberofdetection) {
	// if there are no detection return true

	if (numberofdetection <= 0)
	{
#ifdef DEBUG
		std::cout << "(VisionDataset_checker)_numberofdetection is zero" << std::endl;
#endif
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

	int index;
	for (index = 0; index < 3; index++) {
		if (dataset.Center_X[index] > 0 && dataset.Center_Y[index] > 0) {
			dataset.KCF_X[index] = (dataset.Center_X[index]) - ((dataset.width[index]) * 0.5);
			dataset.KCF_Y[index] = (dataset.Center_Y[index]) - ((dataset.height[index]) * 0.5);
		}
	}
#ifdef DEBUG
	std::cout << "(VisionDataset_KCFCORMaker)" << "dataset.Center_X[0]:" <<dataset.Center_X[0]<< " dataset.Center_X[1]:"  <<dataset.Center_X[index]<<" dataset.Center_X[2]:"  <<dataset.Center_X[2] <<std::endl;
	std::cout << "(VisionDataset_KCFCORMaker)" << " dataset.KCF_X[0]:" <<dataset.KCF_X[0]<< " dataset.KCF_X[1]:"  <<dataset.KCF_X[1]<<" dataset.KCF_X[2]:"  <<dataset.KCF_X[2] <<std::endl;
#endif
}




/*custom simplest align control*/
static float linial_align(short RGB_X, short RGB_Y,  rs2::depth_frame depth_frame) {
	// based on 3m > 6 pixel moved and it is for 640*480
	short fake_depth_x = (RGB_X * 0.63125 + 112);
	
	short real_depth_y = (RGB_Y * 0.63125 + 88.5);
	float fake_distance = VisionDataset_avoid_zero(fake_depth_x, real_depth_y , depth_frame);
	float distance = 0;


	if (fake_distance > 0){
	short move_pixel = ( 17.72 / fake_distance);
	short real_depth_x = (RGB_X * 0.63125 + 118 - move_pixel);
	distance = VisionDataset_avoid_zero(real_depth_x, real_depth_y, depth_frame);
	}
	
#ifdef DEBUG
	if (distance = 0) {
		std::cout << "(linial_align)_fail to get distance / distance = 0" << std::endl;
	}
#endif
	return distance;
}



/*get distance funtion*/
static void VisionDataset_getDepth(VisionDataset& dataset, rs2::depth_frame depth_frame) {
	
	/*get depth data*/


	for (int index = 0; index < 3; index++) {
		if (dataset.Center_X[index] > 0 && dataset.Center_Y[index] > 0) {
			dataset.distance[index] = linial_align(dataset.Center_X[index], dataset.Center_Y[index] , depth_frame);

			// std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  // we don`t need it reight now.
		}
	}

}

/*if distance data get zero value(it beacues headware limitance) check next pixel`s distance*/
static float VisionDataset_avoid_zero( short x, short y , rs2::depth_frame depth_frame) {
	//to use this function, x andy must be larger then 3 and smaler than Max-3
	float Depth = 0;
	float tem_Depth = 0;
	short i = 0;
	short j = 0;
	short count = 0;


	for (i=x; i < x+3; i++){

		for (j = y; j < y+3; j++) {
			tem_Depth = depth_frame.get_distance((i - 1), (j - 1));

			if (tem_Depth > 0) {
				count++;
				Depth = Depth + tem_Depth;
			}
		}
	}

	if (count > 0) {

		Depth = Depth / count;
		return Depth;

	}
	else {
#ifdef DEBUG
		std::cout << "(VisionDataset_avoid_zero) distance is zero" << std::endl;
#endif

		return 0;
	}

}

/*for KCF tracking new img become next base of tracking img*/
static void VisionDataset_continueTraking(VisionDataset& dataset) {
	dataset.detectimg = dataset.afterimg; 
	// copy new img to old img 
#ifdef DEBUG
	std::cout << "(VisionDataset_continueTraking) is worked" << std::endl;
#endif
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
#ifdef DEBUG
		std::cout << "(VisionDataset_avoid_fail_KCF) _Detection became true_ because of 'how_old' " << std::endl;
#endif
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
#ifdef DEBUG
	std::cout << "(VisionDataset_KCF_old_control) _is worked " << std::endl;
#endif
}
