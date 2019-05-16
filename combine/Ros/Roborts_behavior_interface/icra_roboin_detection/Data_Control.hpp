#pragma once
#include "pch.hpp"



/*카메라 비젼의 근간이 되는 구조체*/
struct VisionDataset {

	bool Detection;

	cv::Mat detectimg;  //opencv 컬러 행렬이미지 주소
	cv::Mat afterimg;
	cv::Mat display;

	short number_of_detection = 0;  //detect된 로봇의 숫자. 
	short how_old = 0;
	short Center_X[3] = { 0,0,0 };  //이 데이타 셋은 최대 3개까지 저장한다. [임의로 늘리면 그다지 현명할것같지 않음]
	short Center_Y[3] = { 0,0,0 };

	double height[3]= { 0,0,0 };
	double width[3] = { 0,0,0 };

	double KCF_X[3] = { 0,0,0 };
	double KCF_Y[3] = { 0,0,0 };
	
	double distance[3] = { 0,0,0 };

	double KCF_X_old[3] = { 0,0,0 };
	double KCF_Y_old[3] = { 0,0,0 };


};

/*보내기용 로봇 1개당 세부 정보 구조체*/
struct yamiinfo {

	bool infochecker = false;
	short enemy = true;
	short angle_hori = 0;   // 중앙선 기준으로 왼쪽 마이너스 오른쪽 쁠러스
	short angle_verti= 0;   // 중안선 기준으로 위쪽 플러스 아래쪽 마이너스 
	short Pixel_X = 0;
	short Pixel_Y = 0;
	short Pixel_width = 0;     //픽셀 좌표계상 너비  이걸 타겟 1과 2를 잡아줘야 할수도??
	short Pixel_height = 0;    //픽셀 좌표계상 높이
	short real_width = 0;  // 실제 너비
	short real_height = 0; // 실제 높이
	short distance = 0;  //이건 미리미터 단위로 넘어간다. 

};


/*보내기용 데이타셋*/
struct sendDataset {

	short number_of_detection = 0;
	yamiinfo data_1;
	yamiinfo data_2;
	yamiinfo data_3;

};

/*비젼구조체 초기화 함수*/
static void VisionDataset_initialize(VisionDataset& dataset) {
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
/* yamiinfo함수 초기화*/
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
}   // 실제 내부 구동용 함수. 

/*보내기용 데이타셋 초기화*/
static void sensDataset_initialize(sendDataset& dataset) {
	dataset.number_of_detection = 0;
	yamiinfo_initialize(dataset.data_1);
	yamiinfo_initialize(dataset.data_2);
	yamiinfo_initialize(dataset.data_3);

}


/*함수 미리 선언문*/
static void VisionDataset_avoid_zero(VisionDataset& dataset, rs2::depth_frame depth_frame, int index);
static bool VisionDataset_avoid_fail_KCF(VisionDataset& dataset);

/*디텍팅 실패시 다음루프시 디택팅 유지하는 함수*/
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


/*KCF와 YOLO의 기준좌표가 다르기 떄문에 변환을 시켜준다. */
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

/*거리값 축출 함수*/
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

/*기계의 한계로 인해서 거리값이 0이 축출 되었을 때 이를 근처 픽셀값을 이용하여 회피하는 함수*/
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

/*KCF트래킹에서 이전 프레임을 기반으로 다름 루프때 트래킹을 하도록 해주는 함수*/
static void VisionDataset_continueTraking(VisionDataset& dataset) {
	dataset.detectimg = dataset.afterimg; 
	// 새로운 이미지를 오래된 이미지에 덮어 씌운다.
	
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