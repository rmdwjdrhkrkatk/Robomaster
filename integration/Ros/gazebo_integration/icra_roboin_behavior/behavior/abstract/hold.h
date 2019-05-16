#ifndef ICRA_ROBOIN_BEHAVIOR_HOLD_BEHAVIOR_BASE_H
#define ICRA_ROBOIN_BEHAVIOR_HOLD_BEHAVIOR_BASE_H
#include "behavior_base.h"

namespace icra_roboin_behavior{

class Hold : public BehaviorBase{
    public:
        Hold(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
			icra_roboin_behavior::Blackboard*& blackboard):
			BehaviorBase::BehaviorBase(chassis_executor,blackboard){}
        
        virtual ~Hold() = default;
        
        virtual bool Run() override{
            RunHold();
            return true;
        }

		virtual bool Cancel() override {
			chassis_executor_->Cancel();
			ROS_INFO("behavior hold : canceld");
			return true;
		}

		virtual BehaviorStyle GetBehaviorStyle() override {
			return BehaviorStyle::HOLD;
		}

        virtual void RunHold(){
			geometry_msgs::Twist speed;
            speed.linear.x = 0;
            speed.linear.y = 0;
            speed.angular.z = 0;
			ROS_INFO("behavior : hold");
            chassis_executor_->Execute(speed);
        }















};


}
#endif
