#ifndef ICRA_ROBOIN_BEHAVIOR_RELOAD_BEHAVIOR_H
#define ICRA_ROBOIN_BEHAVIOR_RELOAD_BEHAVIOR_H
#include "abstract/task_move_behavior_base.h"
#include "icra_roboin_msgs/RefereeTag.h"

namespace icra_roboin_behavior {

class ReloadBehavior: public TaskMoveBehaviorBase{
    public:
         ReloadBehavior(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::LockonModule*& lockon_module,
                    icra_roboin_behavior::Blackboard*& blackboard
                    ): TaskMoveBehaviorBase::TaskMoveBehaviorBase(chassis_executor,gimbal_executor,
                                                    lockon_module,blackboard)
        {
            ros::NodeHandle nh;
            behavior_style_ = icra_roboin_behavior::BehaviorStyle::RELOAD;
            behavior_class_name_ = "reload behavior";
            referee_tag_client_ = nh.serviceClient<icra_roboin_msgs::RefereeTag>("referee_tag_service");
            timeout_ = ros::Duration(6);
        }
        ~ReloadBehavior() = default;

        void NoEngage() override{
            lockon_module_->LockonInterface(LockonMode::ANGULAR_VEL,3);
        }

        void ExecuteTask() override{
            lockon_module_->LockonInterface(LockonMode::GLOBAL_YAW,(blackboard_->GetGoal()).yaw);
            switch(current_state_){
                case TaskCheck::EXECUTE:
                {
                    icra_roboin_msgs::RefereeTag srv;
                    referee_tag_client_.call(srv);
                    if(srv.response.info == 1){
                        ROS_INFO("Reload behavior : Reload tagged successfully!");
                        current_state_ = TaskCheck::BUSY;
                        execution_time_ = ros::Time::now();
                        blackboard_ -> SetIsReloading(true);
                    } else {
                        current_state_ = TaskCheck::NOT_YET;
                    }
                    break;
                }
                case TaskCheck::BUSY:
                {
                    if((ros::Time::now() - execution_time_) > timeout_){
                        ROS_INFO("Reload behavior : Reload timeout!");
                        current_state_ = TaskCheck::FAIL;
                        blackboard_->SetIsReloading(false);
                    } else {
                        if(blackboard_->GetIsReloading() == false){
                            current_state_ = TaskCheck::FINISHED;
                        }
                    }
                    break;
                }
                case TaskCheck::FAIL:
                    ROS_INFO("Reload behavior : Reload Failed!");
                    break;
                case TaskCheck::FINISHED:
                    ROS_INFO("Reload behavior : Reload Finished!");
                    break;


            }
        }

        bool Cancel() override{
            if(current_state_ == TaskCheck::BUSY | current_state_ == TaskCheck::EXECUTE){
                ROS_INFO("%s cannont be canceled. it's busy",behavior_class_name_.c_str());
                return false;
            } else {
                chassis_executor_->Cancel();
                ROS_INFO("%s : canceld",behavior_class_name_.c_str());
                current_state_ = TaskCheck::NOT_YET;
                return true;
            }
        }

        BehaviorProcess Update() override{
            if(current_state_ == TaskCheck::FAIL){
                return BehaviorProcess::FAILURE;
            } else if(current_state_ == TaskCheck::BUSY){
                return BehaviorProcess::BUSY;
            } else if(current_state_ == TaskCheck::EXECUTE){
                return BehaviorProcess::BUSY;
            } else if(current_state_ == TaskCheck::FINISHED){
                return BehaviorProcess::SUCCESS;
            } else {
                return chassis_executor_->Update();
            }
        }


    private:
        ros::ServiceClient referee_tag_client_;
        


};




}




#endif



