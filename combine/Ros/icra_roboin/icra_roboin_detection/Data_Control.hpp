#pragma once
#include "pch.hpp"



/*ī�޶� ������ �ٰ��� �Ǵ� ����ü*/
struct VisionDataset {

	bool Detection;

	cv::Mat detectimg;  //opencv �÷� ����̹��� �ּ�
	cv::Mat afterimg;
	cv::Mat display;

	short number_of_detection = 0;  //detect�� �κ��� ����. 
	short how_old = 0;
	short Center_X[3] = { 0,0,0 };  //�� ����Ÿ ���� �ִ� 3������ �����Ѵ�. [���Ƿ� �ø��� �״��� �����ҰͰ��� ����]
	short Center_Y[3] = { 0,0,0 };

	double height[3]= { 0,0,0 };
	double width[3] = { 0,0,0 };

	double KCF_X[3] = { 0,0,0 };
	double KCF_Y[3] = { 0,0,0 };
	
	double distance[3] = { 0,0,0 };

	double KCF_X_old[3] = { 0,0,0 };
	double KCF_Y_old[3] = { 0,0,0 };


};

/*������� �κ� 1���� ���� ���� ����ü*/
struct yamiinfo {

	bool infochecker = false;
	short enemy = true;
	short angle_hori = 0;   // �߾Ӽ� �������� ���� ���̳ʽ� ������ �ܷ���
	short angle_verti= 0;   // �߾ȼ� �������� ���� �÷��� �Ʒ��� ���̳ʽ� 
	short Pixel_X = 0;
	short Pixel_Y = 0;
	short Pixel_width = 0;     //�ȼ� ��ǥ��� �ʺ�  �̰� Ÿ�� 1�� 2�� ������ �Ҽ���??
	short Pixel_height = 0;    //�ȼ� ��ǥ��� ����
	short real_width = 0;  // ���� �ʺ�
	short real_height = 0; // ���� ����
	short distance = 0;  //�̰� �̸����� ������ �Ѿ��. 

};


/*������� ����Ÿ��*/
struct sendDataset {

	short number_of_detection = 0;
	yamiinfo data_1;
	yamiinfo data_2;
	yamiinfo data_3;

};

/*��������ü �ʱ�ȭ �Լ�*/
static void VisionDataset_initialize(VisionDataset& dataset) {
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
/* yamiinfo�Լ� �ʱ�ȭ*/
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
}   // ���� ���� ������ �Լ�. 

/*������� ����Ÿ�� �ʱ�ȭ*/
static void sensDataset_initialize(sendDataset& dataset) {
	dataset.number_of_detection = 0;
	yamiinfo_initialize(dataset.data_1);
	yamiinfo_initialize(dataset.data_2);
	yamiinfo_initialize(dataset.data_3);

}


/*�Լ� �̸� ����*/
static void VisionDataset_avoid_zero(VisionDataset& dataset, rs2::depth_frame depth_frame, int index);
static bool VisionDataset_avoid_fail_KCF(VisionDataset& dataset);

/*������ ���н� ���������� ������ �����ϴ� �Լ�*/
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


/*KCF�� YOLO�� ������ǥ�� �ٸ��� ������ ��ȯ�� �����ش�. */
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

/*�Ÿ��� ���� �Լ�*/
static void VisionDataset_getDepth(VisionDataset& dataset, rs2::depth_frame depth_frame) {
	
	/*�Ÿ��� ����*/
	for (int index = 0; index < 3; index++) {
		if (dataset.Center_X[index] > 0 && dataset.Center_Y[index] > 0) {
			dataset.distance[index] = depth_frame.get_distance(dataset.Center_X[index], dataset.Center_Y[index]);
			VisionDataset_avoid_zero(dataset, depth_frame, index);
			// std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  //�ֿܼ� �Ÿ��� ��� ���߿� �����ȴ�.
		}
	}

}

/*����� �Ѱ�� ���ؼ� �Ÿ����� 0�� ���� �Ǿ��� �� �̸� ��ó �ȼ����� �̿��Ͽ� ȸ���ϴ� �Լ�*/
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

/*KCFƮ��ŷ���� ���� �������� ������� �ٸ� ������ Ʈ��ŷ�� �ϵ��� ���ִ� �Լ�*/
static void VisionDataset_continueTraking(VisionDataset& dataset) {
	dataset.detectimg = dataset.afterimg; 
	// ���ο� �̹����� ������ �̹����� ���� �����.
	
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
		std::cout << "old���ñ�� ��������ȯ" << std::endl;
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