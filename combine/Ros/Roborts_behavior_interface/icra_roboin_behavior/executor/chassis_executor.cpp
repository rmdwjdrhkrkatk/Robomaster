#include "chassis_executor.h"


namespace icra_roboin_behavior {


ChassisExecutor::ChassisExecutor(): executor_mode_(ChassisMode::IDLE), executor_state_(BehaviorState::IDLE), 
                                    global_planner_client_("global_planner_node_action",true),
                                    local_planner_client_("local_planner_node_action",true)
{
    ros::NodeHandle nh;
    speed_pub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
    accel_pub_ = nh.advertise<roborts_msgs::TwistAccel>("cmd_vel_acc",100);
    global_planner_client_.waitForServer();
    ROS_INFO("global planner server connected!");
    local_planner_client_.waitForServer();
    ROS_INFO("local planner server connected!"); 
}


void ChassisExecutor::Execute(const geometry_msgs::PoseStamped& nav_goal){
    executor_mode_ = ChassisMode::NAVIGATION;
    nav_goal_.goal = nav_goal;
    ROS_INFO("Chassis_executor in navigation mode... x: %f, y: %f",nav_goal_.goal.pose.position.x,nav_goal_.goal.pose.position.y);
    global_planner_client_.sendGoal(nav_goal_,
    actionlib::SimpleActionClient<roborts_msgs::GlobalPlannerAction>::SimpleDoneCallback(),
    actionlib::SimpleActionClient<roborts_msgs::GlobalPlannerAction>::SimpleActiveCallback(),
    boost::bind(&ChassisExecutor::GlobalPlannerFeedbackCB, this, _1));
    
    
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

BehaviorState ChassisExecutor::Update(){
    actionlib::SimpleClientGoalState state = actionlib::SimpleClientGoalState::LOST;
    switch(executor_mode_){
        case ChassisMode::IDLE:
            executor_state_ = BehaviorState::IDLE;
            break;
        case ChassisMode::NAVIGATION:
            state = global_planner_client_.getState();
            if (state == actionlib::SimpleClientGoalState::ACTIVE){
                ROS_INFO("%s : ACTIVE", __FUNCTION__);
                executor_state_ = BehaviorState::RUNNING;
            } else if (state == actionlib::SimpleClientGoalState::PENDING) {
                ROS_INFO("%s : PENDING", __FUNCTION__);
                executor_state_ = BehaviorState::RUNNING;
            } else if (state == actionlib::SimpleClientGoalState::SUCCEEDED) {
                ROS_INFO("%s : SUCCEEDED", __FUNCTION__);
                executor_state_ = BehaviorState::SUCCESS;
            } else if (state == actionlib::SimpleClientGoalState::ABORTED) {
                ROS_INFO("%s : ABORTED", __FUNCTION__);
                executor_state_ = BehaviorState::FAILURE;
            } else {
                ROS_ERROR("chassis executor update error: %s", state.toString().c_str());
                executor_state_ = BehaviorState::FAILURE;
            }
            break;

        case ChassisMode::SPEED:
            executor_state_ = BehaviorState::RUNNING;
            break;
        case ChassisMode::ACCEL: 
            executor_state_ = BehaviorState::RUNNING;
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
            global_planner_client_.cancelGoal();
            local_planner_client_.cancelGoal();
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
            usleep(50000);
            break;

        default:
            ROS_ERROR("chassis executor cancel error : wrong execution mode");
    }

}


void ChassisExecutor::GlobalPlannerFeedbackCB(const roborts_msgs::GlobalPlannerFeedbackConstPtr& feedback){
    if(!feedback->path.poses.empty()) {
        local_goal_.route = feedback->path;
        local_planner_client_.sendGoal(local_goal_);
    }
}

}