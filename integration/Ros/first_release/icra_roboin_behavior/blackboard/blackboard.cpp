#include "blackboard.h"





namespace icra_roboin_behavior{



Blackboard::Blackboard(TeamType team = TeamType::BLUE_TEAM, RuleType rule = RuleType::SOLO): 
                            my_team_(team), game_rule_(rule), game_state_(GameState::READY), 
                            ammo_(START_AMMO), my_health_(START_HEALTH), is_ally_alive_(true),
                            enemy_priority_(PlayerType::ENEMY_ANY), locked_on_enemy_(PlayerType::ALLY), //do not lockon
                            behavior_style_(icra_roboin_behavior::BehaviorStyle::READY),
                            behavior_process_(icra_roboin_behavior::BehaviorProcess::IDLE)
{
    ros::NodeHandle nh;
    enemy_detection_sub_ = nh.subscribe("enemy_info",5,&Blackboard::EnemyDetectionCB,this);
    tf_ptr_ = std::make_shared<tf::TransformListener>(ros::Duration(10));
    namespace_ = ros::this_node::getNamespace();
    namespace_.erase(0,namespace_.find_first_not_of("/"));

    referee_hit_service_ = nh.advertiseService("referee_hit_service",&Blackboard::RefereeHitCB,this);
    referee_game_state_service_ = nh.advertiseService("referee_game_state_service",&Blackboard::RefereeGameStateCB,this);
    referee_penalty_service_ = nh.advertiseService("referee_penalty_service",&Blackboard::RefereePenaltyCB,this);
    referee_buff_service_ = nh.advertiseService("referee_buff_service",&Blackboard::RefereeBuffCB,this);
    referee_reload_service_ = nh.advertiseService("referee_reload_service",&Blackboard::RefereeReloadCB,this);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                             */
/*                                        Get Interface                                        */
/*                                                                                             */
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/*   Referee Info Interface   */

//Game State Info
ros::Time Blackboard::GetTimeGameStarted() const{
    return time_game_started_;
}  
const ros::Duration Blackboard::GetTimePassedFromGameStart() {
    UpdateTime();
    return time_passed_from_game_start_;
}  
GameState Blackboard::GetGameState() const{
    return game_state_;
}
//Zone Info
bool Blackboard::GetIsBuffZoneOnline() const{
    return is_buff_zone_online_;
}
ros::Time Blackboard::GetTimeLastBuffed() const{
    return time_last_buffed_;
}  
const ros::Duration Blackboard::GetTimeLeftForBuffZoneToOnline() {
    UpdateTime();
    return time_left_for_buff_zone_to_online_;
}  
bool Blackboard::GetIsReloadZoneOnline() const{
    return is_reload_zone_online_;
}
ros::Time Blackboard::GetTimeLastReloaded() const{
    return time_last_reloaded_;
}  
const ros::Duration Blackboard::GetTimeLeftForReloadZoneToOnline() {
    UpdateTime();
    return time_left_for_reload_zone_to_online_;
}  
//HP Info
int Blackboard::GetMyHealth() const{
    return my_health_;
}
bool Blackboard::GetIsHitFastResponse() const{
    return is_hit_fast_response_;
}
bool Blackboard::GetHitConfirmedFastResponse() const{
    return hit_confirmed_fast_response_;
} 
void Blackboard::ConfirmHitFastResponse(){
    is_hit_fast_response_ = false;
    hit_confirmed_fast_response_ = true;
}
bool Blackboard::GetIsHitSmartResponse() const{
    return is_hit_smart_response_;
} 
bool Blackboard::GetHitConfirmedSmartResponse() const{
    return hit_confirmed_smart_response_;
} 
void Blackboard::ConfirmHitSmartResponse(){
    is_hit_smart_response_ = false;
    hit_confirmed_smart_response_ = true;
}
ArmorType Blackboard::GetWhichArmorHit() const {
    return which_armor_hit_;
}  
ros::Time Blackboard::GetTimeLastHit() const{
    return time_last_hit_;
}  
//Defense Buff Info
bool Blackboard::GetHasBuff() const{
    return has_buff_;
}
const ros::Duration Blackboard::GetTimeBuffLeft() {
    UpdateTime();
    return time_buff_left_;
} 
//Ammunition Info
int Blackboard::GetAmmo() const{
    return ammo_;
}
bool Blackboard::GetIsReloading() const{
    return is_reloading_;
}

/*   Team Info Interface   */
geometry_msgs::PoseStamped Blackboard::GetAllyPose() const{
    return ally_pose_;
}
TeamType Blackboard::GetMyTeam() const{
    return my_team_;
}
bool Blackboard::GetIsAllyAlive() const{
    return is_ally_alive_;
}

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

/*   Behavior Info Interface   */
PlayerType Blackboard::GetLockedOnEnemy() const{
    return locked_on_enemy_;
}
bool Blackboard::GetIsNewLockonTarget() const{
    return is_new_lockon_target_;
}
bool Blackboard::IsNewLockonTarget(){
    if(is_new_lockon_target_){
        is_new_lockon_target_ = false;
        return true;
    } else {
        return false;
    }
}
bool Blackboard::GetIsNewGoal() const{
    return is_new_goal_;
}
bool Blackboard::IsNewGoal(){
    if(is_new_goal_){
        is_new_goal_ = false;
        return true;
    } else {
        return false;
    }
}
icra_roboin_msgs::GoalDescription Blackboard::GetGoal() const{
    return goal_;
}
const geometry_msgs::PoseStamped Blackboard::GetGoalPoseQuaternion(){
    TransformGoalPoseQuaternion();
    return goal_pose_quaternion_;    
}

BehaviorStyle Blackboard::GetBehaviorStyle() const{
    return behavior_style_;
}
BehaviorProcess Blackboard::GetBehaviorProcess() const{
    return behavior_process_;
}

/*   Smart Decision and Tactics Info Interface   */
PlayerType Blackboard::GetEnemyPriority() const{
    return enemy_priority_;
}






/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                             */
/*                                        Set Interface                                        */
/*                                                                                             */
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

void Blackboard::SetGoal(const icra_roboin_msgs::GoalDescription new_goal){
    goal_ = new_goal;
    is_new_goal_ = true;
}
void Blackboard::SetBehaviorStyle(const BehaviorStyle new_style){
    behavior_style_ = new_style;
}
void Blackboard::SetBehaviorProcess(const BehaviorProcess process){
    behavior_process_ = process;
}

void Blackboard::SetEnemyPriority(const PlayerType who){
    enemy_priority_ = who;
}

void Blackboard::SetLockedOnEnemy(const PlayerType who) {
    if(who != PlayerType::ALLY && who != PlayerType::ENEMY_ONE && who != PlayerType::ENEMY_TWO && who != PlayerType::ENEMY_ANY && who != PlayerType::UNKNOWN){
        throw std::invalid_argument( "wrong enemy type" );
        ROS_ERROR("blackboard set enenmy lockon error: wrong enemy type");
    }
    locked_on_enemy_ = who;
}

void Blackboard::AmmoMinusOne() {
    ammo_ --;
}

void Blackboard::SetIsReloading(const bool flag) {
    is_reloading_ = flag;
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
void Blackboard::UpdateTime(){
    time_passed_from_game_start_ = ros::Time::now() - time_game_started_;
    if(is_buff_zone_online_){
        time_left_for_buff_zone_to_online_ = ros::Duration(0);
    } else {
        time_left_for_buff_zone_to_online_ = ros::Duration(60)-ros::Duration((time_passed_from_game_start_.sec % 60),time_passed_from_game_start_.nsec) ; //buffzone opens every 1min
    }
    time_buff_left_ = ros::Duration(BUFF_DURATION) + (time_last_buffed_-ros::Time::now());
    if(time_buff_left_.toSec() <= 0){
        time_buff_left_ = ros::Duration(0);
    }
    time_left_for_reload_zone_to_online_ = ros::Duration(RELOADING_DURATION) + (time_last_buffed_-ros::Time::now());
    if(time_left_for_reload_zone_to_online_.toSec() <= 0){
        time_left_for_reload_zone_to_online_ = ros::Duration(0);
    }
}
void Blackboard::TransformGoalPoseQuaternion(){
    goal_pose_quaternion_.header = goal_.header;
    goal_pose_quaternion_.pose.position.x = goal_.x;
    goal_pose_quaternion_.pose.position.y = goal_.y;
    goal_pose_quaternion_.pose.position.z = 1;
    goal_pose_quaternion_.pose.orientation = tf::createQuaternionMsgFromYaw(goal_.yaw);
}



void Blackboard::EnemyAlert(){
    //TODO
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                             */
/*                                          Callbacks                                          */
/*                                                                                             */
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

bool Blackboard::RefereeHitCB(icra_roboin_msgs::RefereeHit::Request& req, 
                    icra_roboin_msgs::RefereeHit::Response& resp){
    is_hit_fast_response_ = true;
    is_hit_smart_response_ = true;
    time_last_hit_ = req.header.stamp;
    my_health_ -= req.damage;
    if(my_health_ != req.your_hp) ROS_WARN("blackboard: referee hp and blackboard hp is different!");
    which_armor_hit_ = static_cast<ArmorType>(req.which_armor);
    resp.success = true;
    return true;
}


bool Blackboard::RefereeGameStateCB(icra_roboin_msgs::RefereeGameState::Request& req,
                            icra_roboin_msgs::RefereeGameState::Response& resp){
    GameState tmp = game_state_;
    game_state_ = static_cast<GameState>(req.game_state);
    //ROS_WARN("%d, %d",int(tmp),int(game_state_));
    if( tmp == GameState::READY && game_state_ == GameState::PLAY ){
        //ROS_WARN("called!!");
        time_game_started_ = req.header.stamp;
        time_passed_from_game_start_ = ros::Duration(0);
        my_health_=START_HEALTH;
        ammo_=START_AMMO;
    }
    resp.success = true;
    return true;
}
                       
bool Blackboard::RefereePenaltyCB(icra_roboin_msgs::RefereePenalty::Request& req, 
                    icra_roboin_msgs::RefereePenalty::Response& resp){
    penalty_received_ = static_cast<PenaltyType>(req.penalty);
    my_health_ -= req.damage;
    resp.success = true;
    return true;
}  
                     
bool Blackboard::RefereeBuffCB(icra_roboin_msgs::RefereeBuff::Request& req,
                            icra_roboin_msgs::RefereeBuff::Response& resp){
    if(req.buff_type == 0){
        time_last_buffed_ = req.header.stamp;
    }
    resp.success = true;
    return true;
}

bool Blackboard::RefereeReloadCB(icra_roboin_msgs::RefereeReload::Request& req,
                            icra_roboin_msgs::RefereeReload::Response& resp){
    is_reloading_ = false;
    ammo_ = START_AMMO;
    time_last_reloaded_ = req.header.stamp;
    resp.success = true;
    return true;
}


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
            EnemyAlert();
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
            
            if(GetEnemyPriority() == PlayerType::ENEMY_ONE | GetEnemyPriority() == PlayerType::ENEMY_ANY) {
                SetLockedOnEnemy(PlayerType::ENEMY_ONE);
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
            EnemyAlert();
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
            
            if(GetEnemyPriority() == PlayerType::ENEMY_TWO | GetEnemyPriority() == PlayerType::ENEMY_ANY) {
                SetLockedOnEnemy(PlayerType::ENEMY_TWO);
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















}