#pragma once
#include "Data_Control.hpp"


//���ڵ�� ����ϴ� ������ ������ �� ���� �ڵ��̴�. (�������� �����ϳ�, ����ü�� ������� ��밡���ϴ�) 
/*�ȼ����� ī�޶��� ������ �ٲپ��ִ� �Լ�*/
/*
static void pixeltodata(short *X, short *Y, short width, short hight, short *angle_hori, short *angle_vert) {
	//realsense ���� ���� 85.2 ���� 58 �밢 94�� ���� �ܸ� 3
	//RGBȭ�� ���� 69.4 ������ 42.5 �밢 77 ���� �ܸ�3
	// RGBȭ���� ������ȴ�. 
	// 60�й� * pi/180 = �󵥾�. 
	// 60�й� = �󵥾�*180/pi
	// ���̳ʽ��� ���� , �Ʒ� 
	// �÷����� ������ , ���� ������ ��´�. 
	// ���� �����ʹ� short���� 4301 > 43.01���� �ǹ��Ѵ�. 
	// �Լ����� ��� ����  pixeltodata(VisionDataset.Center_X[i] , VisionDataset.Center_Y[i] , yamiinfo.real_width , yamiinfo.real_height ,yamiinfo.angle_hori, yamiinfo.angle_verti)


	//�ʱⰪ 
	short Width = 640*0.5;  //640
	short Height = 480*0.5; //480  ī�޶� �ȼ� �� ������ �ִ´�
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

//�Ʒ��ڵ�� ���� ����ȭ �Ǿ��ִ�.
/*�ȼ����� ī�޶��� ������ �ٲپ��ִ� �Լ�*/
static void pixeltodata(short X , short Y , short w, short h , yamiinfo& send) {
//realsense ���� ���� 85.2 ���� 58 �밢 94�� ���� �ܸ� 3
//RGBȭ�� ���� 69.4 ������ 42.5 �밢 77 ���� �ܸ�3
// RGBȭ���� ������ȴ�. 
// 60�й� * pi/180 = �󵥾�. 
// 60�й� = �󵥾�*180/pi
// ���̳ʽ��� ���� , �Ʒ� 
// �÷����� ������ , ���� ������ ��´�. 
// ���� �����ʹ� short���� 4301 > 43.01���� �ǹ��Ѵ�. 
// �Լ����� ��� ����  pixeltodata(VisionDataset& dataset(vision������) , yamiinfo& send(��¿� ������))

	//�ʱⰪ 
	short Width = 640 * 0.5;  //640
	short Height = 480 * 0.5; //480  ī�޶� �ȼ� �� ������ �ִ´�
	double a = 69.4;
	double hehe;
	double x;

	#pragma region ȭ�� �����
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
	#pragma endregion ���� ������ִ� �Լ�

	#pragma region X,Y�� ���� �ֱ�
	send.Pixel_X = X;
	send.Pixel_Y = Y;
	send.Pixel_width = w;
	send.Pixel_height = h;
	#pragma endregion yaminfo�� ������ �ִ´�.

}


/* �ȼ� ũ�⸦ ���� ũ��� ��ȯ�����ִ� �Լ�  */
static void realsize_control( yamiinfo& send) {
// ������: ȭ��� ũ��� ������� ����ũ�⸦ ã�Ƴ��Ƿ� �߸� ����Ʈ�� ���� ����� �� �ִ�, ���� Ÿ�� ������ ���� ��üȭ �����ϴ�. 
// �ʼ��������!!!!
// �� ���Լ��� pixeltodata() �Լ��� ���� �����ؾ��Ѵ�! �׸��� distance���� �� ���� �־���Ѵ�!
	short width = 640 * 0.5;
	short height = 320 * 0.5;

	if (send.Pixel_X < (width)) {
		send.real_width = (send.distance) * sin(send.angle_verti) * (send.Pixel_width) / (width - (send.Pixel_X));
	}
	else if (send.Pixel_X > (width)) {
		send.real_width = (send.distance) * sin(send.angle_verti) * (send.Pixel_width) / ((send.Pixel_X) - width);
	}
	else {
		//�̰�쿡�� �ٷ� ó���� �ȵǹǷ� �ٸ� �˰������� �����ؾ��Ѵ�. ũ�Ⱑ �������̹Ƿ�, �Ÿ��� ���Ұ��̴�. �̰��� ���� �����Ŀ� ��ʽ����� ���� �־���Ѵ�.
	}

	if (send.Pixel_Y < (height)) {
		send.real_height = (send.distance) * sin(send.angle_hori) * (send.Pixel_height) / (height - send.Pixel_Y);
	}
	else if (send.Pixel_Y > (height)) {
		send.real_height = (send.distance) * sin(send.angle_hori) * (send.Pixel_height) / (send.Pixel_Y - height);
	}
	else {
		//�̰�쿡�� �ٷ� ó���� �ȵǹǷ� �ٸ� �˰������� �����ؾ��Ѵ�.
	}


}


/*���� �����͸� ������ش�.*/
static void sendData_Maker(VisionDataset& data , sendDataset& send) {
	
	send.number_of_detection = data.number_of_detection;

	switch (data.number_of_detection)
	{
	case 0:
		std::cout << "�߰ߵ� �����Ͱ� �����ϴ�.";
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
�ȼ��� ���� �ʺ� ��Ʈ�� ������ ��
		send.data_1.Pixel_height = data.height[0];
		send.data_1.Pixel_width = data.width[0];
		send.data_2.Pixel_height = data.height[1];
		send.data_2.Pixel_width = data.width[1];
		send.data_3.Pixel_height = data.height[2];
		send.data_3.Pixel_width = data.width[2];
*/