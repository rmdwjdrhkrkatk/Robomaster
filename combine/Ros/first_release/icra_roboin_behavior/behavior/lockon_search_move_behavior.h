#ifndef ICRA_ROBOIN_BEHAVIOR_LOCKON_SEARCH_MOVE_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_LOCKON_SEARCH_MOVE_BEHAVIOR_H
#include "abstract/move_behavior_base.h"


namespace icra_roboin_behavior {

class LockonSearchMoveBehavior: public MoveBehaviorBase{
    public:
        LockonSearchMoveBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::LockonModule*& lockon_module,
                    icra_roboin_behavior::Blackboard*& blackboard
                    ): MoveBehaviorBase::MoveBehaviorBase(chassis_executor,gimbal_executor,
                                                    lockon_module,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::LOCKON_SEARCH_MOVE;
            behavior_class_name_ = "lockon and search move behavior";
        }
        ~LockonSearchMoveBehavior() = default;

        void NoEngage() override{
            lockon_module_->LockonInterface(LockonMode::TARGET_GOAL_LOCKON);
        }
};




}




#endif



