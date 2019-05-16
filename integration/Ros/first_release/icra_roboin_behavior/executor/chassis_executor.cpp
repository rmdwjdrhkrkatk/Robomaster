#include "chassis_executor.h"


namespace icra_roboin_behavior {


ChassisExecutor::ChassisExecutor(): executor_mode_(ChassisMode::IDLE), executor_state_(BehaviorProcess::IDLE), 
                                    planner_client_("move_base",true)                                    
{
    ros::NodeHandle nh;
    speed_pub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
    speed_with_lockon_pub_ = nh.advertise<geometry_msgs::Twist>("omni_cmd_vel",1);
    accel_pub_ = nh.advertise<roborts_msgs::TwistAccel>("cmd_vel_acc",100);
    planner_cancel_pub_=nh.advertise<actionlib_msgs::GoalID>("move_base/cancel",1);
    planner_client_.waitForServer();
    ROS_INFO("motion planner server connected!");

}


void ChassisExecutor::Execute(const geometry_msgs::PoseStamped& nav_goal){
    executor_mode_ = ChassisMode::NAVIGATION;
    nav_goal_.target_pose = nav_goal;
    ROS_INFO("Chassis_executor in navigation mode... x: %f, y: %f",nav_goal_.target_pose.pose.position.x,nav_goal_.target_pose.pose.position.y);
    planner_client_.sendGoal(nav_goal_);
    
}

void ChassisExecutor::Execute(const icra_roboin_msgs::LockonSpeedControl& speed_xy){
    if(executor_mode_ == ChassisMode::NAVIGATION) Cancel();
    executor_mode_ = ChassisMode::SPEED_WITH_LOCKON;
    ROS_INFO("Chassis_executor in speed with lockon mode... x: %f, y: %f",speed_xy.x,speed_xy.y);
    geometry_msgs::Twist speed;
    speed.linear.x=speed_xy.x;
    speed.linear.y=speed_xy.y;
    speed_with_lockon_pub_.publish(speed);
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

BehaviorProcess ChassisExecutor::Update(){
    actionlib::SimpleClientGoalState state = actionlib::SimpleClientGoalState::LOST;
    switch(executor_mode_){
        case ChassisMode::IDLE:
            executor_state_ = BehaviorProcess::IDLE;
            break;
        case ChassisMode::NAVIGATION:
            state = planner_client_.getState();
            if (state == actionlib::SimpleClientGoalState::ACTIVE){
                //ROS_INFO("%s : ACTIVE", __FUNCTION__);
                executor_state_ = BehaviorProcess::RUNNING;
            } else if (state == actionlib::SimpleClientGoalState::PENDING) {
                //ROS_INFO("%s : PENDING", __FUNCTION__);
                executor_state_ = BehaviorProcess::RUNNING;
            } else if (state == actionlib::SimpleClientGoalState::SUCCEEDED) {
                //ROS_INFO("%s : SUCCEEDED", __FUNCTION__);
                executor_state_ = BehaviorProcess::SUCCESS;
            } else if (state == actionlib::SimpleClientGoalState::ABORTED) {
                //ROS_INFO("%s : ABORTED", __FUNCTION__);
                executor_state_ = BehaviorProcess::FAILURE;
            } else {
                ROS_ERROR("chassis executor update error: %s", state.toString().c_str());
                executor_state_ = BehaviorProcess::FAILURE;
            }
            break;
        case ChassisMode::SPEED_WITH_LOCKON:
            executor_state_ = BehaviorProcess::RUNNING;
            break;

        case ChassisMode::SPEED:
            executor_state_ = BehaviorProcess::RUNNING;
            break;
        case ChassisMode::ACCEL: 
            executor_state_ = BehaviorProcess::RUNNING;
            break;

        default:
            ROS_ERROR("chassis executor update error: wrong execution mode");
    }
    return executor_state_;
}




void ChassisExecutor::Cancel(){

    switch (executor_mode_){
        case ChassisMode::IDLE:
            ROS_INFO("Chassis Executor: Nothing to be canceled.");
            break;

        case ChassisMode::NAVIGATION:
            planner_client_.cancelAllGoals();
            planner_cancel_pub_.publish(nav_cancel_msg_);
            executor_mode_ = ChassisMode::IDLE;
            ROS_INFO("chassis executor: Cancel Navigation");
            break;

        case ChassisMode::SPEED_WITH_LOCKON:
            speed_with_lockon_pub_.publish(zero_vel_);
            executor_mode_ = ChassisMode::IDLE;
            ROS_INFO("chassis executor: Cancel speed with lockon");
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
            usleep(50000);
            break;

        default:
            ROS_ERROR("chassis executor cancel error : wrong execution mode");
    }

}





}