#include "behavior_interface.h"
#include <memory>

int main(int argc, char** argv) {
    ros::init(argc,argv, "behavior_interface_node");
    ros::NodeHandle nh("~");
    
    icra_roboin_behavior::ChassisExecutor* chassis_executor;
    icra_roboin_behavior::Blackboard* blackboard;


    auto hold = std::make_shared<icra_roboin_behavior::Hold>(chassis_executor,blackboard);
    auto move = std::make_shared<icra_roboin_behavior::Move>(chassis_executor,blackboard);

    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory;


    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(hold));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(move));


    icra_roboin_behavior::BehaviorInterface behavior_interface(chassis_executor,blackboard,behavior_factory);

    ros::Rate rate(10);
    while(ros::ok()){
        ros::spinOnce();
        behavior_interface.Run();
        rate.sleep();
    }

    return 0;

}