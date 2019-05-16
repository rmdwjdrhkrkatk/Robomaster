#ifndef ICRA_ROBOIN_BEHAVIOR_HOLD_ROTATE_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_HOLD_ROTATE_BEHAVIOR_H
#include "abstract/hold_behavior_base.h"
namespace icra_roboin_behavior{

class HoldRotateBehavior : public HoldBehaviorBase{
    public:
        HoldRotateBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                            icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                            icra_roboin_behavior::LockonModule*& lockon_module,
                            icra_roboin_behavior::Blackboard*& blackboard): 
                            HoldBehaviorBase::HoldBehaviorBase(chassis_executor,
                                                                gimbal_executor,
                                                                lockon_module,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::HOLD_ROTATE;
            behavior_class_name_ = "hold rotate behavior";
        }
        ~HoldRotateBehavior() = default;
        
        void NoEngage() override{
            lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,2);
        }
        
    
};


}
#endif