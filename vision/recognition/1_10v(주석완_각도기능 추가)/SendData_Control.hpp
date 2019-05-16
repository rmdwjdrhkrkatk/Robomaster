#pragma once
#include "Data_Control.hpp"


//이코드는 사용하는 내용을 일일이 다 뜯은 코드이다. (보기조금 불편하나, 구조체에 관계없이 사용가능하다) 
/*픽셀값을 카메라기반 각도로 바꾸어주는 함수*/
/*
static void pixeltodata(short *X, short *Y, short width, short hight, short *angle_hori, short *angle_vert) {
	//realsense 제원 수평각 85.2 수직 58 대각 94도 오차 쁠마 3
	//RGB화각 수평각 69.4 수직각 42.5 대각 77 오차 쁠마3
	// RGB화각만 있으면된다. 
	// 60분법 * pi/180 = 라데안. 
	// 60분법 = 라데안*180/pi
	// 마이너스는 왼쪽 , 아래 
	// 플러스는 오른쪽 , 위를 각도로 잡는다. 
	// 각도 데이터는 short으로 4301 > 43.01도를 의미한다. 
	// 함수권장 사용 형식  pixeltodata(VisionDataset.Center_X[i] , VisionDataset.Center_Y[i] , yamiinfo.real_width , yamiinfo.real_height ,yamiinfo.angle_hori, yamiinfo.angle_verti)


	//초기값 
	short Width = 640*0.5;  //640
	short Height = 480*0.5; //480  카메라 픽셀 의 절반을 넣는다
	double a = 69.4;
	double hehe;
	double x;

	if (*X < (Width)) {
		hehe = (Width - *X)*tan(a) / Width;
		x = atan(hehe);
		*angle_hori = -1 * (x * 100);

	}
	else if(*X == Width){
		*angle_hori = 0;
	}
	else {
		hehe = (*X - Width)*tan(a) / Width;
		x = atan(hehe);
		*angle_hori = 1 * (x * 100);
	}

	if (*Y < (Height)) {
		hehe = (Height - *Y)*tan(a) / Height;
		x = atan(hehe);
		*angle_vert = 1 * (x * 100);

	}
	else if (*Y == (Height)) {
		*angle_vert = 0;
	}
	else {
		hehe = (*Y - Height)*tan(a) / Height;
		x = atan(hehe);
		*angle_vert = -1 * (x * 100);
	}
}
*/

//아래코드는 좀더 간편화 되어있다.
/*픽셀값을 카메라기반 각도로 바꾸어주는 함수*/
static void pixeltodata(short X , short Y , short w, short h , yamiinfo& send) {
//realsense 제원 수평각 85.2 수직 58 대각 94도 오차 쁠마 3
//RGB화각 수평각 69.4 수직각 42.5 대각 77 오차 쁠마3
// RGB화각만 있으면된다. 
// 60분법 * pi/180 = 라데안. 
// 60분법 = 라데안*180/pi
// 마이너스는 왼쪽 , 아래 
// 플러스는 오른쪽 , 위를 각도로 잡는다. 
// 각도 데이터는 short으로 4301 > 43.01도를 의미한다. 
// 함수권장 사용 형식  pixeltodata(VisionDataset& dataset(vision데이터) , yamiinfo& send(출력용 데이터))

	//초기값 
	short Width = 640 * 0.5;  //640
	short Height = 480 * 0.5; //480  카메라 픽셀 의 절반을 넣는다
	double a = 69.4;
	double hehe;
	double x;

	#pragma region 화각 만들기
	if (X < (Width)) {
		hehe = (Width - X)*tan(a) / Width;
		x = atan(hehe);
		send.angle_hori = -1 * (x * 100);

	}
	else if (X == Width) {
		send.angle_hori = 0;
	}
	else {
		hehe = (X - Width)*tan(a) / Width;
		x = atan(hehe);
		send.angle_hori = 1 * (x * 100);
	}

	if (Y < (Height)) {
		hehe = (Height - Y)*tan(a) / Height;
		x = atan(hehe);
		send.angle_verti = 1 * (x * 100);

	}
	else if (Y == (Height)) {
		send.angle_verti = 0;
	}
	else {
		hehe = (Y - Height)*tan(a) / Height;
		x = atan(hehe);
		send.angle_verti = -1 * (x * 100);
	}
	#pragma endregion 각도 만들어주는 함수

	#pragma region X,Y축 집어 넣기
	send.Pixel_X = X;
	send.Pixel_Y = Y;
	send.Pixel_width = w;
	send.Pixel_height = h;
	#pragma endregion yaminfo에 정보를 넣는다.

}


/* 픽셀 크기를 실제 크기로 변환시켜주는 함수  */
static void realsize_control( yamiinfo& send) {
// 사용목적: 화면상 크기와 관계없이 실제크기를 찾아내므로 잘못 디텍트된 것을 잡아줄 수 있다, 적의 타겟 범위를 좀더 구체화 가능하다. 
// 필수사용조건!!!!
// 꼭 이함수는 pixeltodata() 함수가 먼저 동작해야한다! 그리고 distance값을 꼭 먼저 넣어야한다!
	short width = 640 * 0.5;
	short height = 320 * 0.5;

	if (send.Pixel_X < (width)) {
		send.real_width = (send.distance) * sin(send.angle_verti) * (send.Pixel_width) / (width - (send.Pixel_X));
	}
	else if (send.Pixel_X > (width)) {
		send.real_width = (send.distance) * sin(send.angle_verti) * (send.Pixel_width) / ((send.Pixel_X) - width);
	}
	else {
		//이경우에는 바로 처리가 안되므로 다른 알고리즘을 고려해야한다. 크기가 고정형이므로, 거리에 비래할것이다. 이것을 직접 실험후에 비례식으로 집어 넣어야한다.
	}

	if (send.Pixel_Y < (height)) {
		send.real_height = (send.distance) * sin(send.angle_hori) * (send.Pixel_height) / (height - send.Pixel_Y);
	}
	else if (send.Pixel_Y > (height)) {
		send.real_height = (send.distance) * sin(send.angle_hori) * (send.Pixel_height) / (send.Pixel_Y - height);
	}
	else {
		//이경우에는 바로 처리가 안되므로 다른 알고리즘을 고려해야한다.
	}


}


/*보낼 데이터를 만들어준다.*/
static void sendData_Maker(VisionDataset& data , sendDataset& send) {
	
	send.number_of_detection = data.number_of_detection;

	switch (data.number_of_detection)
	{
	case 0:
		std::cout << "발견된 데이터가 없습니다.";
		break;
	case 1:
		send.data_1.infochecker = true;
		send.data_2.infochecker = false;
		send.data_3.infochecker = false;
		// pixeltodata(&data.Center_X[0], &data.Center_Y[0], &(send.data_1).angle_hori, &(send.data_1).angle_verti);
		pixeltodata(data.Center_X[0], data.Center_Y[0],data.width[0],data.height[0] ,send.data_1);
		send.data_1.distance = data.distance[0] * 1000;
		realsize_control(send.data_1);


	case 2:
		send.data_1.infochecker = true;
		send.data_2.infochecker = true;
		send.data_3.infochecker = false;
		// pixeltodata(&data.Center_X[0], &data.Center_Y[0], &(send.data_1).angle_hori, &(send.data_1).angle_verti);
		// pixeltodata(&data.Center_X[1], &data.Center_Y[1], &(send.data_2).angle_hori, &(send.data_2).angle_verti);
		pixeltodata(data.Center_X[0], data.Center_Y[0], data.width[0], data.height[0], send.data_1);
		pixeltodata(data.Center_X[1], data.Center_Y[1], data.width[1], data.height[1], send.data_2);
		send.data_1.distance = data.distance[0] * 1000;
		send.data_2.distance = data.distance[1] * 1000;
		realsize_control(send.data_1);
		realsize_control(send.data_2);


	case 3:
		send.data_1.infochecker = true;
		send.data_2.infochecker = true;
		send.data_3.infochecker = true;
		//pixeltodata(&data.Center_X[0], &data.Center_Y[0], &(send.data_1).angle_hori, &(send.data_1).angle_verti);
		//pixeltodata(&data.Center_X[1], &data.Center_Y[1], &(send.data_2).angle_hori, &(send.data_2).angle_verti);
		//pixeltodata(&data.Center_X[2], &data.Center_Y[2], &(send.data_3).angle_hori, &(send.data_3).angle_verti);
		pixeltodata(data.Center_X[0], data.Center_Y[0], data.width[0], data.height[0], send.data_1);
		pixeltodata(data.Center_X[1], data.Center_Y[1], data.width[1], data.height[1], send.data_2);
		pixeltodata(data.Center_X[2], data.Center_Y[2], data.width[2], data.height[2], send.data_3);
		send.data_1.distance = data.distance[0] * 1000;
		send.data_2.distance = data.distance[1] * 1000;
		send.data_3.distance = data.distance[2] * 1000;
		realsize_control(send.data_1);
		realsize_control(send.data_2);
		realsize_control(send.data_3);

	default:
		break;
	}
	

}


/*
픽셀의 높이 너비 컨트롤 보내기 값
		send.data_1.Pixel_height = data.height[0];
		send.data_1.Pixel_width = data.width[0];
		send.data_2.Pixel_height = data.height[1];
		send.data_2.Pixel_width = data.width[1];
		send.data_3.Pixel_height = data.height[2];
		send.data_3.Pixel_width = data.width[2];
*/