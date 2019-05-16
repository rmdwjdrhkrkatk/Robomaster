cmake_minimum_required(VERSION 2.8.3)
project(icra_roboin_behavior)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  actionlib
  actionlib_msgs
  std_msgs
  geometry_msgs
  nav_msgs
  roborts_msgs
  roborts_common
  roborts_costmap
  icra_roboin_msgs

)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_executable(behavior_node
  enums.h
  behavior/move_behavior.h
  behavior/manual_speed_behavior.h
  behavior/manual_accel_behavior.h
  executor/chassis_executor.cpp
  executor/gimbal_executor.cpp
  blackboard/blackboard.cpp
  behavior_interface.cpp
  behavior_node.cpp
  )

target_link_libraries(behavior_node
  PRIVATE
  roborts_costmap
  ${catkin_LIBRARIES}
  )

add_dependencies(behavior_node
  roborts_msgs_generate_messages
  icra_roboin_msgs_generate_messages
  )







add_executable(behavior_test
  behavior_test.cpp
  )

target_link_libraries(behavior_test
  PRIVATE
  ${catkin_LIBRARIES}
  )
add_dependencies(behavior_test
  roborts_msgs_generate_messages
  icra_roboin_msgs_generate_messages
  )




