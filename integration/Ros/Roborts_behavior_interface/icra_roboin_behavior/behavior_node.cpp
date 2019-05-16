#include "behavior_interface.h"
#include <memory>

int main(int argc, char** argv) {
    ros::init(argc,argv, "behavior_interface_node");
    
    auto chassis_executor = new icra_roboin_behavior::ChassisExecutor;
    auto gimbal_executor = new icra_roboin_behavior::GimbalExecutor;
    auto blackboard = new icra_roboin_behavior::Blackboard;

    auto move_behavior = std::make_shared<icra_roboin_behavior::MoveBehavior>(chassis_executor,gimbal_executor,blackboard);
    auto manual_speed_behavior = std::make_shared<icra_roboin_behavior::ManualSpeedBehavior>(chassis_executor,gimbal_executor,blackboard);
    auto manual_accel_behavior = std::make_shared<icra_roboin_behavior::ManualAccelBehavior>(chassis_executor,gimbal_executor,blackboard);

    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory;
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(move_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(manual_speed_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(manual_accel_behavior));

    icra_roboin_behavior::BehaviorInterface behavior_interface(chassis_executor,gimbal_executor,blackboard,behavior_factory);

    ros::Rate rate(10);
    while(ros::ok()){
        ros::spinOnce();
        behavior_interface.Run();
        rate.sleep();
    }

    return 0;

}