#pragma once
#include "Data_Control.hpp"
#include "pch.hpp"


// this code is configure all data for values , quite hard to read but use regard less of sturcture
/* control pixel data and real angle*/
/*
static void pixeltodata(short *X, short *Y, short width, short hight, short *angle_hori, short *angle_vert) {
	//realsense data (Dapth) hori angle 65.2 verti angle 58 diagonal 94 error +-3
	//RGB viewing angle horiangle 69.4 veri angle 42.5 diagonal 77 erroe +-3
	// but we need only RGB angle 
	// 60degree * pi/180 = radian. 
	// 60degree = radian*180/pi
	// minus is left and bottom 
	// plus is right and top 
	// if data type is short is 4301 means 43.01 degree  
	// refference useing format  pixeltodata(VisionDataset.Center_X[i] , VisionDataset.Center_Y[i] , yamiinfo.real_width , yamiinfo.real_height ,yamiinfo.angle_hori, yamiinfo.angle_verti)


	//defalt value
	short Width = 640*0.5;  //640
	short Height = 480*0.5; //480 input half of piexl data
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

//this code is much slmplified.
/* control pixel data and real angle*/
static int pixeltodata(short X , short Y , short w, short h , Sendinfo& send) {
	//realsense data (Dapth) hori angle 65.2 verti angle 58 diagonal 94 error +-3
	//RGB viewing angle horiangle 69.4 veri angle 42.5 diagonal 77 erroe +-3
	// but we need only RGB angle 
	// 60degree * pi/180 = radian. 
	// 60degree = radian*180/pi
	// minus is left and bottom 
	// plus is right and top 
	// if data type is short is 4301 means 43.01 degree  
	// reference funtion useing format pixeltodata(VisionDataset& dataset, yamiinfo& send)

	//initial value
	if (X == 0 or Y == 0 or w == 0 or h == 0 ){

		return 0;
	}

	short Width = 640 * 0.5;  //640
	short Height = 480 * 0.5; //480  input half of piexl data
	double a = 69.4;
	double hehe;
	double x;

///////////////////////////////making Vision angle//////////////
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
///////////////////////////////////////////////////

////////////////////input X,Y,w,h data to send info/////////
	send.Pixel_X = X;
	send.Pixel_Y = Y;
	send.Pixel_width = w;
	send.Pixel_height = h;
///////////////////////////////////////////////////////////////////////
	return 1;
}


/* pixel size and real size matching funtion */
static int realsize_control( Sendinfo& send) {
// mission objects: regardless of pixel size, we can configure wrong data, and specifiy enemys target area
// requirement!!!!
// this function must be use after opperation for pixeltodata(), and yamiinfo data must have distance value
	if(send.Pixel_X == 0 or send.Pixel_Y == 0){
		return 0;
	}

	short width = 640 * 0.5;
	short height = 320 * 0.5;

	if (send.Pixel_X < (width)) {
		send.real_width = (send.distance) * sin(send.angle_verti) * (send.Pixel_width) / (width - (send.Pixel_X));
	}
	else if (send.Pixel_X > (width)) {
		send.real_width = (send.distance) * sin(send.angle_verti) * (send.Pixel_width) / ((send.Pixel_X) - width);
	}
	else {
		//we have to think another algo to do this (i think about using ratio)
	}

	if (send.Pixel_Y < (height)) {
		send.real_height = (send.distance) * sin(send.angle_hori) * (send.Pixel_height) / (height - send.Pixel_Y);
	}
	else if (send.Pixel_Y > (height)) {
		send.real_height = (send.distance) * sin(send.angle_hori) * (send.Pixel_height) / (send.Pixel_Y - height);
	}
	else {
		//we have to think another algo to do this (i think about using ratio)
	}

return 1;
}


/*making data for send*/
static void sendData_Maker(VisionDataset& data , sendDataset& send) {
	int i = 0;
	send.number_of_detection = data.number_of_detection;
#ifdef CUDA_YOLO   //this code for cuda detection

	for (i=0 ; i < 3 ; i++){
		send.sendinfo[i].infochecker = pixeltodata(data.Center_X[i], data.Center_Y[i],data.width[i],data.height[i] ,send.sendinfo[i]);
		send.sendinfo[i].distance = data.distance[i] ;
		realsize_control(send.sendinfo[i]);

		}
		/*
	send.sendinfo[0].infochecker = pixeltodata(data.Center_X[0], data.Center_Y[0],data.width[0],data.height[0] ,send.sendinfo[0]);
	send.sendinfo[1].infochecker = pixeltodata(data.Center_X[1], data.Center_Y[1], data.width[1], data.height[1], send.sendinfo[1));
	send.sendinfo[2].infochecker = pixeltodata(data.Center_X[2], data.Center_Y[2], data.width[2], data.height[2], send.sendinfo[2]);
	send.sendinfo[0].distance = data.distance[0] ;
	send.sendinfo[1].distance = data.distance[1] ;
	send.sendinfo[2].distance = data.distance[2] ;
	realsize_control(send.sendinfo[0]);
	realsize_control(send.sendinfo[1]);
	realsize_control(send.sendinfo[2]);
		 */
#ifdef DEBUG
	std::cout << "(sendData_Maker) _is worked " << std::endl;
#endif

#else
	switch (data.number_of_detection)
	{
	case 0:
		std::cout << "Vision: nodata founed"<< std::endl;
		break;
	case 1:
		send.data_0.infochecker = true;
		send.data_1.infochecker = false;
		send.data_2.infochecker = false;
		// pixeltodata(&data.Center_X[0], &data.Center_Y[0], &(send.data_1).angle_hori, &(send.data_1).angle_verti);
		pixeltodata(data.Center_X[0], data.Center_Y[0],data.width[0],data.height[0] ,send.sendinfo[0]);
		send.sendinfo[0].distance = data.distance[0] ;
		realsize_control(send.sendinfo[0]);


		case 2:
		send.data_0.infochecker = true;
		send.data_1.infochecker = true;
		send.data_2.infochecker = false;
		// pixeltodata(&data.Center_X[0], &data.Center_Y[0], &(send.data_1).angle_hori, &(send.data_1).angle_verti);
		// pixeltodata(&data.Center_X[1], &data.Center_Y[1], &(send.data_2).angle_hori, &(send.data_2).angle_verti);
		pixeltodata(data.Center_X[0], data.Center_Y[0],data.width[0],data.height[0] ,send.sendinfo[0]);
		pixeltodata(data.Center_X[1], data.Center_Y[1], data.width[1], data.height[1], send.sendinfo[1);
		send.sendinfo[0].distance = data.distance[0] ;
		send.sendinfo[1].distance = data.distance[1] ;
		realsize_control(send.sendinfo[0]);
		realsize_control(send.sendinfo[1]);



	case 3:
		send.data_0.infochecker = true;
		send.data_1.infochecker = true;
		send.data_2.infochecker = true;
		//pixeltodata(&data.Center_X[0], &data.Center_Y[0], &(send.data_1).angle_hori, &(send.data_1).angle_verti);
		//pixeltodata(&data.Center_X[1], &data.Center_Y[1], &(send.data_2).angle_hori, &(send.data_2).angle_verti);
		//pixeltodata(&data.Center_X[2], &data.Center_Y[2], &(send.data_3).angle_hori, &(send.data_3).angle_verti);
		pixeltodata(data.Center_X[0], data.Center_Y[0],data.width[0],data.height[0] ,send.sendinfo[0]);
		pixeltodata(data.Center_X[1], data.Center_Y[1], data.width[1], data.height[1], send.sendinfo[1);
		pixeltodata(data.Center_X[2], data.Center_Y[2], data.width[2], data.height[2], send.sendinfo[2]);
		send.sendinfo[0].distance = data.distance[0] ;
		send.sendinfo[1].distance = data.distance[1] ;
		send.sendinfo[2].distance = data.distance[2] ;
		realsize_control(send.sendinfo[0]);
		realsize_control(send.sendinfo[1]);
		realsize_control(send.sendinfo[2]);

	default:
		break;
	}

#endif
	

}
/*select target robot, if possible get data from ros main control*/
static void select_target_robot_vision(VisionDataset& data, int& target) {
	if (data.distance[1] > data.distance[2]) {
		target = 1;
	}
	else if (data.distance[1] < data.distance[2]) {
		target = 2;
	}
}




/*configure bast target */
static void armourdata_selector(VisionDataset& data , Sendinfo& gimbal, rs2::depth_frame depth_frame, int target) {
	//target must be 1 or 2
	int index = 0;
	int reference = 0;
	int count = 0;

	/*find Largest box */
	for (index = 0; index < data.armour[target].number_of_armer; index++) {
		if(reference < data.armour[target].width[index] * data.armour[target].height[index] ){
			reference = data.armour[target].width[index] * data.armour[target].height[index];
			count = index;
		}
	}
	gimbal.infochecker = pixeltodata(data.armour[target].Center_x[count], data.armour[target].Center_y[count],
											data.armour[target].width[count], data.armour[target].height[count], gimbal);
	gimbal.distance = depth_frame.get_distance(data.armour[target].Center_x[count], data.armour[target].Center_y[count]);
	realsize_control(gimbal);
	gimbal.assinged_number = target;


#ifdef DEBUG
	std::cout << "(armourdata_selector)_is worked"<<"// selected target:" << target << " X_center data:"<< "data.armour[target].Center_x[count]"<<endl;
#endif

}

