#ifndef ICRA_ROBOIN_BEHAVIOR_GIMBAL_EXECUTOR_H
#define ICRA_ROBOIN_BEHAVIOR_GIMBAL_EXECUTOR_H

#include <ros/ros.h>
#include "roborts_msgs/GimbalAngle.h"
#include "../enums.h"


namespace icra_roboin_behavior {

class GimbalExecutor{
    public:
        GimbalExecutor();
        ~GimbalExecutor() = default;

        void Execute(const roborts_msgs::GimbalAngle& gimbal_angle);
        BehaviorState Update();
        void Cancel();

    private:

        GimbalMode executor_mode_;
        BehaviorState executor_state_;
        ros::Publisher gimbal_pub_;

};


}
#endif




