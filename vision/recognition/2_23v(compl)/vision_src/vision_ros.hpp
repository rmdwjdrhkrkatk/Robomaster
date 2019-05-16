
#ifdef ROS
#include "icra_roboin_msgs/PitchGain.h"
#include "icra_roboin_msgs/YawGain.h"
#include "icra_roboin_msgs/YoloDetectionInfo.h"
#include "roborts_msgs/GimbalAngle.h"
#include "roborts_msgs/ShootCmd.h"
#include "roborts_msgs/FricWhl.h"
#include "ros/ros.h"
#include "SendData_Control.hpp"
#include "pch.hpp"
#include <cstdio>

float YAW_P_GAIN = 0.0007;
float YAW_I_GAIN = 0.00008;
float YAW_D_GAIN = 0.0006;

float PITCH_P_GAIN = 0.0002;
float PITCH_I_GAIN = 0.001;
float PITCH_D_GAIN = 0.001;

#define X_CENTER_PIXEL 320
#define Y_CENTER_PIXEL 240


short yaw_prev_error = 0;
short pitch_prev_error = 0;
float yaw_i_error = 0;
float pitch_i_error = 0;
roborts_msgs::GimbalAngle gimbal_angle;

ros::ServiceClient cmd_shoot_client;
bool go = true;
short y_offset = 40;



void setFricWhl(ros::ServiceClient cmd_fric_whl_client_) {

    roborts_msgs::FricWhl fric_whl;
    fric_whl.request.open = true;
    if (cmd_fric_whl_client_.call(fric_whl)) {
        ROS_INFO("fric wheel Call Success");
        if(fric_whl.response.received){
            ROS_INFO("fric wheel running");
        } else {
            ROS_WARN("fric wheel call Not Received");
        }
    } else {
        ROS_ERROR("fric wheel Call Fail");
    }
}

void cmdShoot(int shoot) { // 1: shoot, 0: stop
    if(go) {
        roborts_msgs::ShootCmd shoot_cmd;
        shoot_cmd.request.mode = shoot;
        shoot_cmd.request.number = shoot;

        if (cmd_shoot_client.call(shoot_cmd)) {
            ROS_INFO("shoot Call Success");
            if(shoot_cmd.response.received == true){
                ROS_INFO("shoot call Received");
            } else {
                ROS_WARN("shoot call Not Received");
            }
        } else {
            ROS_ERROR("shoot Call Fail");
        }
    } else {

    }

}



bool SetYawGainCallback(icra_roboin_msgs::YawGain::Request &req,
	icra_roboin_msgs::YawGain::Response &resp) {
	if (req.p != 0.0) YAW_P_GAIN = req.p;
	if (req.i != 0.0) YAW_I_GAIN = req.i;
	if (req.d != 0.0) YAW_D_GAIN = req.d;
	printf("yaw pid: %f %f %f\n", YAW_P_GAIN, YAW_I_GAIN, YAW_D_GAIN);
	yaw_prev_error = 0;
	pitch_prev_error = 0;
	yaw_i_error = 0;
	pitch_i_error = 0;

	resp.received = true;
	return true;
}

bool SetPitchGainCallback(icra_roboin_msgs::PitchGain::Request &req,
	icra_roboin_msgs::PitchGain::Response &resp) {

	if (req.p != 0.0) PITCH_P_GAIN = req.p;
	if (req.i != 0.0) PITCH_I_GAIN = req.i;
	if (req.d != 0.0) PITCH_D_GAIN = req.d;
	printf("pitch pid: %f %f %f\n", PITCH_P_GAIN, PITCH_I_GAIN, PITCH_D_GAIN);
	yaw_prev_error = 0;
	pitch_prev_error = 0;
	yaw_i_error = 0;
	pitch_i_error = 0;

	resp.received = true;
	return true;
}


void rosPixelControl(int number_of_detection, Sendinfo& gimbal, ros::Publisher cmd_gimbal_angle_pub_) {
	printf("pixel control ready\n");

	if (gimbal.infochecker == true) {
		printf("pixel control start\n");
		Sendinfo target = gimbal;

		ROS_ERROR("armor pixel: %d, %d\n", target.Pixel_X, target.Pixel_Y);
		short pixel_error_x = target.Pixel_X - X_CENTER_PIXEL;
		short pixel_error_y = target.Pixel_Y - Y_CENTER_PIXEL + 12;

		if(pixel_error_x < 10 && pixel_error_x > -10 && pixel_error_y < 10 && pixel_error_y > -10){
		    printf("shoot!!!!\n");
		  cmdShoot(1);
		} else {
		  cmdShoot(0);
		  		    printf("no shoot!!!!\n");
		}

		// std::cout <<"target: " <<target.assinged_number<<std::endl;

		yaw_i_error += pixel_error_x;
		pitch_i_error += pixel_error_y ;

		// pid
		float angle_cmd = -pixel_error_x * YAW_P_GAIN - yaw_i_error * YAW_I_GAIN + (yaw_prev_error - pixel_error_x) * YAW_D_GAIN;
		gimbal_angle.yaw_angle = angle_cmd;

		printf("error: %d d_error: %d cmd_angle: %f\n", pixel_error_x, yaw_prev_error - pixel_error_x, angle_cmd);
		//    gimbal_angle.pitch_angle = pixel_error_y * PITCH_P_GAIN + pitch_i_error * PITCH_I_GAIN + (pitch_prev_error- pixel_error_y) * PITCH_D_GAIN;
		if (angle_cmd > 3) angle_cmd = 3;
		else if (angle_cmd < -3) angle_cmd = -3;
		gimbal_angle.yaw_angle = angle_cmd;


		//    gimbal_angle.yaw_angle = -pixel_error_x * YAW_P_GAIN;
		gimbal_angle.pitch_angle = pixel_error_y * PITCH_P_GAIN;

		gimbal_angle.yaw_mode = true;
		gimbal_angle.pitch_mode = true;

		cmd_gimbal_angle_pub_.publish(gimbal_angle);

		yaw_prev_error = pixel_error_x;
		pitch_prev_error = pixel_error_y;



	}
	else {
		printf("lost detection. reset prev_error\n");
		cmdShoot(0);
		yaw_i_error = 0;
		pitch_i_error = 0;

		yaw_prev_error = 0;
		pitch_prev_error = 0;
	}
}


void pubEnemyInfo(sendDataset& send_, ros::Publisher enemy_info_pub_) {

	icra_roboin_msgs::YoloDetectionInfo ros_msg;

	ros_msg.stamp = ros::Time();
	ros_msg.number_of_detection = send_.number_of_detection;

	int index = 0;
	for (index = 0; index < 3; index++) {
		ros_msg.enemy_detected[index] = send_.sendinfo[index].infochecker;
		ros_msg.angle_hori[index] = send_.sendinfo[index].angle_hori;
		ros_msg.angle_verti[index] = send_.sendinfo[index].angle_verti;
		ros_msg.Pixel_X[index] = send_.sendinfo[index].Pixel_X;
		ros_msg.Pixel_Y[index] = send_.sendinfo[index].Pixel_Y;
		ros_msg.Pixel_width[index] = send_.sendinfo[index].Pixel_width;
		ros_msg.Pixel_height[index] = send_.sendinfo[index].Pixel_height;
		ros_msg.real_width[index] = send_.sendinfo[index].real_width;
		ros_msg.real_height[index] = send_.sendinfo[index].real_height;
		if (send_.sendinfo[index].distance > 0) {
		ros_msg.distance[index] = 1000 * send_.sendinfo[index].distance;
		}
		else {
		ros_msg.distance[index] = 0;
		}
	}


	enemy_info_pub_.publish(ros_msg);

}



#endif
