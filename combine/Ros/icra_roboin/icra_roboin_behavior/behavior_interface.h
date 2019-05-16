#ifndef ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_INTERFACE_H
#define ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_INTERFACE_H

#include <ros/ros.h>
#include <memory>
#include <vector>

#include "executor/chassis_executor.h"
#include "executor/gimbal_executor.h"
#include "blackboard/blackboard.h"
#include "executor/lockon_module.h"

#include "behavior/abstract/behavior_base.h"
#include "behavior/hold_rotate_behavior.h"
#include "behavior/hold_sentry_behavior.h"
#include "behavior/lockon_search_move_behavior.h"
#include "behavior/manual_speed_control_behavior.h"
#include "behavior/reload_behavior.h"
#include "behavior/get_buff_behavior.h"
#include "behavior/ready_behavior.h"
#include "behavior/backboot_behavior.h"
#include "icra_roboin_msgs/BehaviorStyleSet.h"
#include "icra_roboin_msgs/SetGoal_2.h"
#include "icra_roboin_msgs/SetEnemyPriority.h"
#include "icra_roboin_msgs/BlackboardGeneralInfo.h"
#include "icra_roboin_msgs/RefereeShoot.h"
#include "icra_roboin_msgs/RefereeTag.h"
#include "icra_roboin_msgs/ConfirmHit.h"
#include "icra_roboin_msgs/AmmoConsume.h"





namespace icra_roboin_behavior {

class BehaviorInterface {
    public:
        BehaviorInterface(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::LockonModule*& lockon_module,
                    icra_roboin_behavior::Blackboard*& blackboard,
                    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>>& behavior_factory);


        ~BehaviorInterface() = default;

        void Run();
        
        // callback for set_behavior_style_service_   Service name: "behavior_select_service"
        bool SetBehaviorStyleCB(icra_roboin_msgs::BehaviorStyleSet::Request &req, 
                                icra_roboin_msgs::BehaviorStyleSet::Response &res); 
        // callback for set_goal_service_   Service name: "goal_select_service"
        bool SetBehaviorGoalCB(icra_roboin_msgs::SetGoal_2::Request &req, 
                                icra_roboin_msgs::SetGoal_2::Response &res);
        // callback for set_enemy_priority_service_   Service name: "set_enemy_priority_service" 
        bool SetEnemyPriorityCB(icra_roboin_msgs::SetEnemyPriority::Request &req, 
                                icra_roboin_msgs::SetEnemyPriority::Response &res);
        // callback for general_info_service_  Service name: "blackboard/general_info_service" 
        bool GetGeneralInfoServiceCB(icra_roboin_msgs::BlackboardGeneralInfo::Request& req, 
                                icra_roboin_msgs::BlackboardGeneralInfo::Response& resp); 
        bool ConfirmHitServiceCB(icra_roboin_msgs::ConfirmHit::Request& req, 
                                icra_roboin_msgs::ConfirmHit::Response& resp); 
        bool AmmoConsumeServiceCB(icra_roboin_msgs::AmmoConsume::Request& req, 
                                icra_roboin_msgs::AmmoConsume::Response& resp); 

        

                                                               

        /*                         
        bool RefereeShootCB(icra_roboin_msgs::RefereeShoot::Request& req, 
                            icra_roboin_msgs::RefereeShoot::Response& resp);  // callback for referee_shoot_service_ Service name: "referee_shoot_service"
        bool RefereeTagCB(icra_roboin_msgs::RefereeTag::Request& req,
                                 icra_roboin_msgs::RefereeTag::Response& resp); // callback for referee_tag_service_ Service name: "referee_tag_service"                
        */

        icra_roboin_behavior::ChassisExecutor* const chassis_executor_;
        icra_roboin_behavior::GimbalExecutor* const gimbal_executor_;
        icra_roboin_behavior::LockonModule* const lockon_module_;
        icra_roboin_behavior::Blackboard* const blackboard_;
        std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory_;


    private:
        void UpdateBehaviorProcess();

        ros::ServiceServer set_behavior_style_service_; //Service name: "behavior_select_service"
        ros::ServiceServer set_goal_service_; //Service name: "goal_select_service"
        ros::ServiceServer set_enemy_priority_service_; //set enemy priority. Service name: "set_enemy_priority_service"
        ros::ServiceServer general_info_server_; // Service name: "blackboard/general_info_service"
        ros::ServiceServer confirm_hit_server_; // Service name: "confirm_hit_service"
        ros::ServiceServer ammo_consume_server_; // Service name: "ammo_consume_service"


        //ros::ServiceServer referee_shoot_service_; // request referee for hitscan judgement.    Service name: "referee_shoot_service"
        //ros::ServiceServer referee_tag_service_; // tagging Reload/Buff Zone service.   Service name: "referee_tag_service"
        
};










}

#endif