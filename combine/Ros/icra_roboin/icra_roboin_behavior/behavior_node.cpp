#include "behavior_interface.h"
#include <memory>

int main(int argc, char** argv) {
    ros::init(argc,argv, "behavior_interface_node");
    ros::NodeHandle nh("~");
    

    std::string team_param, rule_param;
    icra_roboin_behavior::TeamType team;
    icra_roboin_behavior::RuleType rule;
    nh.getParam("team",team_param);
    nh.getParam("rule",rule_param);

    if(team_param == "blue_team"){
    team = icra_roboin_behavior::TeamType::BLUE_TEAM;
    } else if(team_param == "red_team"){
    team = icra_roboin_behavior::TeamType::RED_TEAM;
    } else if(team_param == "none"){
    team = icra_roboin_behavior::TeamType::NONE;
    } else {
    ROS_ERROR("behavior_interface error: wrong team parameter");
    }

    if(rule_param == "solo"){
    rule = icra_roboin_behavior::RuleType::SOLO;
    } else if(rule_param == "1vs1"){
    rule = icra_roboin_behavior::RuleType::ONE_VS_ONE;
    } else if(rule_param == "1vs2"){
    rule = icra_roboin_behavior::RuleType::ONE_VS_TWO;
    } else if(rule_param == "2vs1"){
    rule = icra_roboin_behavior::RuleType::TWO_VS_ONE;
    } else if(rule_param == "2vs2"){
    rule = icra_roboin_behavior::RuleType::TWO_VS_TWO;
    } else {
    ROS_ERROR("behavior_interface error: wrong rule parameter");
    }    



    auto chassis_executor = new icra_roboin_behavior::ChassisExecutor;
    auto gimbal_executor = new icra_roboin_behavior::GimbalExecutor;
    auto blackboard = new icra_roboin_behavior::Blackboard(team,rule);
    auto lockon_module = new icra_roboin_behavior::LockonModule(blackboard,DT,SENTRY_ANGLE); //dt = 0.1


    auto lockon_search_move_behavior = std::make_shared<icra_roboin_behavior::LockonSearchMoveBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);
    auto hold_rotate_behavior = std::make_shared<icra_roboin_behavior::HoldRotateBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);
    auto hold_sentry_behavior = std::make_shared<icra_roboin_behavior::HoldSentryBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);
    auto manual_speed_control_behavior = std::make_shared<icra_roboin_behavior::ManualSpeedControlBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);
    auto reload_behavior = std::make_shared<icra_roboin_behavior::ReloadBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);
    auto get_buff_behavior = std::make_shared<icra_roboin_behavior::GetBuffBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);
    auto ready_behavior = std::make_shared<icra_roboin_behavior::ReadyBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);
    auto backboot_behavior = std::make_shared<icra_roboin_behavior::BackbootBehavior>(chassis_executor,gimbal_executor,lockon_module,blackboard);


    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory;
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(lockon_search_move_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(hold_rotate_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(hold_sentry_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(manual_speed_control_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(reload_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(get_buff_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(ready_behavior));
    behavior_factory.push_back(std::dynamic_pointer_cast<icra_roboin_behavior::BehaviorBase>(backboot_behavior));

    icra_roboin_behavior::BehaviorInterface behavior_interface(chassis_executor,gimbal_executor,lockon_module,blackboard,behavior_factory);

    ros::Rate rate(10);
    while(ros::ok()){
        ros::spinOnce();
        behavior_interface.Run();
        rate.sleep();
    }

    return 0;

}