#include "chassis_executor.h"


namespace icra_roboin_behavior {



	


//ChassisExecutor::ChassisExecutor(std::string a): executor_mode_(ChassisMode::IDLE),
//                                    planner_client_( a + "/move_base",true)
ChassisExecutor::ChassisExecutor(): executor_mode_(ChassisMode::IDLE),
                                    planner_client_("move_base",true)
{
    ros::NodeHandle nh;
    speed_pub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
    accel_pub_ = nh.advertise<roborts_msgs::TwistAccel>("cmd_vel_acc",100);
    ROS_INFO("motion planner server connected!");

}


void ChassisExecutor::Execute(const geometry_msgs::PoseStamped& nav_goal){
    executor_mode_ = ChassisMode::NAVIGATION;
    nav_goal_.target_pose = nav_goal;
    ROS_ERROR("Chassis_executor in navigation mode... w: %f, y: %f",nav_goal_.target_pose.pose.orientation.w,nav_goal_.target_pose.pose.position.y);
    planner_client_.sendGoal(nav_goal_);
    
}

void ChassisExecutor::Execute(const geometry_msgs::Twist& speed){
    if(executor_mode_ == ChassisMode::NAVIGATION) Cancel();
    executor_mode_ = ChassisMode::SPEED;
    ROS_INFO("Chassis_executor in speed mode... x: %f, y: %f, w: %f",speed.linear.x,speed.linear.y,speed.angular.z);
    speed_pub_.publish(speed);
}

void ChassisExecutor::Execute(const roborts_msgs::TwistAccel& accel){
    if(executor_mode_ == ChassisMode::NAVIGATION) Cancel();
    executor_mode_ = ChassisMode::ACCEL;
    ROS_INFO("Chassis_executor in accel mode...");
    accel_pub_.publish(accel);
}


void ChassisExecutor::Cancel(){

    switch (executor_mode_){
        case ChassisMode::IDLE:
            ROS_INFO("Chassis Executor: Nothing to be canceled.");
            break;

        case ChassisMode::NAVIGATION:
            planner_client_.cancelAllGoals();
            executor_mode_ = ChassisMode::IDLE;
            ROS_INFO("chassis executor: Cancel Navigation");
            break;

        case ChassisMode::SPEED:
            speed_pub_.publish(zero_vel_);
            executor_mode_ = ChassisMode::IDLE;
            ROS_INFO("chassis executor: Cancel speed");
            break;

        case ChassisMode::ACCEL:
            accel_pub_.publish(zero_acc_);
            executor_mode_ = ChassisMode::IDLE;
            ROS_INFO("chassis executor: Cancel accel");
            break;

        default:
            ROS_ERROR("chassis executor cancel error : wrong execution mode");
    }

}





}
