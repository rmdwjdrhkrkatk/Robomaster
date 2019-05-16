#ifndef ICRA_ROBOIN_BEHAVIOR_HOLD_SENTRY_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_HOLD_SENTRY_BEHAVIOR_H
#include "abstract/hold_behavior_base.h"
namespace icra_roboin_behavior{

class HoldSentryBehavior : public HoldBehaviorBase{
    public:
        HoldSentryBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                            icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                            icra_roboin_behavior::LockonModule*& lockon_module,
                            icra_roboin_behavior::Blackboard*& blackboard): 
                            HoldBehaviorBase::HoldBehaviorBase(chassis_executor,
                                                                gimbal_executor,
                                                                lockon_module,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::HOLD_SENTRY;
            behavior_class_name_ = "hold sentry behavior";
        }
        ~HoldSentryBehavior() = default;
        
        void NoEngage() override{
            lockon_module_->LockonInterface(LockonMode::GLOBAL_YAW_SENTRY,lockon_yaw_);
        }
        
    
};


}
#endif