# cmake_minimum_required(VERSION <specify CMake version here>)
project(vision_dev)
CMAKE_MINIMUM_REQUIRED ( VERSION 2.9 )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module)
set(CMAKE_BUILD_TYPE Release)


add_executable(vision_dev vision_main.cpp)

link_libraries(vision_dev /usr/local/lib)
link_libraries(vision_dev /home/nvidia/robomaster_extra/darknet)


include_directories(vision_dev /home/nvidia/robomaster_extra/darknet/include)
include_directories(vision_dev /usr/local/include)


target_link_libraries(vision_dev "/usr/local/lib/libopencv_world.so")
target_link_libraries(vision_dev "/usr/local/lib/librealsense2.so")
target_link_libraries(vision_dev "/home/nvidia/robomaster_extra/darknet/libdarknet.so")