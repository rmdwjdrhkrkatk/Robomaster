#ifndef ICRA_ROBOIN_BEHAVIOR_MANUAL_ACCEL_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_MANUAL_ACCEL_BEHAVIOR_H
#include "behavior_base.h"
#include <geometry_msgs/Twist.h>
#include "roborts_msgs/TwistAccel.h"
namespace icra_roboin_behavior{

class ManualAccelBehavior : public BehaviorBase{
    public:
        ManualAccelBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                            icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                            icra_roboin_behavior::Blackboard*& blackboard): BehaviorBase::BehaviorBase(chassis_executor,gimbal_executor,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::MANUAL_ACCEL;
        }
        virtual ~ManualAccelBehavior() = default;
        
        bool Run(){
            
            roborts_msgs::TwistAccel speed_acc;
            geometry_msgs::Pose goal = blackboard_->GetGoalPose().pose;
            speed_acc.twist.linear.x = goal.position.x;
            speed_acc.twist.linear.y = goal.position.y;
            speed_acc.twist.angular.z = goal.position.z;
            speed_acc.accel.linear.x = goal.orientation.x;
            speed_acc.accel.linear.y = goal.orientation.y;
            speed_acc.accel.angular.z = goal.orientation.z;
            
            ROS_INFO("run manual_speed behavior");
            chassis_executor_->Execute(speed_acc);
            return true;
        }
        bool Cancel() {
            chassis_executor_->Cancel();
        }
        icra_roboin_behavior::BehaviorState Update(){
            return chassis_executor_->Update();
        }
        icra_roboin_behavior::BehaviorStyle GetBehaviorStyle(){return behavior_style_;}
        
    
};


}
#endif