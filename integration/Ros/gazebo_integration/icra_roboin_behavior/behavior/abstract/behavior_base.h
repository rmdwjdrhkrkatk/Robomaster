#ifndef ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_BASE_H
#define ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_BASE_H
#include <ros/ros.h>
#include <memory>
#include "../../enums.h"
#include "../../executor/chassis_executor.h"
#include "../../blackboard/blackboard.h"

namespace icra_roboin_behavior {

class BehaviorBase {
    public:
        BehaviorBase(ChassisExecutor*& chassis_executor,Blackboard*& blackboard): chassis_executor_(chassis_executor),
			blackboard_(blackboard){}
        virtual ~BehaviorBase() =default;



        
        virtual bool Run() = 0;
		virtual bool Cancel() = 0;
		virtual BehaviorStyle GetBehaviorStyle() = 0;
        

    protected:
    ChassisExecutor* const chassis_executor_;
    Blackboard* const blackboard_; 
    
};


}
#endif