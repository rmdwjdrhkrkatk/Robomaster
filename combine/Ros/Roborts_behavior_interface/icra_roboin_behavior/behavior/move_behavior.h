#ifndef ICRA_ROBOIN_BEHAVIOR_MOVE_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_MOVE_BEHAVIOR_H
#include "behavior_base.h"
#include <tf/tf.h>

namespace icra_roboin_behavior {

class MoveBehavior: public BehaviorBase{
    public:
        MoveBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::Blackboard*& blackboard): BehaviorBase::BehaviorBase(chassis_executor,
                                                                    gimbal_executor,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::MOVE;
        }
        virtual ~MoveBehavior() =default;

        bool Run() {
            if(blackboard_->IsNewGoalPose()){
                chassis_executor_->Execute(blackboard_->GetGoalPoseQuaternion());
            }
            return true;
            //TODO: check whether goal is sent successfully
        }

        bool Cancel() {
            chassis_executor_->Cancel();
        }

        icra_roboin_behavior::BehaviorState Update() {
            return chassis_executor_->Update();
        }

        icra_roboin_behavior::BehaviorStyle GetBehaviorStyle() {return behavior_style_;}


         
        
};




}




#endif



