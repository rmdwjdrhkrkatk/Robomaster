cmake_minimum_required(VERSION 2.8.3)
project(icra_roboin_msgs)

find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
  nav_msgs
  geometry_msgs
  actionlib
  message_generation
)

add_message_files(
  DIRECTORY msg
  FILES
  YoloDetectionInfo.msg
)

add_service_files(
  DIRECTORY srv
  FILES
  BlackboardGeneralInfo.srv
  BehaviorStyleSet.srv
  SetGoal_2.srv
)

add_action_files(
  DIRECTORY action
  FILES
  YoloDetection.action
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  nav_msgs
  actionlib_msgs
)


catkin_package(CATKIN_DEPENDS actionlib_msgs message_runtime)



