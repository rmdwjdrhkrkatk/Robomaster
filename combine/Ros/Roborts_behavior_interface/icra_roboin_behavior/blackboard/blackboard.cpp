#include "blackboard.h"
#define ROBOT_PERIMETER 300     //300 is average distance of robot surface to robot center in milimeters



namespace icra_roboin_behavior{



Blackboard::Blackboard(): is_enemy_detected_(false),
                            behavior_style_(icra_roboin_behavior::BehaviorStyle::STOP),
                            behavior_state_(icra_roboin_behavior::BehaviorState::IDLE)
{
    ros::NodeHandle nh;
    sub_ = nh.subscribe("enemy_info",5,&Blackboard::EnemyDetectionCB,this);
    tf_ptr_ = std::make_shared<tf::TransformListener>(ros::Duration(10));
    
    
    
}

//todo
int Blackboard::GetStartTime() {return game_start_timestamp_;}
int Blackboard::GetDefenseTimeLeft() {return defense_time_left_;}
bool Blackboard::HasDefenseBonus() {return has_defense_bonus_;}
//


const geometry_msgs::PoseStamped Blackboard::GetMyPose(){
    UpdateMyPose();
    return my_pose_;
}

geometry_msgs::PoseStamped Blackboard::GetEnemyPose(int enemy_index) const{
    switch(enemy_index){
        case 0:
            return ally_pose_from_vision_;
        case 1:
            return enemy_pose_1_ghost_;
        case 2:
            return enemy_pose_2_ghost_;
        default:
            throw "blackboard GetEnemyPose error: invalid enemy index!";
    }
}

int Blackboard::GetEnemyNumber() const {
    return number_of_enemy_;
}

geometry_msgs::PoseStamped Blackboard::GetGoalPose() const{
    return goal_pose_;
}

geometry_msgs::PoseStamped Blackboard::GetGoalPoseQuaternion() const{
    geometry_msgs::PoseStamped goal_pose_q;
    goal_pose_q.header=goal_pose_.header;
    goal_pose_q.pose.position.x=goal_pose_.pose.position.x;
    goal_pose_q.pose.position.y=goal_pose_.pose.position.y;
    goal_pose_q.pose.position.z=1;
    goal_pose_q.pose.orientation = tf::createQuaternionMsgFromYaw(goal_pose_.pose.position.z);
    return goal_pose_q;
}

bool Blackboard::IsNewGoalPose() {
    if(is_new_goal_pose_){
        is_new_goal_pose_ = false;
        return true;
    } else {
        return false;
    }
}

bool Blackboard::IsEnemyDetected(int enemy_index) { //enemy_index 0:  all enemy, 1: enemy1. 2: enemy2
    switch(enemy_index){
        case 0:
            return is_enemy_detected_;
        case 1:
            return is_enemy_1_detected_;
        case 2:
            return is_enemy_2_detected_;
        default:
            throw "blackboard IsEnemyDetected error: invalid enemy index!";
    }
}




void Blackboard::UpdateMyPose() {
    tf::Stamped<tf::Pose> my_tf_pose;
    my_tf_pose.setIdentity();
    my_tf_pose.frame_id_="base_link";
    my_tf_pose.stamp_=ros::Time();
    try {
        geometry_msgs::PoseStamped my_pose;
        tf::poseStampedTFToMsg(my_tf_pose,my_pose);
        tf_ptr_ -> transformPose("map", my_pose, my_pose_);
    }
    catch (tf::LookupException& ex) {
        ROS_ERROR("blackboard UpdateMyPose error :%s", ex.what());
    }
}



void Blackboard::EnemyAlert(){
//TODO
}




icra_roboin_behavior::BehaviorStyle Blackboard::GetBehaviorStyle(){
    return behavior_style_;
}
icra_roboin_behavior::BehaviorState Blackboard::GetBehaviorState(){
    return behavior_state_;
}


void Blackboard::SetGoalPose(const geometry_msgs::PoseStamped new_goal_pose){
    goal_pose_ = new_goal_pose;
    is_new_goal_pose_ = true;
}
void Blackboard::SetBehaviorStyle(const icra_roboin_behavior::BehaviorStyle new_style){
    behavior_style_ = new_style;
}
void Blackboard::SetBehaviorState(const icra_roboin_behavior::BehaviorState new_state){
    behavior_state_ = new_state;
}













void Blackboard::EnemyDetectionCB(const icra_roboin_msgs::YoloDetectionInfo::ConstPtr& yolo){
    //TODO change camera frame id from base_link to camera link
    if (yolo->number_of_detection != 0){
        number_of_enemy_ = 0;
        /////////////////////////
        //index [0]  :  ally/////
        if(yolo->enemy_detected[0] == 1){
            is_enemy_detected_ = false;
            //tf transform code
            tf::Stamped<tf::Pose> ally_cam_tf, ally_global_tf;
            geometry_msgs::PoseStamped ally_cam_pose, ally_global_pose;
            ally_cam_pose.header.frame_id="base_link";
            ally_cam_pose.header.stamp = yolo->stamp;
            ally_cam_pose.pose.position.z = (float(yolo->distance[0])+ROBOT_PERIMETER)/1000 * std::sin((float(yolo->angle_verti[0]) / 100)*3.141592/180);
            double flat_d =( (float(yolo->distance[0])+ROBOT_PERIMETER)/1000 * std::cos((float(yolo->angle_verti[0]) / 100)*3.141592/180) ); 
            ally_cam_pose.pose.position.x = flat_d * std::cos((-1*float(yolo->angle_hori[0]) / 100)*3.141592/180);
            ally_cam_pose.pose.position.y = flat_d * std::sin((-1*float(yolo->angle_hori[0]) / 100)*3.141592/180);

            tf::Quaternion quaternion = tf::createQuaternionFromYaw((-1*float(yolo->angle_hori[0]) / 100)*3.141592/180);
            ally_cam_pose.pose.orientation.w=quaternion.w();
            ally_cam_pose.pose.orientation.x=quaternion.x();
            ally_cam_pose.pose.orientation.y=quaternion.y();
            ally_cam_pose.pose.orientation.z=quaternion.z();

            tf::poseStampedMsgToTF(ally_cam_pose, ally_cam_tf);
            ally_cam_tf.stamp_ = ros::Time(0);
            try
            {
                tf_ptr_->transformPose("map",ally_cam_tf,ally_global_tf);
                tf::poseStampedTFToMsg(ally_global_tf,ally_global_pose);
                ally_pose_from_vision_ = ally_global_pose;
            }
            catch (tf::TransformException& ex) {
                ROS_ERROR("blackboard enemy detection callback tf error");
            }
        }
        /////////////////////////
        /////////////////////////


        /////////////////////////
        //index [1]  :  enemy 1//
        if(yolo->enemy_detected[1] == 1){
            is_enemy_detected_ = true;
            is_enemy_1_detected_ = true;
            EnemyAlert();
            ROS_INFO("Enemy 1 Detected!");
            number_of_enemy_++;
            //tf transform code
            tf::Stamped<tf::Pose> enemy1_cam_tf, enemy1_global_tf;
            geometry_msgs::PoseStamped enemy1_cam_pose, enemy1_global_pose;
            enemy1_cam_pose.header.frame_id="base_link";
            enemy1_cam_pose.header.stamp = yolo->stamp;
            enemy1_cam_pose.pose.position.z = (float(yolo->distance[1])+ROBOT_PERIMETER)/1000 * std::sin((float(yolo->angle_verti[1]) / 100)*3.141592/180);
            double flat_d = ( (float(yolo->distance[1])+ROBOT_PERIMETER)/1000 * std::cos((float(yolo->angle_verti[1]) / 100)*3.141592/180) ) ;   
            enemy1_cam_pose.pose.position.x = flat_d * std::cos((-1*float(yolo->angle_hori[1]) / 100)*3.141592/180);
            enemy1_cam_pose.pose.position.y = flat_d * std::sin((-1*float(yolo->angle_hori[1]) / 100)*3.141592/180);

            tf::Quaternion quaternion = tf::createQuaternionFromYaw((-1*float(yolo->angle_hori[1]) / 100)*3.141592/180);
            enemy1_cam_pose.pose.orientation.w=quaternion.w();
            enemy1_cam_pose.pose.orientation.x=quaternion.x();
            enemy1_cam_pose.pose.orientation.y=quaternion.y();
            enemy1_cam_pose.pose.orientation.z=quaternion.z();

            tf::poseStampedMsgToTF(enemy1_cam_pose, enemy1_cam_tf);
            enemy1_cam_tf.stamp_ = ros::Time(0);
            try
            {
                tf_ptr_->transformPose("map",enemy1_cam_tf,enemy1_global_tf);
                tf::poseStampedTFToMsg(enemy1_global_tf,enemy1_global_pose);
                enemy_pose_1_ = enemy1_global_pose;
                enemy_pose_1_ghost_ = enemy_pose_1_;
            }
            catch (tf::TransformException& ex) {
                ROS_ERROR("blackboard enemy detection callback tf error");
            }
        } else {
            is_enemy_1_detected_ = false;
        }
        /////////////////////////
        /////////////////////////


        /////////////////////////
        //index [2]  :  enemy 2//
        if(yolo->enemy_detected[2]==1){
            is_enemy_detected_ = true;
            EnemyAlert();
            ROS_INFO("Enemy 2 Detected!");
            number_of_enemy_++;
            //tf transform code
            tf::Stamped<tf::Pose> enemy2_cam_tf, enemy2_global_tf;
            geometry_msgs::PoseStamped enemy2_cam_pose, enemy2_global_pose;
            enemy2_cam_pose.header.frame_id="base_link";
            enemy2_cam_pose.header.stamp = yolo->stamp;
            enemy2_cam_pose.pose.position.z = (float(yolo->distance[2])+ROBOT_PERIMETER)/1000 * std::sin((float(yolo->angle_verti[2]) / 100)*3.141592/180);
            double flat_d =( (float(yolo->distance[1])+ROBOT_PERIMETER)/1000 * std::cos((float(yolo->angle_verti[2]) / 100)*3.141592/180) );  
            enemy2_cam_pose.pose.position.x = flat_d * std::cos((-1*float(yolo->angle_hori[2]) / 100)*3.141592/180);
            enemy2_cam_pose.pose.position.y = flat_d * std::sin((-1*float(yolo->angle_hori[2]) / 100)*3.141592/180);

            tf::Quaternion quaternion = tf::createQuaternionFromYaw((-1*float(yolo->angle_hori[2]) / 100)*3.141592/180);
            enemy2_cam_pose.pose.orientation.w=quaternion.w();
            enemy2_cam_pose.pose.orientation.x=quaternion.x();
            enemy2_cam_pose.pose.orientation.y=quaternion.y();
            enemy2_cam_pose.pose.orientation.z=quaternion.z();

            tf::poseStampedMsgToTF(enemy2_cam_pose, enemy2_cam_tf);
            enemy2_cam_tf.stamp_ = ros::Time(0);
            try
            {
                tf_ptr_->transformPose("map",enemy2_cam_tf,enemy2_global_tf);
                tf::poseStampedTFToMsg(enemy2_global_tf,enemy2_global_pose);
                enemy_pose_2_ = enemy2_global_pose;
                enemy_pose_2_ghost_ = enemy_pose_2_;
            }
            catch (tf::TransformException& ex) {
                ROS_ERROR("blackboard enemy detection callback tf error");
            }
        } else {
            is_enemy_2_detected_ = false;
        }
        /////////////////////////
        /////////////////////////

    } else {
        is_enemy_detected_ = false;
        is_enemy_1_detected_ = false;
        is_enemy_2_detected_ = false;
        number_of_enemy_ = 0;
    }
}















}