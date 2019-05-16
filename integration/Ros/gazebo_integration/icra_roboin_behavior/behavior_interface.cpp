#include "behavior_interface.h"

namespace icra_roboin_behavior {

	BehaviorInterface::BehaviorInterface(ChassisExecutor*& chassis_executor,
		Blackboard*& blackboard,
		std::vector<std::shared_ptr<icra_roboin_behavior::BehaviorBase>>& behavior_factory) :
		chassis_executor_(chassis_executor),
		blackboard_(blackboard),
		behavior_factory_(behavior_factory){  }
	   	  


void BehaviorInterface::Run(){
  for(auto behav: behavior_factory_){
    if(behav->GetBehaviorStyle()==blackboard_->GetBehaviorStyle()){ 
      behav->Run();
      break;
    }
  }
}





}