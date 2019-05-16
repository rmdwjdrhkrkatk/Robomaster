#ifndef ICRA_ROBOIN_BEHAVIOR_GET_BUFF_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_GET_BUFF_BEHAVIOR_H
#include "abstract/task_move_behavior_base.h"


namespace icra_roboin_behavior {

class GetBuffBehavior: public TaskMoveBehaviorBase{
    public:
         GetBuffBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::LockonModule*& lockon_module,
                    icra_roboin_behavior::Blackboard*& blackboard
                    ): TaskMoveBehaviorBase::TaskMoveBehaviorBase(chassis_executor,gimbal_executor,
                                                    lockon_module,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::GET_BUFF;
            behavior_class_name_ = "get buff behavior";
        }
        ~GetBuffBehavior() = default;

        void NoEngage() override{
            lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,2);
        }

        void ExecuteTask() override{
            
        }
};




}




#endif



