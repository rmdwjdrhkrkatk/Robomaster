#ifndef ICRA_ROBOIN_BEHAVIOR_BLACKBOARD_H
#define ICRA_ROBOIN_BEHAVIOR_BLACKBOARD_H


#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include "../enums.h"
#include "../constants.h"
#include "icra_roboin_msgs/YoloDetectionInfo.h"
#include "icra_roboin_msgs/GoalDescription.h"
#include "icra_roboin_msgs/RefereeGameState.h"
#include "icra_roboin_msgs/RefereeHit.h"
#include "icra_roboin_msgs/RefereePenalty.h"
#include "icra_roboin_msgs/RefereeBuff.h"
#include "icra_roboin_msgs/RefereeReload.h"


/*
#include "roborts_msgs/BonusStatus.h"
#include "roborts_msgs/GameResult.h"
#include "roborts_msgs/GameStatus.h"
#include "roborts_msgs/GameSurvivor.h"
#include "roborts_msgs/ProjectileSupply.h"
#include "roborts_msgs/RobotBonus.h"
#include "roborts_msgs/RobotDamage.h"
#include "roborts_msgs/RobotHeat.h"
#include "roborts_msgs/RobotShoot.h"
#include "roborts_msgs/RobotStatus.h"
#include "roborts_msgs/SupplierStatus.h"
*/



namespace icra_roboin_behavior {



class Blackboard {
    

    public: //Interfaces
        Blackboard(TeamType team, RuleType rule);
        ~Blackboard() = default;

        /*   Referee Info Interface   */
        //Game State Info
        ros::Time GetTimeGameStarted() const;  
        const ros::Duration GetTimePassedFromGameStart();  
        GameState GetGameState() const;
        //Zone Info
        bool GetIsBuffZoneOnline() const;
        ros::Time GetTimeLastBuffed() const;  
        const ros::Duration GetTimeLeftForBuffZoneToOnline();  
        bool GetIsReloadZoneOnline() const;
        ros::Time GetTimeLastReloaded() const;  
        const ros::Duration GetTimeLeftForReloadZoneToOnline();  //TODO need to be changed to abide rule
        //HP Info
        int GetMyHealth() const;
        bool GetIsHitFastResponse() const; // read only, got hit by enemy and need urgent behavior-level response 
        void ConfirmHitFastResponse();  // set is_hit_fast_response to false, set hit_confirmed_fast_response_ true,
        bool GetHitConfirmedFastResponse() const; // meaning every behavior-level measure ought to be taken when hit is finished
        bool GetIsHitSmartResponse() const; // read only, got hit by enemy and need intelligent decision-level response
        void ConfirmHitSmartResponse();  // set is_hit_smart_response to false, set hit_confirmed_smart_response_ true,
        bool GetHitConfirmedSmartResponse() const; //meaning every decision-level measure ought to be taken when hit is finished
        ArmorType GetWhichArmorHit() const; 
        ros::Time GetTimeLastHit() const;  
        //Defense Buff Info
        bool GetHasBuff() const;
        const ros::Duration GetTimeBuffLeft(); 
        //Ammunition Info
        int GetAmmo() const;
        bool GetIsReloading() const;

        /*   Team Info Interface   */
        geometry_msgs::PoseStamped GetAllyPose() const;
        TeamType GetMyTeam() const;
        bool GetIsAllyAlive() const;

        /*   Perception Info Interface   */
        const geometry_msgs::PoseStamped GetMyPose(); // get my pose from TF. lazily updates my_pose_.
        geometry_msgs::PoseStamped GetAllyPoseFromVision() const;
        geometry_msgs::PoseStamped GetEnemyPose(PlayerType who) const; //who: ENEMY_ONE ENEMY_TWO
        geometry_msgs::PoseStamped GetEnemyEstim(PlayerType who) const; //who: ENEMY_ONE ENEMY_TWO
        int GetNumberOfDetectedEnemies() const;
        bool GetIsEnemyDetected(PlayerType who) const; //who: ENEMY_ONE ENEMY_TWO ENEMY_ANY
        PlayerType GetWhichEnemyDetected() const;
        bool GetIsNewEnemy() const; //read only
        bool IsNewEnemy(); //when called, is_enemy_new_ is set to false
        ros::Time GetTimeLastSeen(PlayerType who) const;
        
        /*   Behavior Info Interface   */
        PlayerType GetLockedOnEnemy() const; 
        bool GetIsNewLockonTarget() const; //read only
        bool IsNewLockonTarget(); //when called, is_new_lockon_target_ is set to false
        bool GetIsNewGoal() const; //read only
        bool IsNewGoal(); //when called, is_new_goal_ is set to false
        icra_roboin_msgs::GoalDescription GetGoal() const; // goal for current behavior
        const geometry_msgs::PoseStamped GetGoalPoseQuaternion(); // transform goal pose into quaternion lazily.
        BehaviorStyle GetBehaviorStyle() const;
        BehaviorProcess GetBehaviorProcess() const;

        /*   Smart Decision and Tactics Info Interface   */
        PlayerType GetEnemyPriority() const;



        /*   External Set Interface   */
        void SetGoal(const icra_roboin_msgs::GoalDescription goal);
        void SetBehaviorStyle(const BehaviorStyle new_style);
        void SetBehaviorProcess(const BehaviorProcess process);
        void SetEnemyPriority(const PlayerType who);
        void SetLockedOnEnemy(const PlayerType who); //who: ALLY, ENEMY_ONE ENEMY_TWO       ALLY means do not lock on
        void AmmoMinusOne();
        void SetIsReloading(const bool flag);


    private: // Referee Info

        //Game State Info
        ros::Time time_game_started_;  
        ros::Duration time_passed_from_game_start_;  
        GameState game_state_;
        RuleType game_rule_; //1vs1, 2vs2...
        PenaltyType penalty_received_;

        //Zone Info
        bool is_buff_zone_online_=true;
        ros::Time time_last_buffed_; 
        ros::Duration time_left_for_buff_zone_to_online_;  
        bool is_reload_zone_online_=true;
        ros::Time time_last_reloaded_;  
        ros::Duration time_left_for_reload_zone_to_online_;  

        //HP Info
        int my_health_;
        bool is_hit_fast_response_=false;
        bool is_hit_smart_response_=false;
        bool hit_confirmed_fast_response_=false;
        bool hit_confirmed_smart_response_=false;
        ArmorType which_armor_hit_;
        ros::Time time_last_hit_; 

        //Defense Buff Info
        bool has_buff_=false;
        ros::Duration time_buff_left_;
        bool has_enemy_buff_=false;
        ros::Duration time_enemy_buff_left_;
        std::array<double,3> enemy_buff_time_estimation_moments_; //variance, skewness, kurtosis

        //Ammunition Info
        int ammo_;
        bool is_reloading_ = false;

    private: //Team Info
        geometry_msgs::PoseStamped ally_pose_;
        TeamType my_team_;
        bool is_ally_alive_=false;
        
    private: // Perception Info

        //My Pose
        geometry_msgs::PoseStamped my_pose_;
        geometry_msgs::PoseStamped amcl_pose_;
        geometry_msgs::PoseStamped uwb_pose_;

        //Enemy Pose
        geometry_msgs::PoseStamped enemy_pose_1_;  //real pose from vision
        geometry_msgs::PoseStamped enemy_pose_2_;  
        geometry_msgs::PoseStamped enemy_pose_1_ghost_;  //last seen location
        geometry_msgs::PoseStamped enemy_pose_2_ghost_;
        geometry_msgs::PoseStamped enemy_pose_1_estim_;  //approximate enemy location estimated by AI
        geometry_msgs::PoseStamped enemy_pose_2_estim_;
        ros::Time time_enemy_1_last_seen_;  
        ros::Time time_enemy_2_last_seen_;  
        ros::Time time_enemy_last_seen_;  

        //Ally Pose
        geometry_msgs::PoseStamped ally_pose_from_vision_;  //ally pose from vision
        ros::Time time_ally_last_seen_;  

        //Unknown Pose
        geometry_msgs::PoseStamped unknown_pose_;  //real pose from vision  
        geometry_msgs::PoseStamped unknown_pose_ghost_;  //last seen location
        geometry_msgs::PoseStamped unknown_pose_estim_;  //approximate enemy location estimated by AI
        ros::Time time_unknown_last_seen_;  


        //Detection Info
        int number_of_detection_;
        int number_of_detected_enemies_;

        bool is_ally_detected_=false;
        bool is_enemy_1_detected_=false;
        bool is_enemy_2_detected_=false;
        bool is_enemy_detected_=false;
        bool is_unknown_detected_=false;

        bool is_new_enemy_=false;

    private: // Behavior Info

        PlayerType locked_on_enemy_; // who: ALLY, ENEMY_ONE ENEMY_TWO       ALLY means do not lock on
        bool is_new_lockon_target_=false;
        bool is_new_goal_=false;
        icra_roboin_msgs::GoalDescription goal_;
        geometry_msgs::PoseStamped goal_pose_quaternion_;
        BehaviorStyle behavior_style_;
        BehaviorProcess behavior_process_;

    private: // Smart Decision and Tactics Info
        PlayerType enemy_priority_;





///////////////////Techincal//////////////////////////



    private: //Resources
        std::shared_ptr<tf::TransformListener> tf_ptr_;
        ros::Subscriber enemy_detection_sub_;  // receives Yolo detection result.   Topic name:"enemy_info"
        std::string namespace_;  // ROS namespace of this node

        // update HP of robot according to referee hit judgement and record it.    Service name: "referee_hit_service"
        ros::ServiceServer referee_hit_service_; 
        // update game state according to referee request.   Service name: "referee_game_state_service"
        ros::ServiceServer referee_game_state_service_; 
        // service to receive referee penalty.    Service name: "referee_penalty_service"
        ros::ServiceServer referee_penalty_service_; 
        // service for getting buffstate from referee.   Service name: "referee_buff_service"
        ros::ServiceServer referee_buff_service_;
        // service for getting reload state from referee.   Service name: "referee_reload_service"
        ros::ServiceServer referee_reload_service_;

        /*
        ros::Subscriber referee_bonus_status_sub_;
        ros::Subscriber referee_game_result_sub_;
        ros::Subscriber referee_game_status_sub_;
        ros::Subscriber referee_game_survivor_sub_;
        ros::Subscriber referee_projectile_supply_sub_;
        ros::Subscriber referee_robot_bonus_sub_;
        ros::Subscriber referee_robot_damage_sub_;
        ros::Subscriber referee_robot_heat_sub_;
        ros::Subscriber referee_robot_shoot_sub_;
        ros::Subscriber referee_robot_status_sub_;
        ros::Subscriber referee_supplier_status_sub_;
        */



    
    public: // Callback functions
        void EnemyDetectionCB(const icra_roboin_msgs::YoloDetectionInfo::ConstPtr& yolo);  // callback for detection_sub_ Topic name: "enemy_info"
        

        

    private: //Private Member Functions
        void UpdateMyPose();
        void UpdateTime();
        void TransformGoalPoseQuaternion();
        void EnemyAlert();

        // callback for referee_hit_service_ Service name: "referee_hit_service"
        bool RefereeHitCB(icra_roboin_msgs::RefereeHit::Request& req, 
                            icra_roboin_msgs::RefereeHit::Response& resp);  
        // callback for referee_game_state_service_ Service name: "referee_game_state_service"
        bool RefereeGameStateCB(icra_roboin_msgs::RefereeGameState::Request& req,
                                 icra_roboin_msgs::RefereeGameState::Response& resp);
        // callback for referee_penalty_service_ Service name: "referee_penalty_service"                          
        bool RefereePenaltyCB(icra_roboin_msgs::RefereePenalty::Request& req, 
                            icra_roboin_msgs::RefereePenalty::Response& resp);  
        // callback for referee_buff_service_ Service name: "referee_buff_service"                      
        bool RefereeBuffCB(icra_roboin_msgs::RefereeBuff::Request& req,
                                 icra_roboin_msgs::RefereeBuff::Response& resp); 
        // callback for referee_reload_service_ Service name: "referee_reload_service"                      
        bool RefereeReloadCB(icra_roboin_msgs::RefereeReload::Request& req,
                                 icra_roboin_msgs::RefereeReload::Response& resp);
};






}
#endif


