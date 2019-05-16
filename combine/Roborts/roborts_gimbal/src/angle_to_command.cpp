#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Header.h"
#include "roborts_msgs/GimbalAngle.h"
#include "gazebo_msgs/GetLinkState.h"
#include "gazebo_msgs/GetJointProperties.h"

std_msgs::Float64 pitch_angle_;
std_msgs::Float64 yaw_angle_;

std::string robot_namespace;

double yaw_pos;
double pitch_pos;

double yaw_command;
double pitch_command;

void angleCallback(const roborts_msgs::GimbalAngleConstPtr& msg) {
    ROS_INFO("Pitch Angle : %f", msg->pitch_angle);
    ROS_INFO("Yaw Angle : %f", msg->yaw_angle);

    if (msg->pitch_mode) {
        pitch_command = msg->pitch_angle;
    } else {
        pitch_command = msg->pitch_angle - pitch_pos;
    }

    if (msg->yaw_mode) {
        yaw_command = msg->yaw_angle;
    } else {
        yaw_command = msg->yaw_angle - yaw_pos;
    }
    
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "angle_to_command");
    ros::NodeHandle nh;

    nh.param<std::string>("robot_namespace", robot_namespace, "roborts_Red_0");

    ros::Subscriber sub = nh.subscribe("cmd_gimbal_angle", 1, angleCallback);
    ros::Publisher pub1 = nh.advertise<std_msgs::Float64>("pitch_position_controller/command", 1);
    ros::Publisher pub2 = nh.advertise<std_msgs::Float64>("yaw_position_controller/command", 1);

    ros::ServiceClient joint_property_client = nh.serviceClient<gazebo_msgs::GetJointProperties>("/gazebo/get_joint_properties");
    gazebo_msgs::GetJointProperties joint_property;

    ros::Rate loop_rate(10);
    
    // ros::ServiceClient get_link_state_client = nh.serviceClient<gazebo_msgs::GetLinkState>("/gazebo/get_link_state");
    // gazebo_msgs::GetLinkState svc;
    // svc.request.link_name = "pitch_Link";
    // svc.request.reference_frame = "map";

    while(ros::ok()){
        ros::spinOnce();

        joint_property.request.joint_name = robot_namespace + "base_link_to_yaw_joint";

        if(joint_property_client.call(joint_property)) {
            if(joint_property.response.success) {
                ROS_INFO("Service Recieved!");
                yaw_pos = joint_property.response.position[0];
                ROS_INFO("YAW_POS : %f", yaw_pos);
            } else {
                ROS_INFO("Recieve Fail!");
            }
        } else {
            ROS_INFO("CALL FAIL!");
        }

        joint_property.request.joint_name = robot_namespace + "base_link_to_yaw_joint";

        if(joint_property_client.call(joint_property)) {
            if(joint_property.response.success) {
                ROS_INFO("Service Recieved!");
                pitch_pos = joint_property.response.position[0];
                ROS_INFO("PITCH_POS : %f", pitch_pos);
            } else {
                ROS_INFO("Recieve Fail!");
            }
        } else {
            ROS_INFO("CALL FAIL!");
        }

        pitch_pos += pitch_command;
        yaw_pos += yaw_command;

        pitch_angle_.data = pitch_pos;
        yaw_angle_.data = yaw_pos;

        pub1.publish(pitch_angle_);
        pub2.publish(yaw_angle_);
        
        loop_rate.sleep();

        yaw_command = 0.0;
        pitch_command = 0.0;

    }
    return 0;
}
