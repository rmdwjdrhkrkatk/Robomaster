#pragma once
#include "pch.hpp"




struct VisionDataset {

	bool Detection;

	cv::Mat detectimg;  //opencv 컬러 행렬이미지 주소
	cv::Mat afterimg;
	cv::Mat display;

	int number_of_detection = 0;  //detect된 로봇의 숫자. 
	int how_old = 0;
	int Center_X[3] = { 0,0,0 };  //이 데이타 셋은 최대 3개까지 저장한다. [임의로 늘리면 그다지 현명할것같지 않음]
	int Center_Y[3] = { 0,0,0 };

	double height[3]= { 0,0,0 };
	double width[3] = { 0,0,0 };

	double KCF_X[3] = { 0,0,0 };
	double KCF_Y[3] = { 0,0,0 };
	
	double distance[3] = { 0,0,0 };

	double KCF_X_old[3] = { 0,0,0 };
	double KCF_Y_old[3] = { 0,0,0 };

	

};


/*함수 미리 선언문*/
static void VisionDataset_avoid_zero(VisionDataset& dataset, rs2::depth_frame depth_frame, int index);
static bool VisionDataset_avoid_fail_KCF(VisionDataset& dataset);



static void VisionDataset_initialize( VisionDataset& dataset ) {
	// 프레임상에서 디택트된 정보들을 제거한다. 

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

static bool VisionDataset_checker(int numberofdetection) {
	// 아무 것도 디택트 되지 않으면 참값을 반환한다. 

	if (numberofdetection <= 0)
	{
		return true;
	}

	return false;

}


/*
static bool VisionDataset_checker(VisionDataset& dataset) {
	// 아무 것도 디택트 되지 않으면 참값을 반환한다. 

	if (
		dataset.Center_X[0] <= 0 || dataset.Center_Y[0] <= 0 ||
		dataset.Center_X[1] <= 0 || dataset.Center_Y[1] <= 0 ||
		dataset.Center_X[2] <= 0 || dataset.Center_Y[2] <= 0
		)
	{
		return true;
	}

	return false;

}

*/

/*0을 참조하지 못하도록 설정해야한다.*/
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

static void VisionDataset_getDepth(VisionDataset& dataset, rs2::depth_frame depth_frame) {
	
	/*거리값 축출*/
	for (int index = 0; index < 3; index++) {
		if (dataset.Center_X[index] > 0 && dataset.Center_Y[index] > 0) {
			dataset.distance[index] = depth_frame.get_distance(dataset.Center_X[index], dataset.Center_Y[index]);
			VisionDataset_avoid_zero(dataset, depth_frame, index);
			// std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  //콘솔에 거리값 출력 나중에 빼도된다.
		}
	}

}

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


static void VisionDataset_continueTraking(VisionDataset& dataset) {
	/*최신 프레임을 기반으로 지속 트래킹을 하도록 한다.*/
	dataset.detectimg = dataset.afterimg;
	
}

static bool VisionDataset_avoid_fail_KCF(VisionDataset& dataset) {
	int index = 0;
	int oldindex[3] = { 0,0,0 };
	for (index = 0; index < dataset.number_of_detection; index++) {
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
		std::cout << "old뭐시기로 디택팅전환" << std::endl;
		return true;
	}
}

static void VisionDataset_KCF_old_control(VisionDataset& dataset) {
	int index = 0;
	for (index = 0; index < 3; index++) {
		dataset.KCF_X_old[index] = dataset.KCF_X[index];
		dataset.KCF_Y_old[index] = dataset.KCF_Y[index];
	}

}