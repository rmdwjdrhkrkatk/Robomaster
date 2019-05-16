#ifndef ICRA_ROBOIN_BEHAVIOR_TASK_MOVE_BEHAVIOR_BASE_H
#define ICRA_ROBOIN_BEHAVIOR_TASK_MOVE_BEHAVIOR_BASE_H
#include "move_behavior_base.h"


namespace icra_roboin_behavior {

class TaskMoveBehaviorBase: public MoveBehaviorBase{
    public:
        TaskMoveBehaviorBase(icra_roboin_behavior::ChassisExecutor*& chassis_executor,
                    icra_roboin_behavior::GimbalExecutor*& gimbal_executor,
                    icra_roboin_behavior::LockonModule*& lockon_module,
                    icra_roboin_behavior::Blackboard*& blackboard
                    ): MoveBehaviorBase::MoveBehaviorBase(chassis_executor,gimbal_executor,
                                                    lockon_module,blackboard){}

        virtual ~TaskMoveBehaviorBase() = default;

        virtual bool Run() override{
            if(current_state_ != TaskCheck::BUSY && current_state_ != TaskCheck::FINISHED && current_state_ != TaskCheck::FAIL){
                switch(CheckDistance()){
                    case TaskCheck::NOT_YET:
                        RunNavigation();
                        RunLockon();
                        //ROS_INFO("task behavior: not yet :: %d",int(current_state_));
                        break;
                    case TaskCheck::GET_READY:
                        RunNavigation();
                        //ROS_INFO("task behavior: get ready :: %d",int(current_state_));
                        lockon_module_->LockonInterface(LockonMode::GLOBAL_YAW,(blackboard_->GetGoal()).yaw);
                        break;
                    case TaskCheck::EXECUTE:
                        //ROS_INFO("task behavior: execute :: %d",int(current_state_));
                        lockon_module_->LockonInterface(LockonMode::GLOBAL_YAW,(blackboard_->GetGoal()).yaw);
                        ExecuteTask();
                        
                        break;
                }
            } else {
                ExecuteTask();
            }

            return true;
        }

        virtual TaskCheck CheckDistance(){
            distance_ = tools::GetPlanarDistance(blackboard_->GetGoalPoseQuaternion(),blackboard_->GetMyPose());
            if(distance_ > 2) {
                current_state_ = TaskCheck::NOT_YET;
                return TaskCheck::NOT_YET;
            } else if(distance_ < 2 && distance_ > 0.3) {
                current_state_ = TaskCheck::GET_READY;
                return TaskCheck::GET_READY;
            } else if(distance_ < 0.3) {
                current_state_ = TaskCheck::EXECUTE;
                return TaskCheck::EXECUTE;
            }
        }
        virtual void ExecuteTask() = 0;

        virtual bool Cancel() override{
            if(current_state_ == TaskCheck::BUSY){
                ROS_INFO("%s cannont be canceled. it's busy",behavior_class_name_.c_str());
                return false;
            } else {
                chassis_executor_->Cancel();
                ROS_INFO("%s : canceld",behavior_class_name_.c_str());
                current_state_ = TaskCheck::NOT_YET;
                return true;
            }
        }

        virtual BehaviorProcess Update() override{
            if(current_state_ == TaskCheck::FAIL){
                return BehaviorProcess::FAILURE;
            } else if(current_state_ == TaskCheck::BUSY){
                return BehaviorProcess::BUSY;
            } else if(current_state_ == TaskCheck::EXECUTE){
                return BehaviorProcess::RUNNING;
            } else if(current_state_ == TaskCheck::FINISHED){
                return BehaviorProcess::SUCCESS;
            } else {
                return chassis_executor_->Update();
            }
        }

    protected:
        TaskCheck current_state_;
        double distance_;
        ros::Time execution_time_;
        ros::Duration timeout_;
};




}




#endif
