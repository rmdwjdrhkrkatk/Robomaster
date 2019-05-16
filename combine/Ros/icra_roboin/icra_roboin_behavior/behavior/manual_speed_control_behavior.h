#ifndef ICRA_ROBOIN_BEHAVIOR_MANUAL_SPEED_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_MANUAL_SPEED_BEHAVIOR_H
#include "abstract/manual_control_behavior_base.h"

namespace icra_roboin_behavior{

class ManualSpeedControlBehavior : public ManualControlBehaviorBase{
    public:
        ManualSpeedControlBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                            icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                            icra_roboin_behavior::LockonModule*& lockon_module,
                            icra_roboin_behavior::Blackboard*& blackboard): ManualControlBehaviorBase::ManualControlBehaviorBase(chassis_executor,gimbal_executor,lockon_module,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::MANUAL_SPEED_CONTROL;
            behavior_class_name_ = "manual speed with lockon behavior";
        }
        ~ManualSpeedControlBehavior() = default;
        
        void NoEngage() override{
            lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,2);
        }
        
    
};


}
#endif