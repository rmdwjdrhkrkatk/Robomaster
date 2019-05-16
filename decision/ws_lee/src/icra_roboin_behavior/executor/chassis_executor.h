#ifndef ICRA__ROBOIN_BEHAVIOR_CHASSIS_EXECUTOR_H
#define ICRA__ROBOIN_BEHAVIOR_CHASSIS_EXECUTOR_H

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib_msgs/GoalID.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include "roborts_msgs/LocalPlannerAction.h"
#include "roborts_msgs/GlobalPlannerAction.h"
#include "roborts_msgs/TwistAccel.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "../enums.h"


namespace icra_roboin_behavior {

class ChassisExecutor{

    public:
        ChassisExecutor();
        ~ChassisExecutor() = default;

        void Execute(const geometry_msgs::PoseStamped& nav_goal);
        void Execute(const geometry_msgs::Twist& speed);
        void Execute(const roborts_msgs::TwistAccel& accel);
        void Cancel();


    private:
        //void GlobalPlannerFeedbackCB(const roborts_msgs::GlobalPlannerFeedbackConstPtr& feedback);
        
        ChassisMode executor_mode_;
        //actionlib::SimpleActionClient<roborts_msgs::LocalPlannerAction> local_planner_client_;
        //actionlib::SimpleActionClient<roborts_msgs::GlobalPlannerAction> global_planner_client_;
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> planner_client_;
        ros::Publisher planner_cancel_pub_;
        ros::Publisher speed_pub_;
        ros::Publisher accel_pub_;
       
        //roborts_msgs::GlobalPlannerGoal nav_goal_;
        move_base_msgs::MoveBaseGoal nav_goal_;

        geometry_msgs::Twist zero_vel_;
        roborts_msgs::TwistAccel zero_acc_;

        actionlib::SimpleClientGoalState state = actionlib::SimpleClientGoalState::LOST;
        /*
        zero_vel_.linear.x = 0;
        zero_vel_.linear.y = 0;
        zero_vel_.linear.z = 0;
        zero_vel_.angular.x = 0;
        zero_vel_.angular.y = 0;
        zero_vel_.angular.z = 0;

        zero_acc_.twist.linear.x = 0;
        zero_acc_.twist.linear.y = 0;
        zero_acc_.twist.linear.z = 0;
        zero_acc_.twist.angular.x = 0;
        zero_acc_.twist.angular.y = 0;
        zero_acc_.twist.angular.z = 0;

        zero_acc_.accel.linear.x = 0;
        zero_acc_.accel.linear.y = 0;
        zero_acc_.accel.linear.z = 0;
        zero_acc_.accel.angular.x = 0;
        zero_acc_.accel.angular.y = 0;
        zero_acc_.accel.angular.z = 0;
        */


			




};



}

#endif
