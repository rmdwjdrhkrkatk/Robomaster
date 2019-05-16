#ifndef ICRA__ROBOIN_BEHAVIOR_CHASSIS_EXECUTOR_H
#define ICRA__ROBOIN_BEHAVIOR_CHASSIS_EXECUTOR_H

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include "roborts_msgs/LocalPlannerAction.h"
#include "roborts_msgs/GlobalPlannerAction.h"
#include "roborts_msgs/TwistAccel.h"
#include "../enums.h"


namespace icra_roboin_behavior {

class ChassisExecutor{

    public:
        ChassisExecutor();
        ~ChassisExecutor() = default;

        void Execute(const geometry_msgs::PoseStamped& nav_goal);
        void Execute(const geometry_msgs::Twist& speed);
        void Execute(const roborts_msgs::TwistAccel& accel);
        BehaviorState Update();
        void Cancel();


    private:
        void GlobalPlannerFeedbackCB(const roborts_msgs::GlobalPlannerFeedbackConstPtr& feedback);
        ChassisMode executor_mode_;
        BehaviorState executor_state_;
        actionlib::SimpleActionClient<roborts_msgs::LocalPlannerAction> local_planner_client_;
        actionlib::SimpleActionClient<roborts_msgs::GlobalPlannerAction> global_planner_client_;
        ros::Publisher speed_pub_;
        ros::Publisher accel_pub_;

        roborts_msgs::GlobalPlannerGoal nav_goal_;
        roborts_msgs::LocalPlannerGoal local_goal_;
        geometry_msgs::Twist zero_vel_;
        roborts_msgs::TwistAccel zero_acc_;





};



}

#endif