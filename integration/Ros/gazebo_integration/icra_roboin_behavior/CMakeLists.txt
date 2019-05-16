cmake_minimum_required(VERSION 2.8.3)
project(icra_roboin_behavior)
set(CMAKE_CXX_STANDARD 14)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  actionlib
  actionlib_msgs
  std_msgs
  geometry_msgs
  nav_msgs
  roborts_msgs
  icra_roboin_msgs
  move_base
  move_base_msgs

)

include_directories(
  include
  behavior
  /home/kimtaehan/integration/src/icra_roboin_behavior/blackboard
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_executable(behavior_node
  enums.h
  blackboard/class.h
  executor/chassis_executor.cpp
  blackboard/blackboard.cpp
  behavior_interface.cpp
  behavior_node.cpp
  )

target_link_libraries(behavior_node
  PRIVATE
  ${catkin_LIBRARIES}
  )

add_dependencies(behavior_node
  roborts_msgs_generate_messages
  icra_roboin_msgs_generate_messages
  )









