// 라이브러리 통합관리 헤더파일

#ifndef PCH_HPP
#define PCH_HPP


/* 통합 해더 파일 관리 */

//c++기본 헤더파일
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <cstring>     //kcftracking에도 사용됨
#include <exception>


//deeplearning과 opencv기본 헤더파일
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

//KCFtraking용 헤더파일
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>  //opencv contrib module설치가 필요하다. 
#include <opencv2/core/ocl.hpp>


//realsense이용하기 위한 해더파일
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>

/* 통합 구조체 관리*/

/* 통합 정적 변수 관리*/
const float PI = 3.141592;

#endif