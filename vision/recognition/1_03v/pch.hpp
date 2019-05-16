// ���̺귯�� ���հ��� �������

#ifndef PCH_HPP
#define PCH_HPP


/* ���� �ش� ���� ���� */

//c++�⺻ �������
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <cstring>     //kcftracking���� ����
#include <exception>


//deeplearning�� opencv�⺻ �������
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

//KCFtraking�� �������
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>  //opencv contrib module��ġ�� �ʿ��ϴ�. 
#include <opencv2/core/ocl.hpp>


//realsense�̿��ϱ� ���� �ش�����
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>

/* ���� ����ü ����*/

/* ���� ���� ���� ����*/
const float PI = 3.141592;

#endif