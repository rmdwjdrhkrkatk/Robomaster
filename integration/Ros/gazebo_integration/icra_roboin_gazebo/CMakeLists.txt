cmake_minimum_required(VERSION 2.8.3)
project(icra_roboin_gazebo)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  roscpp
  rospy
  message_generation
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
find_package(Boost REQUIRED COMPONENTS system)
find_package(gazebo REQUIRED)

# find_package(OpenCV REQUIRED 
#     COMPONENTS
#     opencv_highgui)

catkin_package(
  LIBRARIES roborts_gazebo
  CATKIN_DEPENDS message_generation
  roscpp 
  geometry_msgs
  rospy 
  DEPENDS
  roscpp
  gazebo_ros
  Boost
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)

include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(gazebo_shooter_plugin src/gazebo_shooter.cc)


add_executable(angle_to_command src/angle_to_command.cpp)
target_link_libraries(angle_to_command
  ${catkin_LIBRARIES})

add_executable(gimbal_test_node src/gimbal_test.cpp)
target_link_libraries(gimbal_test_node
  ${catkin_LIBRARIES})

add_executable(contact_to_damage src/contact_to_damage.cpp)
target_link_libraries(contact_to_damage
  ${catkin_LIBRARIES})
# ### INSTALL ###

# install(TARGETS look_to_point
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )
