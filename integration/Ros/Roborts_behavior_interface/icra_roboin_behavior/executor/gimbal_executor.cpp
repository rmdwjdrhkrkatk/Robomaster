#include "gimbal_executor.h"
namespace icra_roboin_behavior {

GimbalExecutor::GimbalExecutor():executor_mode_(GimbalMode::IDLE),
                                executor_state_(BehaviorState::IDLE)
{
    ros::NodeHandle nh;
    gimbal_pub_ = nh.advertise<roborts_msgs::GimbalAngle>("cmd_gimbal_angle",1);
}

void GimbalExecutor::Execute(const roborts_msgs::GimbalAngle& gimbal_angle){
    executor_mode_ = GimbalMode::ANGLE;
    gimbal_pub_.publish(gimbal_angle);
}

BehaviorState GimbalExecutor::Update(){
    switch (executor_mode_){
        case GimbalMode::IDLE:
            executor_state_ = BehaviorState::IDLE;
            break;
        case GimbalMode::ANGLE:
            executor_state_ = BehaviorState::RUNNING;
            break;
        default:
            ROS_ERROR("gimbal executor update error: wrong executor mode");
    }
    return executor_state_;
}

void GimbalExecutor::Cancel(){
    switch (executor_mode_){
        case GimbalMode::IDLE:
            ROS_INFO("gimbal executor cancle: nothing to be canceled");
            break;
        
        case GimbalMode::ANGLE:
            executor_mode_ = GimbalMode::IDLE;
            break;
        default:
            ROS_ERROR("gimbal executor cancel error: wrong executor mode");
    }
}



}