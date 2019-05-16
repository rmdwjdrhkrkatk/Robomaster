cmake_minimum_required(VERSION 2.8.3)
project(roborts_navigation)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  roscpp
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

include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_executable(contact_to_damage src/contact_to_damage.cpp)
target_link_libraries(contact_to_damage
  ${catkin_LIBRARIES})

