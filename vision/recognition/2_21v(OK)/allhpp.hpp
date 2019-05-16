
//vision _ header files



#include "vision_src/Cfg_robot.hpp"
#include "vision_src/Data_Control.hpp"

#ifndef SIMULATION
#include "vision_src/detection.hpp"
#include "vision_src/KCFtraker.hpp"
#endif

#include "vision_src/pch.hpp"
#include "vision_src/SendData_Control.hpp"
#include "vision_src/CUDA_detection.hpp"




#ifdef ROS
#include "vision_src/vision_ros.hpp"
#endif

#ifdef SIMULATION
#include "vision_src/simulation_GZ.hpp"
#endif

//external _ header files

#include "extern_src/allign.hpp"
#include "extern_src/cv-helper.hpp"
