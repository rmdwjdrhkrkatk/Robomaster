cmake_minimum_required(VERSION 2.8.3)
project(roborts_gazebo)

add_definitions(-std=c++11)

find_package(gazebo REQUIRED)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	message_generation 
	geometry_msgs 
	std_msgs 
	sensor_msgs
  gazebo_ros
)

find_package(Boost REQUIRED COMPONENTS system)
catkin_package(
  LIBRARIES roborts_gazebo
  CATKIN_DEPENDS message_generation
  roscpp 
  geometry_msgs 
  rospy
  DEPENDS Boost gazebo_ros
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS} 
  ${Boost_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  )

link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")


add_library(RealSensePlugin SHARED 
   src/RealSensePlugin.cc
 )

target_link_libraries(RealSensePlugin ${GAZEBO_libraries})
