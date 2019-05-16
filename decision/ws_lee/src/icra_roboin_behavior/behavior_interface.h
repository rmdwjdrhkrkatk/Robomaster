#ifndef ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_INTERFACE_H
#define ICRA_ROBOIN_BEHAVIOR_BEHAVIOR_INTERFACE_H

#include <ros/ros.h>
#include <memory>
#include <vector>

#include "executor/chassis_executor.h"
#include "blackboard/blackboard.h"
#include "behavior/abstract/behavior_base.h"
#include "behavior/abstract/move.h"
#include "behavior/abstract/hold.h"





namespace icra_roboin_behavior {

class BehaviorInterface {
    public:
        BehaviorInterface(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::Blackboard*& blackboard,
                    std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>>& behavior_factory);


        ~BehaviorInterface() = default;

        void Run();
        

        icra_roboin_behavior::ChassisExecutor* const chassis_executor_;
        icra_roboin_behavior::Blackboard* const blackboard_;
        std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>> behavior_factory_;


};










}

#endif
