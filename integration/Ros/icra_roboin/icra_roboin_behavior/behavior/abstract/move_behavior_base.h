#ifndef ICRA_ROBOIN_BEHAVIOR_MOVE_BEHAVIOR_BASE_H
#define ICRA_ROBOIN_BEHAVIOR_MOVE_BEHAVIOR_BASE_H
#include "behavior_base.h"

namespace icra_roboin_behavior {

class MoveBehaviorBase: public BehaviorBase{
    public:
        MoveBehaviorBase(ChassisExecutor*& chassis_executor,
                    GimbalExecutor*& gimbal_executor,
                    LockonModule*& lockon_module,
                    Blackboard*& blackboard
                    ): BehaviorBase::BehaviorBase(chassis_executor,gimbal_executor,
                                                    lockon_module,blackboard){}
        
        virtual ~MoveBehaviorBase() =default;

        virtual bool Run() override{
            RunNavigation();
            RunLockon();
            return true;
        }

        virtual void RunNavigation() {
            if(blackboard_->IsNewGoal()){
            chassis_executor_->Execute(blackboard_->GetGoalPoseQuaternion());
            ROS_INFO("run %s behavior",behavior_class_name_.c_str());
            }
            
        }

        virtual void RunLockon() {
            if(blackboard_->GetLockedOnEnemy() == PlayerType::ENEMY_ONE | blackboard_->GetLockedOnEnemy() == PlayerType::ENEMY_TWO){
                if( (ros::Time::now() - (blackboard_->GetTimeLastSeen(blackboard_->GetLockedOnEnemy()))).toSec() > 2 ){
                    blackboard_->ConfirmHitFastResponse();
                    blackboard_->SetLockedOnEnemy(PlayerType::ALLY);
                    NoLockonTargetBehavior();
                } else{
                    lockon_module_->LockonInterface(LockonMode::TARGET_ENEMY_LOCKON,blackboard_->GetLockedOnEnemy());
                }
                
            } else if(blackboard_->GetLockedOnEnemy() == PlayerType::ALLY) {
                NoLockonTargetBehavior();
            }
        }

        virtual void NoLockonTargetBehavior() {
            if(blackboard_->GetIsEnemyDetected(PlayerType::ENEMY_ANY)){
                OnDetect();
            } else if(blackboard_->GetIsHitFastResponse()){
                OnHit();
            } else {
                NoEngage();
            }
        }
        virtual void OnHit() {
            switch(blackboard_->GetWhichArmorHit()){
                case ArmorType::FRONT:
                  blackboard_->ConfirmHitFastResponse();
                  break;
                case ArmorType::LEFT:
                  lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,4);
                  break;
                case ArmorType::RIGHT:
                  lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,-4);
                  break;
                case ArmorType::REAR:
                  lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,4);
                  break;
            } 
        }

        virtual void OnDetect() {
            blackboard_->ConfirmHitFastResponse();
            if(blackboard_->GetEnemyPriority() == PlayerType::ENEMY_ANY){
                switch(blackboard_->GetWhichEnemyDetected()){
                    case PlayerType::ENEMY_ANY:
                        blackboard_->SetLockedOnEnemy(PlayerType::ENEMY_ONE);
                        lockon_module_->LockonInterface(LockonMode::TARGET_ENEMY_LOCKON,blackboard_->GetLockedOnEnemy());
                        break;
                    case PlayerType::ENEMY_ONE:
                        blackboard_->SetLockedOnEnemy(PlayerType::ENEMY_ONE);
                        lockon_module_->LockonInterface(LockonMode::TARGET_ENEMY_LOCKON,blackboard_->GetLockedOnEnemy());
                        break;
                    case PlayerType::ENEMY_TWO:
                        blackboard_->SetLockedOnEnemy(PlayerType::ENEMY_TWO);
                        lockon_module_->LockonInterface(LockonMode::TARGET_ENEMY_LOCKON,blackboard_->GetLockedOnEnemy());
                        break;
                }
            }
        }

        virtual void NoEngage() = 0;

        

        virtual bool Cancel() override{
            chassis_executor_->Cancel();
            ROS_INFO("%s : canceld",behavior_class_name_.c_str());
            return true;
        }

        virtual BehaviorProcess Update() override{
            return chassis_executor_->Update();
        }

        virtual BehaviorStyle GetBehaviorStyle() const override{
            return behavior_style_;
        }



         
        
};




}




#endif