#include "roborts_msgs/GimbalAngle.h"
#include "roborts_msgs/FricWhl.h"
#include "roborts_msgs/GimbalMode.h"
#include "roborts_msgs/ShootCmd.h"

#include "ros/ros.h"

void commandGimbalAngle(ros::Publisher &cmd_gimbal_angle_pub_, roborts_msgs::GimbalAngle &gimbal_angle_);
void setGimbalMode(ros::ServiceClient &gimbal_mode_client_, roborts_msgs::GimbalMode &gimbal_mode_);
void setFricWhl(ros::ServiceClient &cmd_fric_whl_client_, roborts_msgs::FricWhl &fric_whl_);
void commandShoot(ros::ServiceClient &cmd_shoot_client, roborts_msgs::ShootCmd &shoot_cmd_);



int main(int argc, char **argv) {

    ros::init(argc, argv, "behavior_test_node");

    ros::NodeHandle nh;

    ros::Publisher cmd_gimbal_angle_pub = nh.advertise<roborts_msgs::GimbalAngle>("cmd_gimbal_angle", 1);
    roborts_msgs::GimbalAngle gimbal_angle;

    ros::ServiceClient gimbal_mode_client = nh.serviceClient<roborts_msgs::GimbalMode>("set_gimbal_mode");
    roborts_msgs::GimbalMode gimbal_mode;

    ros::ServiceClient cmd_fric_whl_client = nh.serviceClient<roborts_msgs::FricWhl>("cmd_fric_wheel");
    roborts_msgs::FricWhl fric_whl;

    ros::ServiceClient cmd_shoot_client = nh.serviceClient<roborts_msgs::ShootCmd>("cmd_shoot");
    roborts_msgs::ShootCmd shoot_cmd;
    
    char selection;

    ros::Rate rate(10);
    while(ros::ok()){

        std::cout << "**************************************************************************************" << std::endl;
        std::cout << "**********************************Select Action***************************************" << std::endl;
        std::cout << "1: Command Gimbal Angle" << std::endl
                << "2: Set Gimbal Mode" << std::endl
                << "3: Set Fric Whl" << std::endl
                << "4: Commnad Shoot" << std::endl;
        std::cout << "**************************************************************************************" << std::endl;
        std::cout << "> ";
        std::cin >> selection;
        
        switch (selection) {
        //back to boot area
        case '1':
            commandGimbalAngle(cmd_gimbal_angle_pub, gimbal_angle);
            break;
            //patrol
        case '2':
            setGimbalMode(gimbal_mode_client, gimbal_mode);
            break;
            //chase.
        case '3':
            setFricWhl(cmd_fric_whl_client, fric_whl);
            break;
            //search
        case '4':
            commandShoot(cmd_shoot_client, shoot_cmd);
            break;
            //escape.
        default:
            break;
        }

        ros::spinOnce();
        rate.sleep();
    }

    
    return 0;
    
}

void commandGimbalAngle(ros::Publisher &cmd_gimbal_angle_pub_, roborts_msgs::GimbalAngle &gimbal_angle_) {
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "*********************************Command Gimbal Angle*********************************" << std::endl;
    std::cout << "Yaw Angle : ";
    std::cin >> gimbal_angle_.yaw_angle;
    std::cout << std::endl << "Pitch Angle : ";
    std::cin >> gimbal_angle_.pitch_angle;

    gimbal_angle_.yaw_mode = true;
    gimbal_angle_.pitch_mode = true;

    cmd_gimbal_angle_pub_.publish(gimbal_angle_);

    // ros::spin();
}

void setGimbalMode(ros::ServiceClient &gimbal_mode_client_, roborts_msgs::GimbalMode &gimbal_mode_) {
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "*********************************Set Gimbal Mode*********************************" << std::endl;
    std::cout << "Gimbal Mode(uint8) : ";
    std::cin >> gimbal_mode_.request.gimbal_mode;

    if (gimbal_mode_client_.call(gimbal_mode_)) {
        ROS_INFO("Call Success");
        if(gimbal_mode_.response.received == true){
            ROS_INFO("Received");
        } else {
            ROS_WARN("Not Received");
        }
    } else {
        ROS_ERROR("Call Fail");
    }
}


void setFricWhl(ros::ServiceClient &cmd_fric_whl_client_, roborts_msgs::FricWhl &fric_whl_) {
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "*********************************Set Fric whl*********************************" << std::endl;
    std::cout << "Fric Whl(bool) : ";
    std::cin >> fric_whl_.request.open;

    if (cmd_fric_whl_client_.call(fric_whl_)) {
        ROS_INFO("Call Success");
        if(fric_whl_.response.received == true){
            ROS_INFO("Received");
        } else {
            ROS_WARN("Not Received");
        }
    } else {
        ROS_ERROR("Call Fail");
    }
}

void commandShoot(ros::ServiceClient &cmd_shoot_client_, roborts_msgs::ShootCmd &shoot_cmd_){
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "*********************************Command Shoot*********************************" << std::endl;
    std::cout << "Shoot Mode(uint8) : ";
    std::cin >> shoot_cmd_.request.mode;
    std::cout << std::endl << "Shoot Number(uint8) : ";
    std::cin >> shoot_cmd_.request.number;

    if (cmd_shoot_client_.call(shoot_cmd_)) {
        ROS_INFO("Call Success");
        if(shoot_cmd_.response.received == true){
            ROS_INFO("Received");
        } else {
            ROS_WARN("Not Received");
        }
    } else {
        ROS_ERROR("Call Fail");
    }

}