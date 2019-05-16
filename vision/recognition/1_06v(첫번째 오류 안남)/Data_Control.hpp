#pragma once
#include "pch.hpp"

struct VisionDataset {

	cv::Mat detectimg;  //opencv 컬러 행렬이미지 주소
	cv::Mat afterimg;

	int number_of_detection = 0;  //detect된 로봇의 숫자. 
	
	int Center_X[3] = { 0,0,0 };  //이 데이타 셋은 최대 3개까지 저장한다. [임의로 늘리면 그다지 현명할것같지 않음]
	int Center_Y[3] = { 0,0,0 };

	double height[3]= { 0,0,0 };
	double width[3] = { 0,0,0 };

	double KCF_X[3] = { 0,0,0 };
	double KCF_Y[3] = { 0,0,0 };
	
	double distance[3] = { 0,0,0 };

	



};

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
		if (!dataset.Center_X[index] == 0 || !dataset.Center_Y[index] == 0) {
			dataset.KCF_X[index] = (dataset.Center_X[index]) - ((dataset.width[index]) * 0.5);
			dataset.KCF_Y[index] = (dataset.Center_Y[index]) - ((dataset.height[index]) * 0.5);
		}
	}
}

static void VisionDataset_getDepth(VisionDataset& dataset, rs2::depth_frame depth_frame) {
	
	/*거리값 축출*/
	for (int index = 0; index < 3; index++) {
		if (dataset.Center_X[index] > 0 || dataset.Center_Y[index] > 0) {
			dataset.distance[index] = depth_frame.get_distance(dataset.Center_X[index], dataset.Center_Y[index]);
			std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  //콘솔에 거리값 출력 나중에 빼도된다.
		}
	}



}

static void VisionDataset_continueTraking(VisionDataset& dataset) {
	/*최신 프레임을 기반으로 지속 트래킹을 하도록 한다.*/
	dataset.detectimg = dataset.afterimg;
	
}