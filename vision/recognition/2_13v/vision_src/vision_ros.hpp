

#ifdef ROS
#include "icra_roboin_msgs/PitchGain.h"
#include "icra_roboin_msgs/YawGain.h"
#include "icra_roboin_msgs/YoloDetectionInfo.h"
#include "roborts_msgs/GimbalAngle.h"
#include "roborts_msgs/ShootCmd.h"
#include "ros/ros.h"
#include "SendData_Control.hpp"
#include "pch.hpp"

float YAW_P_GAIN = 0.0002;
float YAW_I_GAIN = 0.001;
float YAW_D_GAIN = 0.001;

float PITCH_P_GAIN = 0.001;
float PITCH_I_GAIN = 0.001;
float PITCH_D_GAIN = 0.001;

#define X_CENTER_PIXEL 320
#define Y_CENTER_PIXEL 240


float yaw_prev_error = 0;
float pitch_prev_error = 0;
float yaw_i_error = 0;
float pitch_i_error = 0;
roborts_msgs::GimbalAngle gimbal_angle;




bool SetYawGainCallback(icra_roboin_msgs::YawGain::Request &req,
                        icra_roboin_msgs::YawGain::Response &resp ) {
    if(req.p != 0.0) YAW_P_GAIN = req.p;
    if(req.i != 0.0) YAW_I_GAIN = req.i;
    if(req.d != 0.0) YAW_D_GAIN = req.d;

    resp.received = true;
    return true;
}

bool SetPitchGainCallback(icra_roboin_msgs::PitchGain::Request &req,
                          icra_roboin_msgs::PitchGain::Response &resp) {

    if(req.p != 0.0) PITCH_P_GAIN = req.p;
    if(req.i != 0.0) PITCH_I_GAIN = req.i;
    if(req.d != 0.0) PITCH_D_GAIN = req.d;

    resp.received = true;
    return true;
}


void rosPixelControl(int number_of_detection, Sendinfo& gimbal, ros::Publisher cmd_gimbal_angle_pub_) {
    if(number_of_detection > 0) {

        Sendinfo target = gimbal;

        short pixel_error_x = target.Pixel_X - X_CENTER_PIXEL;
        short pixel_error_y = target.Pixel_Y - Y_CENTER_PIXEL;

        yaw_i_error += pixel_error_x;
        pitch_i_error += pixel_error_y;

        // pid
//		gimbal_angle.yaw_angle = pixel_error_x * YAW_P_GAIN + yaw_i_error * YAW_I_GAIN + (yaw_prev_error - pixel_error_x) * YAW_D_GAIN;
//		gimbal_angle.pitch_angle = pixel_error_y * PITCH_P_GAIN + pitch_i_error * PITCH_I_GAIN + (pitch_prev_error- pixel_error_y) * PITCH_D_GAIN;

        gimbal_angle.yaw_angle = -pixel_error_x * YAW_P_GAIN;
        gimbal_angle.pitch_angle = pixel_error_y * PITCH_P_GAIN;

        gimbal_angle.yaw_mode = true;
        gimbal_angle.pitch_mode = true;

        cmd_gimbal_angle_pub_.publish(gimbal_angle);

        yaw_prev_error = pixel_error_x;
        pitch_prev_error = pixel_error_y;


    } else {
        yaw_i_error = 0;
        pitch_i_error = 0;

        yaw_prev_error = 0;
        pitch_prev_error = 0;
    }
}


void pubEnemyInfo(sendDataset& send_, ros::Publisher enemy_info_pub_) {

    icra_roboin_msgs::YoloDetectionInfo ros_msg;

    ros_msg.stamp = ros::Time();
    ros_msg.number_of_detection= send_.number_of_detection;



    ros_msg.enemy_detected[0] = send_.data_1.infochecker;
    ros_msg.angle_hori[0] = send_.data_1.angle_hori;
    ros_msg.angle_verti[0] = send_.data_1.angle_verti;
    ros_msg.Pixel_X[0] = send_.data_1.Pixel_X;
    ros_msg.Pixel_Y[0] = send_.data_1.Pixel_Y;
    ros_msg.Pixel_width[0] = send_.data_1.Pixel_width;
    ros_msg.Pixel_height[0] = send_.data_1.Pixel_height;
    ros_msg.real_width[0] = send_.data_1.real_width;
    ros_msg.real_height[0] = send_.data_1.real_height;
    ros_msg.distance[0] = send_.data_1.distance;



    ros_msg.enemy_detected[1] = send_.data_2.infochecker;
    ros_msg.angle_hori[1] = send_.data_2.angle_hori;
    ros_msg.angle_verti[1] = send_.data_2.angle_verti;
    ros_msg.Pixel_X[1] = send_.data_2.Pixel_X;
    ros_msg.Pixel_Y[1] = send_.data_2.Pixel_Y;
    ros_msg.Pixel_width[1] = send_.data_2.Pixel_width;
    ros_msg.Pixel_height[1] = send_.data_2.Pixel_height;
    ros_msg.real_width[1] = send_.data_2.real_width;
    ros_msg.real_height[1] = send_.data_2.real_height;
    ros_msg.distance[1] = send_.data_2.distance;



    ros_msg.enemy_detected[2] = send_.data_3.infochecker;
    ros_msg.angle_hori[2] = send_.data_3.angle_hori;
    ros_msg.angle_verti[2] = send_.data_3.angle_verti;
    ros_msg.Pixel_X[2] = send_.data_3.Pixel_X;
    ros_msg.Pixel_Y[2] = send_.data_3.Pixel_Y;
    ros_msg.Pixel_width[2] = send_.data_3.Pixel_width;
    ros_msg.Pixel_height[2] = send_.data_3.Pixel_height;
    ros_msg.real_width[2] = send_.data_3.real_width;
    ros_msg.real_height[2] = send_.data_3.real_height;
    ros_msg.distance[2] = send_.data_3.distance;


    enemy_info_pub_.publish(ros_msg);

}



#endif