#ifndef ICRA_ROBOIN_BEHAVIOR_BACKBOOT_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_BACKBOOT_BEHAVIOR_H
#include "abstract/task_move_behavior_base.h"
namespace icra_roboin_behavior{

class BackbootBehavior : public TaskMoveBehaviorBase{
    public:
        BackbootBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                            icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                            icra_roboin_behavior::LockonModule*& lockon_module,
                            icra_roboin_behavior::Blackboard*& blackboard): 
                            TaskMoveBehaviorBase::TaskMoveBehaviorBase(chassis_executor,
                                                                gimbal_executor,
                                                                lockon_module,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::BACKBOOT;
            behavior_class_name_ = "backboot behavior";
        }
        ~BackbootBehavior() = default;
        
        void NoEngage() override{
            lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,0);
        }

        void ExecuteTask() override {
            switch(current_state_){
                case TaskCheck::EXECUTE:
                    if(blackboard_->GetGameState() != GameState::READY){
                        current_state_ == TaskCheck::FINISHED;
                    } else if(blackboard_->GetGameState() == GameState::READY) {
                        lockon_module_->LockonInterface(LockonMode::GLOBAL_YAW,(blackboard_->GetGoal()).yaw);
                    }
                    break;
                case TaskCheck::FINISHED:
                    lockon_module_->LockonInterface(LockonMode::GLOBAL_YAW,(blackboard_->GetGoal()).yaw);
                    ROS_INFO("backboot behavior : Ready!");
                    break;
            }
        }
        
    
};


}
#endif