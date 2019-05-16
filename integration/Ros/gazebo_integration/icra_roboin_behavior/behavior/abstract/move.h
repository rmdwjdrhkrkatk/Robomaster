#ifndef ICRA_ROBOIN_BEHAVIOR_MOVE_H
#define ICRA_ROBOIN_BEHAVIOR_MOVE_H
#include "behavior_base.h"
#include "../../tools.h"

namespace icra_roboin_behavior {

class Move: public BehaviorBase{
    public:
        Move(ChassisExecutor*& chassis_executor,
                    Blackboard*& blackboard
                    ): BehaviorBase::BehaviorBase(chassis_executor,blackboard){}
        
        virtual ~Move() =default;

        virtual bool Run() override{
            RunNavigation();
            return true;
        }

		virtual bool Cancel() override {
			chassis_executor_->Cancel();
			ROS_INFO("behavior move : canceld");
			return true;
		}

		virtual BehaviorStyle GetBehaviorStyle() override {
			return BehaviorStyle::MOVE;
		}

        virtual void RunNavigation() {

            chassis_executor_->Execute(blackboard_->transform_goal());
            ROS_INFO("behavior : move");                       
        }



         
        
};




}




#endif
