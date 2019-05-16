#include "behavior_interface.h"

namespace icra_roboin_behavior {

BehaviorInterface::BehaviorInterface(ChassisExecutor*& chassis_executor,
                    GimbalExecutor*& gimbal_executor,
                    LockonModule*& lockon_module,
                    Blackboard*& blackboard,
                    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>>& behavior_factory): 
                                                                    chassis_executor_(chassis_executor),
                                                                    gimbal_executor_(gimbal_executor),
                                                                    lockon_module_(lockon_module),
                                                                    blackboard_(blackboard),
                                                                    behavior_factory_(behavior_factory)
                                                                    
{
  ros::NodeHandle nh("~");

  
  set_behavior_style_service_ = nh.advertiseService("behavior_select_service",&BehaviorInterface::SetBehaviorStyleCB,this);
  set_goal_service_ = nh.advertiseService("goal_select_service",&BehaviorInterface::SetBehaviorGoalCB,this);
  set_enemy_priority_service_ = nh.advertiseService("set_enemy_priority_service",&BehaviorInterface::SetEnemyPriorityCB,this);
  general_info_server_ = nh.advertiseService("blackboard/general_info_service",&BehaviorInterface::GetGeneralInfoServiceCB,this);
  confirm_hit_server_ = nh.advertiseService("confirm_hit_service",&BehaviorInterface::ConfirmHitServiceCB,this);
  ammo_consume_server_ = nh.advertiseService("ammo_consume_service",&BehaviorInterface::AmmoConsumeServiceCB,this);

  //referee_shoot_service_ = nh.advertiseService("referee_shoot_service",&BehaviorInterface::RefereeShootCB,this);
  //referee_tag_service_ = nh.advertiseService("referee_tag_service",&BehaviorInterface::RefereeTagCB,this);
}

bool BehaviorInterface::SetBehaviorStyleCB(icra_roboin_msgs::BehaviorStyleSet::Request &req,
                                           icra_roboin_msgs::BehaviorStyleSet::Response &res) 
{
  auto new_behavior = static_cast<BehaviorStyle>(req.behavior);
  BehaviorStyle current_behavior = blackboard_->GetBehaviorStyle();
  if (current_behavior == new_behavior){
    res.success = true;
    res.info = int(SetBehaviorServiceInfo::ALREADY_THAT_BEHAVIOR);
  } else {
    for(auto behav: behavior_factory_){
      if(behav->GetBehaviorStyle() == current_behavior){
        if( behav->Cancel() ){  // cancel current behavior
          res.success = true;
          res.info = int(SetBehaviorServiceInfo::SUCCESS);
          ROS_INFO("Behavior Interface Set Behavior : successfully canceled behavior");
          break;
        } else {
          if(behav->Update()==BehaviorProcess::BUSY){
            res.success = false;
            res.info = int(SetBehaviorServiceInfo::FAIL_BEHAVIOR_BUSY);
            ROS_INFO("Behavior Interface Set Behavior fail : behavior busy");
          } else {
            res.success = false;
            res.info = int(SetBehaviorServiceInfo::FAIL_UNKNOWN);
            ROS_INFO("Behavior Interface Set Behavior fail : behavior busy");
          }
          return true;
        }
      }
    

    }
  }
  blackboard_->SetBehaviorStyle(new_behavior); //sets new behavior
  ROS_INFO("Behavior Interface Set Behavior : successfully set new behavior");
  return true;
}

bool BehaviorInterface::SetBehaviorGoalCB(icra_roboin_msgs::SetGoal_2::Request &req, icra_roboin_msgs::SetGoal_2::Response &res) {
  for(auto behav: behavior_factory_){
      if(behav->GetBehaviorStyle() == blackboard_->GetBehaviorStyle()){
        behav->Cancel();
        break;
      }
  }
  blackboard_ -> SetGoal(req.goal);
  res.success = true;
  res.info = 0;
  return true;
}

bool BehaviorInterface::SetEnemyPriorityCB(icra_roboin_msgs::SetEnemyPriority::Request &req, icra_roboin_msgs::SetEnemyPriority::Response &res) {
  blackboard_-> SetEnemyPriority( static_cast<PlayerType>(req.enemy_priority) );
  res.success = true;
  res.info = 0; 
  return true;
}
bool BehaviorInterface::ConfirmHitServiceCB(icra_roboin_msgs::ConfirmHit::Request& req, 
                                icra_roboin_msgs::ConfirmHit::Response& resp)
{
  blackboard_->ConfirmHitSmartResponse();
  resp.success = true;
  return true;
}

bool BehaviorInterface::AmmoConsumeServiceCB(icra_roboin_msgs::AmmoConsume::Request& req, 
                                icra_roboin_msgs::AmmoConsume::Response& resp)
{
  for(int i=0;i<req.shots;i++){
    blackboard_->AmmoMinusOne();
  }
  resp.success = true;
  return true;
}


bool BehaviorInterface::GetGeneralInfoServiceCB(icra_roboin_msgs::BlackboardGeneralInfo::Request& req, 
                                        icra_roboin_msgs::BlackboardGeneralInfo::Response& resp)
{
    UpdateBehaviorProcess();
    resp.stamp = ros::Time::now();
    resp.game_start_time = blackboard_->GetTimeGameStarted();
    resp.time_passed_from_start = blackboard_->GetTimePassedFromGameStart();
    resp.game_state = int(blackboard_->GetGameState()); //0,1,2,3 : dead, ready, play, end
    resp.buff_zone_cooltime = blackboard_->GetTimeLeftForBuffZoneToOnline();
    resp.reload_zone_cooltime = blackboard_->GetTimeLeftForReloadZoneToOnline();
    resp.my_health = blackboard_->GetMyHealth();
    resp.is_hit = blackboard_->GetIsHitSmartResponse();
    if(req.confirm = true){
      blackboard_->ConfirmHitSmartResponse();
    }
    resp.which_armor_hit = int(blackboard_->GetWhichArmorHit()); // 0,1,2,3 : front left rear right (counterclockwise)
    resp.last_hit_time = blackboard_->GetTimeLastHit();
    resp.has_buff = blackboard_->GetHasBuff();
    resp.buff_left = blackboard_->GetTimeBuffLeft();
    resp.ammo = blackboard_->GetAmmo();
    resp.my_pose = blackboard_->GetMyPose();
    resp.how_many_enemies_detected = blackboard_->GetNumberOfDetectedEnemies();
    resp.enemy_pose1 = blackboard_->GetEnemyPose(PlayerType::ENEMY_ONE);
    resp.enemy_pose2 = blackboard_->GetEnemyPose(PlayerType::ENEMY_TWO);
    resp.is_enemy_1_detected = blackboard_->GetIsEnemyDetected(PlayerType::ENEMY_ONE);
    resp.is_enemy_2_detected = blackboard_->GetIsEnemyDetected(PlayerType::ENEMY_TWO);
    resp.locked_on_enemy = int(blackboard_->GetLockedOnEnemy()); // 0,1,2 : no lockon, enemy1, enemy2
    resp.enemy_priority = int(blackboard_->GetEnemyPriority()); // 0,1,2,3,4 : no priority, enemy1, enemy2, any enemym, reserved slot
    resp.goal = blackboard_->GetGoal();
    resp.current_behavior_style = int(blackboard_->GetBehaviorStyle()); 
    resp.current_behavior_process = int(blackboard_->GetBehaviorProcess()); //0,1,2,3 : idle, running, success, failure
    return true;
}






void BehaviorInterface::Run(){
  for(auto behav: behavior_factory_){
    if(behav->GetBehaviorStyle()==blackboard_->GetBehaviorStyle()){
      behav->Run();
      break;
    }
  }
}


void BehaviorInterface::UpdateBehaviorProcess(){
  for(auto behav: behavior_factory_){
    if(behav->GetBehaviorStyle()==blackboard_->GetBehaviorStyle()){
      blackboard_->SetBehaviorProcess(behav->Update());
      break;
    }
  }
}




}