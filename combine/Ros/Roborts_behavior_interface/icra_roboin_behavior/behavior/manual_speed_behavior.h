#ifndef ICRA_ROBOIN_BEHAVIOR_MANUAL_SPEED_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_MANUAL_SPEED_BEHAVIOR_H
#include "behavior_base.h"
#include <geometry_msgs/Twist.h>
namespace icra_roboin_behavior{

class ManualSpeedBehavior : public BehaviorBase{
    public:
        ManualSpeedBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                            icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                            icra_roboin_behavior::Blackboard*& blackboard): BehaviorBase::BehaviorBase(chassis_executor,gimbal_executor,blackboard)
        {
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::MANUAL_SPEED;
        }
        virtual ~ManualSpeedBehavior() = default;
        
        bool Run(){
            
            geometry_msgs::Twist speed_msg;
            geometry_msgs::Pose tmp = blackboard_->GetGoalPose().pose;
            speed_msg.linear.x = tmp.position.x;
            speed_msg.linear.y = tmp.position.y;
            speed_msg.angular.z = tmp.position.z;
            ROS_INFO("run manual_speed behavior x:%f, y:%f, yaw:%f",speed_msg.linear.x,speed_msg.linear.y,speed_msg.angular.z);
            chassis_executor_->Execute(speed_msg);
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