#include "blackboard.h"




namespace icra_roboin_behavior{



Blackboard::Blackboard():  game_status(GameStatus::PRE_MATCH)
{
    ros::NodeHandle nh("~");

    tf_ptr_ = std::make_shared<tf::TransformListener>(ros::Duration(10));
    namespace_ = ros::this_node::getNamespace();
    namespace_.erase(0,namespace_.find_first_not_of("/")); // have to know that 1

    referee_game_status = nh.subscribe("game_status",1,&Blackboard::GameStatusCB,this);
    referee_game_result = nh.subscribe("game_result",1,&Blackboard::GameResultCB,this);
    referee_game_survivor = nh.subscribe("game_survivor",1,&Blackboard::GameSurvivorCB,this);
    referee_bonus_status = nh.subscribe("field_bonus_status",1,&Blackboard::BonusStatusCB,this);
    referee_supplier_status = nh.subscribe("field_supplier_status",1,&Blackboard::SupplierStatusCB,this);
    referee_robot_status = nh.subscribe("robot_status",1,&Blackboard::RobotStatusCB,this);
    referee_robot_heat = nh.subscribe("robot_heat",1,&Blackboard::RobotHeatCB,this);
    referee_robot_bonus = nh.subscribe("robot_bonus",1,&Blackboard::RobotBonusCB,this);
    referee_robot_damage = nh.subscribe("robot_damage",1,&Blackboard::RobotDamageCB,this);
    //referee_robot_shoot = nh.subscribe("robot_shoot",1,&Blackboard::RobotShootCB,this);
    //referee_projectile_supply = nh.subscribe("projectile_supply",1,&Blackboard::ProjectileSupplyCB,this);

	goal_set = nh.subscribe("goal_set", 1, &Blackboard::GoalSetCB, this);
	behavior_set = nh.subscribe("behavior_ser", 1, &Blackboard::BehaviorSetCB, this);


    enemy_detection_sub_ = nh.subscribe("enemy_info",5,&Blackboard::EnemyDetectionCB,this);



}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
////*                      callback function                       *///
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void Blackboard::GameStatusCB(const roborts_msgs::GameStatus::ConstPtr& msg){
    game_status = static_cast<icra_roboin_behavior::GameStatus>(msg->game_status);
    remaining_time = msg->remaining_time;
	time_passed_from_game_start = 180 - remaining_time;
}

void Blackboard::GameResultCB(const roborts_msgs::GameResult::ConstPtr& msg){
    game_result = static_cast<icra_roboin_behavior::GameResult>(msg->result);
}

void Blackboard::GameSurvivorCB(const roborts_msgs::GameSurvivor::ConstPtr& msg){
    if(my_id == RobotId::RED3){
        my_id = static_cast<icra_roboin_behavior::RobotId>(msg->red3);
        ally_id = static_cast<icra_roboin_behavior::RobotId>(msg->red4);
        enemy1_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue3);
        enemy2_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue4);

                my_teamtype = TeamType::RED_TEAM;
                ally_teamtype = TeamType::RED_TEAM;
                enemy1_teamtype = TeamType::BLUE_TEAM;
                enemy2_teamtype = TeamType::BLUE_TEAM;
    }
    else if(my_id == RobotId::RED4){
        my_id = static_cast<icra_roboin_behavior::RobotId>(msg->red4);
        ally_id = static_cast<icra_roboin_behavior::RobotId>(msg->red3);
        enemy1_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue3);
        enemy2_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue4);

                my_teamtype = TeamType::RED_TEAM;
                ally_teamtype = TeamType::RED_TEAM;
                enemy1_teamtype = TeamType::BLUE_TEAM;
                enemy2_teamtype = TeamType::BLUE_TEAM;
    }
    else if(my_id == RobotId::BLUE3){
        my_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue3);
        ally_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue4);
        enemy1_id = static_cast<icra_roboin_behavior::RobotId>(msg->red3);
        enemy2_id = static_cast<icra_roboin_behavior::RobotId>(msg->red4);

                my_teamtype = TeamType::BLUE_TEAM;
                ally_teamtype = TeamType::BLUE_TEAM;
                enemy1_teamtype = TeamType::RED_TEAM;
                enemy2_teamtype = TeamType::RED_TEAM;
    }
    else if(my_id == RobotId::BLUE4){
        my_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue4);
        ally_id = static_cast<icra_roboin_behavior::RobotId>(msg->blue3);
        enemy1_id = static_cast<icra_roboin_behavior::RobotId>(msg->red3);
        enemy2_id = static_cast<icra_roboin_behavior::RobotId>(msg->red4);

                my_teamtype = TeamType::BLUE_TEAM;
                ally_teamtype = TeamType::BLUE_TEAM;
                enemy1_teamtype = TeamType::RED_TEAM;
                enemy2_teamtype = TeamType::RED_TEAM;
    }
}


void Blackboard::BonusStatusCB(const roborts_msgs::BonusStatus::ConstPtr& msg){
    if(my_id == RobotId::RED3 || my_id == RobotId::RED4){
        my_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->red_bonus);
        ally_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->red_bonus);
        enemy1_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->blue_bonus);
        enemy2_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->blue_bonus);
		
                if (my_bonus_zone == BonusZone::OCCUPIED) {
			last_buff_time = time_passed_from_game_start;
		}

                if (enemy1_bonus_zone == BonusZone::OCCUPIED) {
			enemy_last_buff_time = time_passed_from_game_start;
		}

    }
    else if(my_id == RobotId::BLUE3 || my_id == RobotId::BLUE4){
        my_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->blue_bonus);
        ally_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->blue_bonus);
        enemy1_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->red_bonus);
        enemy2_bonus_zone = static_cast<icra_roboin_behavior::BonusZone>(msg->red_bonus);

                if (ally_bonus_zone == BonusZone::BEING_OCCUPIED) {
			last_buff_time = time_passed_from_game_start;
		}

                if (enemy1_bonus_zone == BonusZone::BEING_OCCUPIED) {
			enemy_last_buff_time = time_passed_from_game_start;
		}
    }
}

void Blackboard::SupplierStatusCB(const roborts_msgs::SupplierStatus::ConstPtr& msg){
    supplier_status = static_cast<icra_roboin_behavior::SupplierStatus>(msg->status);
        if (supplier_status == SupplierStatus::SUPPLYING) {
		last_supply_time = time_passed_from_game_start;
	}
}

void Blackboard::RobotStatusCB(const roborts_msgs::RobotStatus::ConstPtr& msg){
    my_id = static_cast<icra_roboin_behavior::RobotId>(msg->id);
    my_hp = msg->remain_hp;
    heat_cooling_rate = msg->heat_cooling_rate;
    gimbal_output = msg->gimbal_output;
    chassis_output = msg->chassis_output;
    shooter_output = msg->shooter_output;
}

void Blackboard::RobotHeatCB(const roborts_msgs::RobotHeat::ConstPtr& msg){
    chassis_volt = msg->chassis_volt;
    chassis_current = msg->chassis_current;
    chassis_power = msg->chassis_power;
    chassis_power_buffer = msg->chassis_power_buffer;
    shooter_heat = msg->shooter_heat;
}

void Blackboard::RobotBonusCB(const roborts_msgs::RobotBonus::ConstPtr& msg){
    robot_bonus = static_cast<icra_roboin_behavior::RobotBonus>(msg->bonus);
}

void Blackboard::RobotDamageCB(const roborts_msgs::RobotDamage::ConstPtr& msg){
    robot_damage_type = static_cast<icra_roboin_behavior::RobotDamageType>(msg->damage_type);
    robot_damage_armor = static_cast<icra_roboin_behavior::RobotDamageArmor>(msg->damage_source);
}

void Blackboard::GoalSetCB(const geometry_msgs::PoseStamped::ConstPtr& msg) {
	goal.header = msg->header;
	goal.pose = msg->pose;
}

void Blackboard::BehaviorSetCB(const std_msgs::Int32::ConstPtr& msg) {
        behavior_style = static_cast<icra_roboin_behavior::BehaviorStyle>(msg->data);
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                             */
/*                                        Get Interface                                        */
/*                                                                                             */
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////



/*   Referee Info Interface   */
        GameStatus Blackboard::GetGameStatus() const {

		return game_status;
	}

	int Blackboard::GetTimeGameRemaining() const {
		return remaining_time;
	}

	int Blackboard::GetTimePassedFromGameStart() {
		return time_passed_from_game_start;
	}

	BonusZone Blackboard::GetBonusZoneState() const {
                return my_bonus_zone;
	}

	int Blackboard::GetTimeLastBuffed() const {
		return last_buff_time;
	}

	int Blackboard::GetTimeLeftForBuffZoneToOnline() {
		return ((last_buff_time + 30) - time_passed_from_game_start);
	}

	BonusZone Blackboard::GetEnemyBonusZoneState() const {
                return enemy1_bonus_zone;
	}

	int Blackboard::GetEnemyTimeLastBuffed() const {
		return enemy_last_buff_time;
	}

	int Blackboard::GetEnemyTimeLeftForBuffZoneToOnline() {
		return ((enemy_last_buff_time + 30) - time_passed_from_game_start);
	}

	SupplierStatus Blackboard::GetIsSupplyZoneOnline() const {
		return supplier_status;
	}

	int Blackboard::GetTimeLastSupply() const {
		return last_supply_time;
	}
	int Blackboard::GetTimeLeftForSupplyZoneToOnline() {
		return ((last_supply_time + 30) - time_passed_from_game_start);
	}

	int Blackboard::GetMyHealth() const {
                return my_hp;
	}

	RobotDamageArmor Blackboard::GetWhichArmorHit() const {
                return robot_damage_armor;
	}

	RobotBonus Blackboard::GetRobotBonusState() const {
		return robot_bonus;
	}

	int Blackboard::GetTimeBuffLeft() {
		return (time_passed_from_game_start - last_buff_time);
	}

	int Blackboard::GetAmmo() const {
		return ammo;
	}

	geometry_msgs::PoseStamped Blackboard::GetAllyPose() const {
		return ally_pose_;
	}
	TeamType Blackboard::GetMyTeam() const {
                return my_teamtype;
	}
        RobotLife Blackboard::GetIsAllyAlive() const {
                return ally_life;
	}

	//////////////////////////////////
	   	  
/*   Perception Info Interface   */
const geometry_msgs::PoseStamped Blackboard::GetMyPose(){
    UpdateMyPose();
    return my_pose_;
} 
geometry_msgs::PoseStamped Blackboard::GetAllyPoseFromVision() const{
    return ally_pose_from_vision_;
}
geometry_msgs::PoseStamped Blackboard::GetEnemyPose(PlayerType who) const{
  switch(who){
      case PlayerType::ENEMY_ONE:
        return enemy_pose_1_ghost_;
      case PlayerType::ENEMY_TWO:
        return enemy_pose_2_ghost_;
      default:
        throw std::invalid_argument( "wrong enemy type" );
        ROS_ERROR("blackboard GetEnemyPose error: wrong enemy type");
  }
}
geometry_msgs::PoseStamped Blackboard::GetEnemyEstim(PlayerType who) const{
  switch(who){
      case PlayerType::ENEMY_ONE:
        return enemy_pose_1_estim_;
      case PlayerType::ENEMY_TWO:
        return enemy_pose_2_estim_;
      default:
        throw std::invalid_argument( "wrong enemy type" );
        ROS_ERROR("blackboard GetEnemyEstim error: wrong enemy type");
  }    
} 
int Blackboard::GetNumberOfDetectedEnemies() const{
    return number_of_detected_enemies_;
}
bool Blackboard::GetIsEnemyDetected(PlayerType who) const{
  switch(who){
      case PlayerType::ENEMY_ONE:
        return is_enemy_1_detected_;
      case PlayerType::ENEMY_TWO:
        return is_enemy_2_detected_;
      case PlayerType::ENEMY_ANY:
        return is_enemy_detected_;        
      default:
        throw std::invalid_argument( "wrong enemy type" );
        ROS_ERROR("blackboard GetIsEnemyDetected error: wrong enemy type");
  } 
}
PlayerType Blackboard::GetWhichEnemyDetected() const {
    if (is_enemy_1_detected_ && is_enemy_2_detected_){
        return PlayerType::ENEMY_ANY;
    } else if(is_enemy_1_detected_){
        return PlayerType::ENEMY_ONE;
    } else if(is_enemy_2_detected_){
        return PlayerType::ENEMY_TWO;
    } else {
        return PlayerType::ALLY;
    }
}
bool Blackboard::GetIsNewEnemy() const{
    return is_new_enemy_;
}
bool Blackboard::IsNewEnemy(){
    if(is_new_enemy_){
        is_new_enemy_ = false;
        return true;
    } else {
        return false;
    }    
}

ros::Time Blackboard::GetTimeLastSeen(PlayerType who) const{
    switch(who){
        case PlayerType::ALLY:
          return time_ally_last_seen_;
        case PlayerType::ENEMY_ONE:
          return time_enemy_1_last_seen_;
        case PlayerType::ENEMY_TWO:
          return time_enemy_2_last_seen_;
        case PlayerType::ENEMY_ANY:
          return time_enemy_last_seen_;
        case PlayerType::UNKNOWN:
          return time_unknown_last_seen_;
        default:
          return ros::Time(0);
    }
}


/////////////////////////////

geometry_msgs::PoseStamped Blackboard::GetGoal() const{
    return goal;
}

BehaviorStyle Blackboard::GetBehaviorStyle() const{
    return behavior_style;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                             */
/*                                        Set Interface                                        */
/*                                                                                             */
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

void Blackboard::AmmoMinusOne() {
    ammo--;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                             */
/*                                      Internal Members                                       */
/*                                                                                             */
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
void Blackboard::UpdateMyPose(){
    tf::Stamped<tf::Pose> my_tf_pose;
    my_tf_pose.setIdentity();
    my_tf_pose.frame_id_=namespace_ + "/" + "base_link";
    my_tf_pose.stamp_=ros::Time(0);   
    try {
        geometry_msgs::PoseStamped my_pose;
        tf::poseStampedTFToMsg(my_tf_pose,my_pose);
        tf_ptr_ -> transformPose(namespace_ + "/" + "map", my_pose, my_pose_);
    }
    catch (tf::LookupException& ex) {
        ROS_ERROR("blackboard UpdateMyPose error :%s", ex.what());
    }
}





/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                             */
/*                                          Callbacks                                          */
/*                                                                                             */
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

void Blackboard::EnemyDetectionCB(const icra_roboin_msgs::YoloDetectionInfo::ConstPtr& yolo){
    //TODO change camera frame id from base_link to camera link
    if (yolo->number_of_detection != 0){
        number_of_detection_ = yolo->number_of_detection;
        number_of_detected_enemies_ = 0;
        is_enemy_detected_ = false;

        //////////////////////////////////////////////////////////
        /*                         Ally                         */
        //////////////////////////////////////////////////////////

        if(yolo->enemy_detected[0] == 1){
            is_ally_detected_ = true;
            time_ally_last_seen_ = yolo->stamp;

            //tf transform code
            tf::Stamped<tf::Pose> ally_cam_tf, ally_global_tf;
            geometry_msgs::PoseStamped ally_cam_pose, ally_global_pose;
            ally_cam_pose.header.frame_id=namespace_ + "/" +"base_link";
            ally_cam_pose.header.stamp = yolo->stamp;
            ally_cam_pose.pose.position.z = (float(yolo->distance[0])+ROBOT_PERIMETER)/1000 * std::sin((float(yolo->angle_verti[0]) / 100)*3.141592/180);
            double flat_d =( (float(yolo->distance[0])+ROBOT_PERIMETER)/1000 * std::cos((float(yolo->angle_verti[0]) / 100)*3.141592/180) ); 
            ally_cam_pose.pose.position.x = flat_d * std::cos((-1*float(yolo->angle_hori[0]) / 100)*3.141592/180);
            ally_cam_pose.pose.position.y = flat_d * std::sin((-1*float(yolo->angle_hori[0]) / 100)*3.141592/180);

            tf::Quaternion quaternion = tf::createQuaternionFromYaw((-1*float(yolo->angle_hori[0]) / 100)*3.141592/180);
            ally_cam_pose.pose.orientation.w=quaternion.w();
            ally_cam_pose.pose.orientation.x=quaternion.x();
            ally_cam_pose.pose.orientation.y=quaternion.y();
            ally_cam_pose.pose.orientation.z=quaternion.z();

            tf::poseStampedMsgToTF(ally_cam_pose, ally_cam_tf);
            ally_cam_tf.stamp_ = ros::Time(0);
            try
            {
                tf_ptr_->transformPose(namespace_ + "/" +"map",ally_cam_tf,ally_global_tf);
                tf::poseStampedTFToMsg(ally_global_tf,ally_global_pose);
                ally_pose_from_vision_ = ally_global_pose;
            }
            catch (tf::TransformException& ex) {
                ROS_ERROR("blackboard enemy detection callback tf error");
            }
        } else {
            is_ally_detected_ = false;
        }
        

        //////////////////////////////////////////////////////////
        /*                       Enemy 1                        */
        //////////////////////////////////////////////////////////
        if(yolo->enemy_detected[1] == 1){
            if(is_enemy_1_detected_ != true){
                is_new_enemy_ = true;
            }
            is_enemy_detected_ = true;
            is_enemy_1_detected_ = true;
            time_enemy_last_seen_ = yolo->stamp;
            time_enemy_1_last_seen_ = yolo->stamp;
            //ROS_INFO("Enemy 1 Detected!");
            number_of_detected_enemies_++;
            //tf transform code
            tf::Stamped<tf::Pose> enemy1_cam_tf, enemy1_global_tf;
            geometry_msgs::PoseStamped enemy1_cam_pose, enemy1_global_pose;
            enemy1_cam_pose.header.frame_id=namespace_ + "/" +"base_link";
            enemy1_cam_pose.header.stamp = yolo->stamp;
            enemy1_cam_pose.pose.position.z = (float(yolo->distance[1])+ROBOT_PERIMETER)/1000 * std::sin((float(yolo->angle_verti[1]) / 100)*3.141592/180);
            double flat_d = ( (float(yolo->distance[1])+ROBOT_PERIMETER)/1000 * std::cos((float(yolo->angle_verti[1]) / 100)*3.141592/180) ) ;   
            enemy1_cam_pose.pose.position.x = flat_d * std::cos((-1*float(yolo->angle_hori[1]) / 100)*3.141592/180);
            enemy1_cam_pose.pose.position.y = flat_d * std::sin((-1*float(yolo->angle_hori[1]) / 100)*3.141592/180);

            tf::Quaternion quaternion = tf::createQuaternionFromYaw((-1*float(yolo->angle_hori[1]) / 100)*3.141592/180);
            enemy1_cam_pose.pose.orientation.w=quaternion.w();
            enemy1_cam_pose.pose.orientation.x=quaternion.x();
            enemy1_cam_pose.pose.orientation.y=quaternion.y();
            enemy1_cam_pose.pose.orientation.z=quaternion.z();

            tf::poseStampedMsgToTF(enemy1_cam_pose, enemy1_cam_tf);
            enemy1_cam_tf.stamp_ = ros::Time(0);
            try
            {
                tf_ptr_->transformPose(namespace_ + "/" +"map",enemy1_cam_tf,enemy1_global_tf);
                tf::poseStampedTFToMsg(enemy1_global_tf,enemy1_global_pose);
                enemy_pose_1_ = enemy1_global_pose;
                enemy_pose_1_ghost_ = enemy_pose_1_;
            }
            catch (tf::TransformException& ex) {
                ROS_ERROR("blackboard enemy detection callback tf error");
            }

            
        } else {
            is_enemy_1_detected_ = false;
        }
        


        //////////////////////////////////////////////////////////
        /*                       Enemy 2                        */
        //////////////////////////////////////////////////////////
        if(yolo->enemy_detected[2]==1){
            if(is_enemy_1_detected_ != true){
                is_new_enemy_ = true;
            }
            is_enemy_detected_ = true;
            is_enemy_2_detected_ = true;
            time_enemy_last_seen_ = yolo->stamp;
            time_enemy_2_last_seen_ = yolo->stamp;
            //ROS_INFO("Enemy 2 Detected!");
            number_of_detected_enemies_++;
            //tf transform code
            tf::Stamped<tf::Pose> enemy2_cam_tf, enemy2_global_tf;
            geometry_msgs::PoseStamped enemy2_cam_pose, enemy2_global_pose;
            enemy2_cam_pose.header.frame_id=namespace_ + "/" +"base_link";
            enemy2_cam_pose.header.stamp = yolo->stamp;
            enemy2_cam_pose.pose.position.z = (float(yolo->distance[2])+ROBOT_PERIMETER)/1000 * std::sin((float(yolo->angle_verti[2]) / 100)*3.141592/180);
            double flat_d =( (float(yolo->distance[1])+ROBOT_PERIMETER)/1000 * std::cos((float(yolo->angle_verti[2]) / 100)*3.141592/180) );  
            enemy2_cam_pose.pose.position.x = flat_d * std::cos((-1*float(yolo->angle_hori[2]) / 100)*3.141592/180);
            enemy2_cam_pose.pose.position.y = flat_d * std::sin((-1*float(yolo->angle_hori[2]) / 100)*3.141592/180);

            tf::Quaternion quaternion = tf::createQuaternionFromYaw((-1*float(yolo->angle_hori[2]) / 100)*3.141592/180);
            enemy2_cam_pose.pose.orientation.w=quaternion.w();
            enemy2_cam_pose.pose.orientation.x=quaternion.x();
            enemy2_cam_pose.pose.orientation.y=quaternion.y();
            enemy2_cam_pose.pose.orientation.z=quaternion.z();

            tf::poseStampedMsgToTF(enemy2_cam_pose, enemy2_cam_tf);
            enemy2_cam_tf.stamp_ = ros::Time(0);
            try
            {
                tf_ptr_->transformPose(namespace_ + "/" +"map",enemy2_cam_tf,enemy2_global_tf);
                tf::poseStampedTFToMsg(enemy2_global_tf,enemy2_global_pose);
                enemy_pose_2_ = enemy2_global_pose;
                enemy_pose_2_ghost_ = enemy_pose_2_;
            }
            catch (tf::TransformException& ex) {
                ROS_ERROR("blackboard enemy detection callback tf error");
            }

            
        } else {
            is_enemy_2_detected_ = false;
        }
        
        

    } else {
        is_ally_detected_ = false;
        is_enemy_detected_ = false;
        is_enemy_1_detected_ = false;
        is_enemy_2_detected_ = false;
        number_of_detected_enemies_ = 0;
        number_of_detection_ = 0;
    }
}

geometry_msgs::PoseStamped Blackboard::transform_goal() {
	real_goal.header = goal.header;
	real_goal.pose.position = goal.pose.position;
	double distance_x = real_goal.pose.position.x - my_pose_.pose.position.x;
	double distance_y = real_goal.pose.position.y - my_pose_.pose.position.y;
        double distance = icra_roboin_behavior::tools::GetPlanarDistance(real_goal, my_pose_);
	real_goal.pose.orientation.w = 0;
	real_goal.pose.orientation.x = distance_x/distance;
	real_goal.pose.orientation.y = distance_y/distance;
	real_goal.pose.orientation.z = 0;

	return real_goal;
}



}
