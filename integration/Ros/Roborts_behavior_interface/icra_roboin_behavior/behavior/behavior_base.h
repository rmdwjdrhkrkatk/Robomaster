#ifndef ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_BASH_H
#define ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_BASH_H
#include <ros/ros.h>
#include <memory>
#include "../executor/chassis_executor.h"
#include "../executor/gimbal_executor.h"
#include "../blackboard/blackboard.h"

namespace icra_roboin_behavior {

class BehaviorBase {
    public:
        BehaviorBase(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::Blackboard*& blackboard): chassis_executor_(chassis_executor),
                                                                    gimbal_executor_(gimbal_executor),
                                                                    blackboard_(blackboard){}
        virtual ~BehaviorBase() =default;



        
        virtual bool Run() = 0;
        virtual bool Cancel() = 0;
        virtual icra_roboin_behavior::BehaviorState Update() = 0;
        virtual icra_roboin_behavior::BehaviorStyle GetBehaviorStyle() = 0;
        
        
        

    protected:
    icra_roboin_behavior::ChassisExecutor* const chassis_executor_;
    icra_roboin_behavior::GimbalExecutor* const gimbal_executor_;
    icra_roboin_behavior::Blackboard* const blackboard_;
    icra_roboin_behavior::BehaviorStyle behavior_style_;
    
    
};


}
#endif