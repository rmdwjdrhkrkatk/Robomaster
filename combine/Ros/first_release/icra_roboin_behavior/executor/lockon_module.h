#ifndef ICRA_ROBOIN_BEHAVIOR_LOCKON_MODULE_H
#define ICRA_ROBOIN_BEHAVIOR_LOCKON_MODULE_H

#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "../tools.h"

namespace icra_roboin_behavior {



class LockonModule {
    public:
        LockonModule(Blackboard*& blackboard,
                    double dt = 0.1,double sentry_angle=0.7854): 
                                                            dt_(dt),blackboard_(blackboard),sentry_angle_(sentry_angle)
        {
            ros::NodeHandle nh;
            sub_ = nh.subscribe("omni_cmd_vel",1,&LockonModule::CB,this);
            pub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);
        }
        ~LockonModule() = default;

        void LockonInterface(const LockonMode mode, const double target){
            switch(mode){
                case LockonMode::ANGULAR_VEL:
                  //ROS_INFO("ANGVEL");
                  SetTargetAngularVelocity(target);
                  lockon_mode_ = mode;
                  break;
                case LockonMode::RELATIVE_ANGLE:
                  //ROS_INFO("RELANG");
                  SetTargetAngle(target);
                  lockon_mode_ = mode;
                  break;
                case LockonMode::RELATIVE_ANGLE_SENTRY:
                  //ROS_INFO("RELANGSEN");
                  SetTargetAngleSentryMode(target);
                  lockon_mode_ = mode;
                  break;              
                case LockonMode::GLOBAL_YAW:
                  //ROS_INFO("GLOYAW");
                  SetTargetGlobalYaw(target);
                  lockon_mode_ = mode;
                  break;
                case LockonMode::GLOBAL_YAW_SENTRY:
                  //ROS_INFO("GLOYAWSEN");
                  SetTargetGlobalYawSentryMode(target);
                  lockon_mode_ = mode;
                  break;
                default:
                    throw std::invalid_argument( "wrong lockon mode" );
                    ROS_ERROR("LockonModule error: wrong lockon mode");
                                  
            } 
        }

        void LockonInterface(const LockonMode mode, const PlayerType who){
            //ROS_INFO("TARGETENEM");
            if(mode != LockonMode::TARGET_ENEMY_LOCKON){
                    throw std::invalid_argument( "wrong lockon parameter" );
                    ROS_ERROR("LockonModule error: wrong lockon parameter with TARGET_ENEMY_LOCKON mode");
            } else {
                SetTargetEnemy(who);
            }
        }

        void LockonInterface(const LockonMode mode, const double x, const double y){
            //ROS_INFO("TARGETPOS");
            if(mode != LockonMode::TARGET_POSITION_LOCKON){
                    throw std::invalid_argument( "wrong lockon parameter" );
                    ROS_ERROR("LockonModule error: wrong lockon parameter with TARGET_POSITION_LOCKON mode");
            } else {
                SetTargetPosition(x,y);
            }
        }

        void LockonInterface(const LockonMode mode){
            //ROS_INFO("TARGETGOAL");
            if(mode != LockonMode::TARGET_GOAL_LOCKON){
                    throw std::invalid_argument( "wrong lockon parameter" );
                    ROS_ERROR("LockonModule error: wrong lockon parameter with TARGET_GOAL_LOCKON mode");
            } else {
                SetTargetGoal();
            }
        }

        LockonMode GetLockonMode() const {
            return lockon_mode_;
        }


    private:
        void SetTargetAngularVelocity(double target) {
            //ROS_INFO("target_ang_vel: %f",target);
            target_angular_velocity_ = target;
        }
        void SetTargetAngle(double target){
            target_angle_ = target;
            //ROS_INFO("target angle: %f",target);
            if(target > 0.1 | target < -0.1){
                SetTargetAngularVelocity( tools::Clip(2*target_angle_,-3.0,3.0) );
            } else {
                SetTargetAngularVelocity(0);
            }
            ///need PID control
        }

        void SetTargetAngleSentryMode(double target){
            target_angle_ = target;
            //ROS_INFO("sentry target angle: %f",target);

            if(target_angle_ < sentry_angle_ && target_angle_ > -1* sentry_angle_){
                if(target/sentry_angle_ > 0.9  )
                {
                    sentry_flag_ = 1;
                } else if ( target/sentry_angle_ < -0.9 ) {
                    sentry_flag_ = -1;
                }
                //ROS_INFO("%f, %f, %f, %f,%f,%d",sentry_flag_ * (0.3 + cos( 1.570796 * (target/sentry_angle_) )),target/sentry_angle_, target,sentry_angle_,target_angle_,sentry_flag_ );
                SetTargetAngularVelocity(sentry_flag_ * (0.3 + cos( 1.570796 * (target/sentry_angle_)) ));
            } else {
                SetTargetAngularVelocity( tools::Clip(2*target_angle_,-3.0,3.0) );
            }
            
        }

        void SetTargetGlobalYaw(double yaw) {
            SetTargetAngle( tools::GetShortestYawSigned(yaw,tools::GetYaw(blackboard_->GetMyPose())) );
        }

        void SetTargetGlobalYawSentryMode(double yaw) {
            //ROS_INFO("global_yaw_sentry: %f %f",yaw,tools::GetYaw(blackboard_->GetMyPose()));
            SetTargetAngleSentryMode( tools::GetShortestYawSigned(yaw,tools::GetYaw(blackboard_->GetMyPose())) );
        }

        void SetTargetEnemy(PlayerType who){
            if(who == PlayerType::ENEMY_ONE | who == PlayerType::ENEMY_TWO){
                auto enemy_pose = blackboard_->GetEnemyPose(who);
                auto my_pose = blackboard_->GetMyPose();
                SetTargetGlobalYaw( atan2((enemy_pose.pose.position.y - my_pose.pose.position.y), 
                                (enemy_pose.pose.position.x - my_pose.pose.position.x)) );
            } else {
                throw std::invalid_argument( "wrong enemy type" );
                ROS_ERROR("lockon module SetTargetEnemy error: wrong enemy type");
            }
        }

        void SetTargetPosition(double x, double y){
                auto my_pose = blackboard_->GetMyPose();
                SetTargetGlobalYaw( atan2((y - my_pose.pose.position.y), 
                                (x - my_pose.pose.position.x)) );
        }

        void SetTargetGoal(){
                auto goal = blackboard_ -> GetGoal();
                auto my_pose = blackboard_->GetMyPose();
                SetTargetGlobalYaw( atan2((goal.y - my_pose.pose.position.y), 
                                (goal.x - my_pose.pose.position.x)) );
        }






    private:
        Blackboard* const blackboard_;
        ros::Subscriber sub_;
        ros::Publisher pub_;
        void CB(const geometry_msgs::Twist::ConstPtr& msg) {
            
            geometry_msgs::Twist cmd;
            cmd.angular.z = target_angular_velocity_;
            //ROS_INFO("%f",cmd.angular.z);
            double det = pow(dt_ * cmd.angular.z , 2) + 4;
            double alpha = ( dt_ * dt_ * cmd.angular.z * (msg->angular.z) ) + 4;
            double beta = 2*dt_*(cmd.angular.z - (msg->angular.z));

            
            cmd.linear.x = ( (alpha * (msg->linear.x)) + (beta * (msg->linear.y)) ) / det;
            cmd.linear.y = ( (alpha * (msg->linear.y)) - (beta * (msg->linear.x)) ) / det;

            pub_.publish(cmd);
        }
        LockonMode lockon_mode_;
        double target_angle_=0;
        double target_angular_velocity_=0; //rad/sec
        const double dt_;
        const double sentry_angle_;
        int sentry_flag_ = 1;
};
        



}

#endif