#ifndef ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_BASE_H
#define ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_BASE_H
#include <ros/ros.h>
#include <memory>
#include "../../executor/chassis_executor.h"
#include "../../executor/gimbal_executor.h"
#include "../../executor/lockon_module.h"
#include "../../blackboard/blackboard.h"

namespace icra_roboin_behavior {

class BehaviorBase {
    public:
        BehaviorBase(ChassisExecutor*& chassis_executor,
                    GimbalExecutor*& gimbal_executor,
                    LockonModule*& lockon_module,
                    Blackboard*& blackboard): chassis_executor_(chassis_executor),
                                                                    gimbal_executor_(gimbal_executor),
                                                                    lockon_module_(lockon_module),
                                                                    blackboard_(blackboard){}
        virtual ~BehaviorBase() =default;



        
        virtual bool Run() = 0;
        virtual bool Cancel() = 0;
        virtual BehaviorProcess Update() = 0;
        virtual BehaviorStyle GetBehaviorStyle() const = 0;
        
        
        

    protected:
    ChassisExecutor* const chassis_executor_;
    GimbalExecutor* const gimbal_executor_;
    LockonModule* const lockon_module_;
    Blackboard* const blackboard_;
    BehaviorStyle behavior_style_;
    std::string behavior_class_name_;
    
    
};


}
#endif