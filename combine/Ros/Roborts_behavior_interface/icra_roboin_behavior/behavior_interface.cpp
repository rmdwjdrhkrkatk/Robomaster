#include "behavior_interface.h"

namespace icra_roboin_behavior {

BehaviorInterface::BehaviorInterface(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::Blackboard*& blackboard,
                    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>>& behavior_factory): 
                                                                    chassis_executor_(chassis_executor),
                                                                    gimbal_executor_(gimbal_executor),
                                                                    blackboard_(blackboard),
                                                                    behavior_factory_(behavior_factory)
                                                                    
{
  ros::NodeHandle nh("~");
  set_behavior_style_service_ = nh.advertiseService("behavior_select_service",&BehaviorInterface::SetBehaviorStyleCB,this);
  set_goal_service_ = nh.advertiseService("goal_select_service",&BehaviorInterface::SetBehaviorGoalCB,this);
  general_info_server_ = nh.advertiseService("blackboard/general_info_service",&BehaviorInterface::GetGeneralInfoServiceCB,this);
}

bool BehaviorInterface::SetBehaviorStyleCB(icra_roboin_msgs::BehaviorStyleSet::Request &req, icra_roboin_msgs::BehaviorStyleSet::Response &res) {
  ROS_DEBUG("behavior interface: Behavior received: %d",req.behavior);
  auto selected_behavior = static_cast<icra_roboin_behavior::BehaviorStyle>(req.behavior);
  icra_roboin_behavior::BehaviorStyle current_style = blackboard_->GetBehaviorStyle();
  if (current_style == selected_behavior){
    res.is_new = false;
  } else {
    res.is_new = true;
    //ROS_INFO("req:%d,BB:%d",tmp,int(blackboard_->GetBehaviorStyle());
    for(auto behav: behavior_factory_){
      if(behav->GetBehaviorStyle() == current_style){
        behav->Cancel();
        break;
      }
    }
    ROS_INFO("behavior_interface: cancel behaviors");
  }
  blackboard_->SetBehaviorStyle(selected_behavior);
  return true;
}

bool BehaviorInterface::SetBehaviorGoalCB(icra_roboin_msgs::SetGoal_2::Request &req, icra_roboin_msgs::SetGoal_2::Response &res) {
  geometry_msgs::PoseStamped goal;
  goal.header = req.header;
  goal.pose.position.x=req.x;
  goal.pose.position.y=req.y;
  goal.pose.position.z=req.yaw;
  goal.pose.orientation.x=req.xa;
  goal.pose.orientation.y=req.ya;
  goal.pose.orientation.z=req.yawa;
  goal.pose.orientation.w=req.etc;
  blackboard_ -> SetGoalPose(goal);
  res.success = true;
  res.info = 0;
  ROS_DEBUG("behavior interface: Goal received: %f,%f,%f,%f,%f,%f,%f",req.x,req.y,req.yaw,req.xa,req.ya,req.yawa,req.etc);
  return true;
}

bool BehaviorInterface::GetGeneralInfoServiceCB(icra_roboin_msgs::BlackboardGeneralInfo::Request& req, 
                                        icra_roboin_msgs::BlackboardGeneralInfo::Response& resp)
{
    UpdateBlackboardState();
    resp.stamp = ros::Time();
    resp.my_pose = blackboard_->GetMyPose();
    resp.enemy_count = blackboard_ -> GetEnemyNumber();
    resp.enemy_pose1 = blackboard_ -> GetEnemyPose(1);
    resp.enemy_pose2 = blackboard_ -> GetEnemyPose(2);
    resp.goal_pose = blackboard_->GetGoalPose();
    resp.is_enemy_detected = blackboard_-> IsEnemyDetected(0);
    resp.is_enemy_1_detected = blackboard_-> IsEnemyDetected(1);
    resp.is_enemy_2_detected = blackboard_-> IsEnemyDetected(2);
    resp.has_defense_bonus = blackboard_-> HasDefenseBonus();
    resp.defense_time_left = blackboard_-> GetDefenseTimeLeft();
    resp.current_behavior_state = int(blackboard_->GetBehaviorState());
    resp.current_behavior_style = int(blackboard_->GetBehaviorStyle());

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


void BehaviorInterface::UpdateBlackboardState(){
  for(auto behav: behavior_factory_){
    if(behav->GetBehaviorStyle()==blackboard_->GetBehaviorStyle()){
      blackboard_->SetBehaviorState(behav->Update());
      break;
    }
  }
}










}