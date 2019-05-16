#ifndef ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_INTERFACE_H
#define ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_INTERFACE_H

#include <ros/ros.h>
#include "executor/chassis_executor.h"
#include "executor/gimbal_executor.h"
#include "blackboard/blackboard.h"
#include "behavior/move_behavior.h"
#include "behavior/manual_accel_behavior.h"
#include "behavior/manual_speed_behavior.h"
#include "icra_roboin_msgs/BehaviorStyleSet.h"
#include "icra_roboin_msgs/SetGoal_2.h"
#include "icra_roboin_msgs/BlackboardGeneralInfo.h"
#include <memory>
#include <vector>


namespace icra_roboin_behavior {

class BehaviorInterface {
    public:
        BehaviorInterface(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::Blackboard*& blackboard,
                    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>>& behavior_factory);


        ~BehaviorInterface() = default;

        void Run();
        
        

        bool SetBehaviorStyleCB(icra_roboin_msgs::BehaviorStyleSet::Request &req, icra_roboin_msgs::BehaviorStyleSet::Response &res);
        bool SetBehaviorGoalCB(icra_roboin_msgs::SetGoal_2::Request &req, icra_roboin_msgs::SetGoal_2::Response &res);
        bool GetGeneralInfoServiceCB(icra_roboin_msgs::BlackboardGeneralInfo::Request& req, icra_roboin_msgs::BlackboardGeneralInfo::Response& resp);
        icra_roboin_behavior::ChassisExecutor* const chassis_executor_;
        icra_roboin_behavior::GimbalExecutor* const gimbal_executor_;
        icra_roboin_behavior::Blackboard* const blackboard_;
        std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory_;


    private:
        void UpdateBlackboardState();

        ros::ServiceServer set_behavior_style_service_;
        ros::ServiceServer set_goal_service_;
        ros::ServiceServer general_info_server_;
        
};










}

#endif