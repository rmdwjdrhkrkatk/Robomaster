cmake_minimum_required(VERSION 2.8.3)
project(icra_roboin_detection)

SET(CMAKE_CXX_STANDARD 14)
SET(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OpenCV-3.4.5/share/OpenCV/)
SET(CMAKE_BUILD_TYPE Release)



find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf
  actionlib
  std_msgs
  sensor_msgs
  roborts_msgs
  icra_roboin_msgs
  )

find_package(OpenCV REQUIRED)


catkin_package(
  INCLUDE_DIRS
)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
 ${OpenCV_INCLUDE_DIRS}
)

add_executable(detection_node
  allign.hpp
  Cfg_robot.hpp
  cv-helper.hpp
  Data_Control.hpp
  detection.hpp
  KCFtraker.hpp
  pch.hpp
  SendData_Control.hpp
  vision_main.cpp
)

target_link_libraries(detection_node
  PRIVATE
  realsense2
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)
