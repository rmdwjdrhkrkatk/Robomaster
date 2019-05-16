#include "behavior_interface.h"
#include <memory>

int main(int argc, char** argv) {
    ros::init(argc,argv, "behavior_interface_node");
    ros::NodeHandle nh("");
    

        auto chassis_executor_0 = new icra_roboin_behavior::ChassisExecutor;
        //auto chassis_executor_1 = new icra_roboin_behavior::ChassisExecutor("robot_1");

        //auto blackboard_0 = new icra_roboin_behavior::Blackboard("robot_0");
        //auto blackboard_1 = new icra_roboin_behavior::Blackboard("robot_1");

        auto blackboard_0 = new icra_roboin_behavior::Blackboard;
        //auto blackboard_1 = new icra_roboin_behavior::Blackboard;


        auto hold_0 = std::make_shared<icra_roboin_behavior::Hold>(chassis_executor_0,blackboard_0);
        auto move_0 = std::make_shared<icra_roboin_behavior::Move>(chassis_executor_0,blackboard_0);
        //auto hold_1 = std::make_shared<icra_roboin_behavior::Hold>(chassis_executor_1, blackboard_1);
        //auto move_1 = std::make_shared<icra_roboin_behavior::Move>(chassis_executor_1, blackboard_1);

        std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory_0;
        //std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory_1;


        behavior_factory_0.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(hold_0));
        behavior_factory_0.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(move_0));

        //behavior_factory_1.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(hold_1));
        //behavior_factory_1.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(move_1));


        icra_roboin_behavior::BehaviorInterface behavior_interface_0(chassis_executor_0,blackboard_0,behavior_factory_0);
        //icra_roboin_behavior::BehaviorInterface behavior_interface_1(chassis_executor_1,blackboard_1,behavior_factory_1);

    ros::Rate rate(10);
    while(ros::ok()){
        ros::spinOnce();
        behavior_interface_0.Run();
        //behavior_interface_1.Run();
        rate.sleep();
    }

    return 0;

}
