cmake_minimum_required(VERSION 2.8.3)
project(icra_roboin_simulation)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	nav_msgs
	sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_executable(stage_tf_remap
	src/stage_tf_remap.cpp
  )

target_link_libraries(stage_tf_remap
  PRIVATE
  ${catkin_LIBRARIES}
  )

