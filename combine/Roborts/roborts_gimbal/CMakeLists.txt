cmake_minimum_required(VERSION 2.8.3)
project(roborts_gimbal)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  roscpp
  actionlib
  cv_bridge
  image_transport
  sensor_msgs
  control_msgs
  geometry_msgs
  roborts_msgs
  std_msgs
  gazebo_msgs
)

find_package(gazebo REQUIRED)

# find_package(OpenCV REQUIRED 
#     COMPONENTS
#     opencv_highgui)

catkin_package(
  DEPENDS
    roscpp
    gazebo_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_library(gazebo_shooter_plugin src/gazebo_shooter.cc)

add_executable(angle_to_command src/angle_to_command.cpp)
target_link_libraries(angle_to_command
  ${catkin_LIBRARIES})

add_executable(gimbal_test_node src/gimbal_test.cpp)
target_link_libraries(gimbal_test_node
  ${catkin_LIBRARIES})


# ### INSTALL ###

# install(TARGETS look_to_point
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )