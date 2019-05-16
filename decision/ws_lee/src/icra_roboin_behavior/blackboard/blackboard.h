#ifndef ICRA_ROBOIN_BEHAVIOR_BLACKBOARD_H
#define ICRA_ROBOIN_BEHAVIOR_BLACKBOARD_H


#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int32.h>
#include <math.h>
#include "../tools.h"
#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include "../enums.h"
#include "../constants.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int32.h"
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include "std_srvs/SetBool.h"

#include "roborts_msgs/GameStatus.h"
#include "roborts_msgs/GameResult.h"
#include "roborts_msgs/GameSurvivor.h"
#include "roborts_msgs/BonusStatus.h"
#include "roborts_msgs/SupplierStatus.h"
#include "roborts_msgs/RobotStatus.h"
#include "roborts_msgs/RobotHeat.h"
#include "roborts_msgs/RobotBonus.h"
#include "roborts_msgs/RobotDamage.h"
#include "roborts_msgs/RobotShoot.h"
#include "roborts_msgs/ProjectileSupply.h"

#include "icra_roboin_msgs/BlackboardGeneralInfo.h"


#include "icra_roboin_msgs/YoloDetectionInfo.h"




namespace icra_roboin_behavior {




class Blackboard {

    public: //Interfaces
        Blackboard();
        ~Blackboard() = default;

 

	

	


///////////////////////////   callback function   ////////////////////////////////
    private:
        std::string b;
        ros::Subscriber referee_game_status;
        ros::Subscriber referee_game_result;
        ros::Subscriber referee_game_survivor;
        ros::Subscriber referee_bonus_status;
        ros::Subscriber referee_supplier_status;
        ros::Subscriber referee_robot_status;
        ros::Subscriber referee_robot_heat;
        ros::Subscriber referee_robot_bonus;
        ros::Subscriber referee_robot_damage;
        //ros::Subscriber referee_robot_shoot;
        //ros::Subscriber referee_projectile_supply; // need more test

        ros::Subscriber goal_set;
        
        ros::ServiceServer decision_getinfo;

        ros::Subscriber my_pose_setting;

        //ros::ServiceServer behavior_set;
        ros::Subscriber behavior_set;

        void GameStatusCB(const roborts_msgs::GameStatus::ConstPtr& msg);
        void GameResultCB(const roborts_msgs::GameResult::ConstPtr& msg);
        void GameSurvivorCB(const roborts_msgs::GameSurvivor::ConstPtr& msg);
        void BonusStatusCB(const roborts_msgs::BonusStatus::ConstPtr& msg);
        void SupplierStatusCB(const roborts_msgs::SupplierStatus::ConstPtr& msg);
        void RobotStatusCB(const roborts_msgs::RobotStatus::ConstPtr& msg);
        void RobotHeatCB(const roborts_msgs::RobotHeat::ConstPtr& msg);
        void RobotBonusCB(const roborts_msgs::RobotBonus::ConstPtr& msg);
        void RobotDamageCB(const roborts_msgs::RobotDamage::ConstPtr& msg);
        //void RobotShootCB(const roborts_msgs::RobotShoot::ConstPtr& msg);
        //void ProjectileSupplyCB(const roborts_msgs::ProjectileSupply::ConstPtr& msg);

        void GoalSetCB(const geometry_msgs::PoseStamped::ConstPtr& msg);
        
        void EnemyDetectionCB(const icra_roboin_msgs::YoloDetectionInfo::ConstPtr& yolo);  // callback for detection_sub_ Topic name: "enemy_info"
        bool DecisionGetinfoCB(icra_roboin_msgs::BlackboardGeneralInfo::Request& request, icra_roboin_msgs::BlackboardGeneralInfo::Response& response);
	
        void MyPoseCB(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
        //bool BehaviorSetCB(std_srvs::SetBool::Request& req, std_srvs::SetBool::Response& res);
        void BehaviorSetCB(const std_msgs::Int32::ConstPtr& msg);
//////////////////////////////////////////////////
//////////*         game info        *////////////
//////////////////////////////////////////////////
		
////////////////      robot info      /////////////
              private:  RobotId my_id = RobotId::RED3;
                        RobotLife my_life = RobotLife::ALIVE;
                        TeamType my_teamtype = TeamType::RED_TEAM;
                        RobotDamageType robot_damage_type = RobotDamageType::ARMOR;
                        RobotDamageArmor robot_damage_armor = RobotDamageArmor::FORWARD;
                        BonusZone my_bonus_zone = BonusZone::UNOCCUPIED;
                        int my_hp = 200;

                        bool gimbal_output = 1;
                        bool chassis_output = 1;
                        bool shooter_output = 1;

                        int chassis_volt = 0;
                        int chassis_current = 0;
                        float chassis_power = 0;
                        int chassis_power_buffer = 0;
                        int shooter_heat = 0;
                        int heat_cooling_rate = 0;


                        RobotId ally_id = RobotId::RED4;
                        RobotLife ally_life = RobotLife::ALIVE;
                        BonusZone ally_bonus_zone = BonusZone::UNOCCUPIED;
                        TeamType ally_teamtype = TeamType::RED_TEAM;


                        RobotId enemy1_id = RobotId::BLUE3;
                        RobotLife enemy1_life = RobotLife::ALIVE;
                        BonusZone enemy1_bonus_zone = BonusZone::UNOCCUPIED;
                        TeamType enemy1_teamtype = TeamType::BLUE_TEAM;


                        RobotId enemy2_id = RobotId::BLUE4;
                        RobotLife enemy2_life = RobotLife::ALIVE;
                        BonusZone enemy2_bonus_zone = BonusZone::UNOCCUPIED;
                        TeamType enemy2_teamtype = TeamType::BLUE_TEAM;

   /* public:

                class my_info {
                public:

                        my_info();
                        ~my_info() = default;

                        static RobotId my_id;
                        static RobotLife my_life;
                        static TeamType teamtype;
                        static RobotDamageType robot_damage_type;
                        static RobotDamageArmor robot_damage_armor;
                        static BonusZone ally_bonus_zone;
                        static int my_hp;

                        static bool gimbal_output;
                        static bool chassis_output;
                        static bool shooter_output;

                        static int chassis_volt;
                        static int chassis_current;
                        static float chassis_power;
                        static int chassis_power_buffer;
                        static int shooter_heat;
                        static int heat_cooling_rate;

                };

                class ally_info {
                public:

                        ally_info();
                        ~ally_info() = default;

                        static RobotId ally_id;
                        static RobotLife ally_life;
                        static BonusZone ally_bonus_zone;
                        static TeamType teamtype;

                };

                class enemy1_info {
                public:

                        enemy1_info();
                        ~enemy1_info() = default;

                        static RobotId enemy1_id;
                        static RobotLife enemy1_life;
                        static BonusZone enemy_bonus_zone;
                        static TeamType teamtype;
                };

                class enemy2_info {
                public:

                        enemy2_info();
                        ~enemy2_info() = default;

                        static RobotId enemy2_id;
                        static RobotLife enemy2_life;
                        static BonusZone enemy_bonus_zone;
                        static TeamType teamtype;
                };*/

	private:

                GameStatus game_status = GameStatus::PRE_MATCH;
                RobotBonus robot_bonus = RobotBonus::BUFF_OFF;
                GameResult game_result;
                SupplierStatus supplier_status = SupplierStatus::CLOSE;

                int heat_cooling_limit = 0;
                int robot_max_hp = 0;

                int remaining_time = 0;
                int time_passed_from_game_start = 0;

                int last_buff_time = 0;
                int last_supply_time = 0;

                int enemy_last_buff_time = 0;

                int ammo = 50;

		geometry_msgs::PoseStamped goal;
		geometry_msgs::PoseStamped real_goal;
		BehaviorStyle behavior_style;



		


        //bool projectile_supply=0;


	private: //Team Info

		geometry_msgs::PoseStamped ally_pose_;

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

		bool is_ally_detected_ = false;
		bool is_enemy_1_detected_ = false;
		bool is_enemy_2_detected_ = false;
		bool is_enemy_detected_ = false;
		bool is_unknown_detected_ = false;

		bool is_new_enemy_ = false;





//////////////////////////////////////////////////
//////////*    game info interface   *////////////
//////////////////////////////////////////////////
///
        public:
        //game state
        GameStatus GetGameStatus() const;

        //game time
        int GetTimeGameRemaining() const;
        int GetTimePassedFromGameStart();

        //buff zone
        BonusZone GetBonusZoneState() const;
        int GetTimeLastBuffed() const;
        int GetTimeLeftForBuffZoneToOnline();
        BonusZone GetEnemyBonusZoneState() const;
        int GetEnemyTimeLastBuffed() const;
        int GetEnemyTimeLeftForBuffZoneToOnline();

        //supplier zone
        SupplierStatus GetIsSupplyZoneOnline() const;
        int GetTimeLastSupply() const;
        int GetTimeLeftForSupplyZoneToOnline();

        //HP
        int GetMyHealth() const;

        //damaged armor
        RobotDamageArmor GetWhichArmorHit() const;

        //buff
        RobotBonus GetRobotBonusState() const;
        int GetTimeBuffLeft();
        //ammo
        int GetAmmo() const;////////////////////\BF\A9\B1\E2\B1\EE\C1\F6 th

		/*   Team Info Interface   */
		geometry_msgs::PoseStamped GetAllyPose() const;
		TeamType GetMyTeam() const;
                RobotLife GetIsAllyAlive() const;


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
///*                      vision                         *///
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
		
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
        
		/*   behavior interface   */
		geometry_msgs::PoseStamped GetGoal() const; // goal for current behavior
        BehaviorStyle GetBehaviorStyle() const;
        
       /*   External Set Interface   */
        void AmmoMinusOne();
///////////////////////////////////////////////////////////////////////






///////////////////Techincal//////////////////////////



    private: //Resources
        std::shared_ptr<tf::TransformListener> tf_ptr_;
        ros::Subscriber enemy_detection_sub_;  // receives Yolo detection result.   Topic name:"enemy_info"
        std::string namespace_;  // ROS namespace of this node

   	

    private: //Private Member Functions
        void UpdateMyPose();

    public:
        geometry_msgs::PoseStamped transform_goal();
};






}
#endif


