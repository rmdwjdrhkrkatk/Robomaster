#pragma once
#include "pch.hpp"

struct VisionDataset {

	cv::Mat detectimg;  //opencv �÷� ����̹��� �ּ�
	cv::Mat afterimg;

	int number_of_detection = 0;  //detect�� �κ��� ����. 
	
	int Center_X[3] = { 0,0,0 };  //�� ����Ÿ ���� �ִ� 3������ �����Ѵ�. [���Ƿ� �ø��� �״��� �����ҰͰ��� ����]
	int Center_Y[3] = { 0,0,0 };

	double height[3]= { 0,0,0 };
	double width[3] = { 0,0,0 };

	double KCF_X[3] = { 0,0,0 };
	double KCF_Y[3] = { 0,0,0 };
	
	double distance[3] = { 0,0,0 };

	



};

static void VisionDataset_initialize( VisionDataset& dataset ) {
	// �����ӻ󿡼� ����Ʈ�� �������� �����Ѵ�. 

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
	// �ƹ� �͵� ����Ʈ ���� ������ ������ ��ȯ�Ѵ�. 

	if (numberofdetection <= 0)
	{
		return true;
	}

	return false;

}


/*
static bool VisionDataset_checker(VisionDataset& dataset) {
	// �ƹ� �͵� ����Ʈ ���� ������ ������ ��ȯ�Ѵ�. 

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

/*0�� �������� ���ϵ��� �����ؾ��Ѵ�.*/
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
	
	/*�Ÿ��� ����*/
	for (int index = 0; index < 3; index++) {
		if (dataset.Center_X[index] > 0 || dataset.Center_Y[index] > 0) {
			dataset.distance[index] = depth_frame.get_distance(dataset.Center_X[index], dataset.Center_Y[index]);
			std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  //�ֿܼ� �Ÿ��� ��� ���߿� �����ȴ�.
		}
	}



}

static void VisionDataset_continueTraking(VisionDataset& dataset) {
	/*�ֽ� �������� ������� ���� Ʈ��ŷ�� �ϵ��� �Ѵ�.*/
	dataset.detectimg = dataset.afterimg;
	
}