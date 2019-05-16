//
// Created by arbiter95 on 2019-03-16.
// this hpp refferd by yolo_console_dll.cpp
//
#include "pch.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <thread>
#include <atomic>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include "/home/nvidia/robomaster_extra/darknet/include/yolo_v2_class.hpp"

#ifndef PROJECT_CUDA_DETECTION_HPP
#define PROJECT_CUDA_DETECTION_HPP

#ifdef OPENCV
#include <opencv2/opencv.hpp>            // C++
#include <opencv2/core/version.hpp>
#ifndef CV_VERSION_EPOCH
#include <opencv2/videoio/videoio.hpp>
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_MAJOR)"" CVAUX_STR(CV_VERSION_MINOR)"" CVAUX_STR(CV_VERSION_REVISION)
#ifndef USE_CMAKE_LIBS
#pragma comment(lib, "opencv_world" OPENCV_VERSION ".lib")
#ifdef TRACK_OPTFLOW
#pragma comment(lib, "opencv_cudaoptflow" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_cudaimgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif    // TRACK_OPTFLOW
#endif    // USE_CMAKE_LIBS
#else
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_EPOCH)"" CVAUX_STR(CV_VERSION_MAJOR)"" CVAUX_STR(CV_VERSION_MINOR)
#ifndef USE_CMAKE_LIBS
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif    // USE_CMAKE_LIBS
#endif    // CV_VERSION_EPOCH

using namespace darknet;

class track_kalman {
public:
    cv::KalmanFilter kf;
    int state_size, meas_size, contr_size;


    track_kalman(int _state_size = 10, int _meas_size = 10, int _contr_size = 0)
        : state_size(_state_size), meas_size(_meas_size), contr_size(_contr_size)
    {
        kf.init(state_size, meas_size, contr_size, CV_32F);

        cv::setIdentity(kf.measurementMatrix);
        cv::setIdentity(kf.measurementNoiseCov, cv::Scalar::all(1e-1));
        cv::setIdentity(kf.processNoiseCov, cv::Scalar::all(1e-5));
        cv::setIdentity(kf.errorCovPost, cv::Scalar::all(1e-2));
        cv::setIdentity(kf.transitionMatrix);
    }

    void set(std::vector<bbox_t> result_vec) {
        for (size_t i = 0; i < result_vec.size() && i < state_size*2; ++i) {
            kf.statePost.at<float>(i * 2 + 0) = result_vec[i].x;
            kf.statePost.at<float>(i * 2 + 1) = result_vec[i].y;
        }
    }

    // Kalman.correct() calculates: statePost = statePre + gain * (z(k)-measurementMatrix*statePre);
    // corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    std::vector<bbox_t> correct(std::vector<bbox_t> result_vec) {
        cv::Mat measurement(meas_size, 1, CV_32F);
        for (size_t i = 0; i < result_vec.size() && i < meas_size * 2; ++i) {
            measurement.at<float>(i * 2 + 0) = result_vec[i].x;
            measurement.at<float>(i * 2 + 1) = result_vec[i].y;
        }
        cv::Mat estimated = kf.correct(measurement);
        for (size_t i = 0; i < result_vec.size() && i < meas_size * 2; ++i) {
            result_vec[i].x = estimated.at<float>(i * 2 + 0);
            result_vec[i].y = estimated.at<float>(i * 2 + 1);
        }
        return result_vec;
    }

    // Kalman.predict() calculates: statePre = TransitionMatrix * statePost;
    // predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
    std::vector<bbox_t> predict() {
        std::vector<bbox_t> result_vec;
        cv::Mat control;
        cv::Mat prediction = kf.predict(control);
        for (size_t i = 0; i < prediction.rows && i < state_size * 2; ++i) {
            result_vec[i].x = prediction.at<float>(i * 2 + 0);
            result_vec[i].y = prediction.at<float>(i * 2 + 1);
        }
        return result_vec;
    }

};




class extrapolate_coords_t {
public:
    std::vector<bbox_t> old_result_vec;
    std::vector<float> dx_vec, dy_vec, time_vec;
    std::vector<float> old_dx_vec, old_dy_vec;

    void new_result(std::vector<bbox_t> new_result_vec, float new_time) {
        old_dx_vec = dx_vec;
        old_dy_vec = dy_vec;
        if (old_dx_vec.size() != old_result_vec.size()) std::cout << "old_dx != old_res \n";
        dx_vec = std::vector<float>(new_result_vec.size(), 0);
        dy_vec = std::vector<float>(new_result_vec.size(), 0);
        update_result(new_result_vec, new_time, false);
        old_result_vec = new_result_vec;
        time_vec = std::vector<float>(new_result_vec.size(), new_time);
    }

    void update_result(std::vector<bbox_t> new_result_vec, float new_time, bool update = true) {
        for (size_t i = 0; i < new_result_vec.size(); ++i) {
            for (size_t k = 0; k < old_result_vec.size(); ++k) {
                if (old_result_vec[k].track_id == new_result_vec[i].track_id && old_result_vec[k].obj_id == new_result_vec[i].obj_id) {
                    float const delta_time = new_time - time_vec[k];
                    if (abs(delta_time) < 1) break;
                    size_t index = (update) ? k : i;
                    float dx = ((float)new_result_vec[i].x - (float)old_result_vec[k].x) / delta_time;
                    float dy = ((float)new_result_vec[i].y - (float)old_result_vec[k].y) / delta_time;
                    float old_dx = dx, old_dy = dy;

                    // if it's shaking
                    if (update) {
                        if (dx * dx_vec[i] < 0) dx = dx / 2;
                        if (dy * dy_vec[i] < 0) dy = dy / 2;
                    } else {
                        if (dx * old_dx_vec[k] < 0) dx = dx / 2;
                        if (dy * old_dy_vec[k] < 0) dy = dy / 2;
                    }
                    dx_vec[index] = dx;
                    dy_vec[index] = dy;

                    //if (old_dx == dx && old_dy == dy) std::cout << "not shakin \n";
                    //else std::cout << "shakin \n";

                    if (dx_vec[index] > 1000 || dy_vec[index] > 1000) {
                        //std::cout << "!!! bad dx or dy, dx = " << dx_vec[index] << ", dy = " << dy_vec[index] <<
                        //    ", delta_time = " << delta_time << ", update = " << update << std::endl;
                        dx_vec[index] = 0;
                        dy_vec[index] = 0;
                    }
                    old_result_vec[k].x = new_result_vec[i].x;
                    old_result_vec[k].y = new_result_vec[i].y;
                    time_vec[k] = new_time;
                    break;
                }
            }
        }
    }

    std::vector<bbox_t> predict(float cur_time) {
        std::vector<bbox_t> result_vec = old_result_vec;
        for (size_t i = 0; i < old_result_vec.size(); ++i) {
            float const delta_time = cur_time - time_vec[i];
            auto &bbox = result_vec[i];
            float new_x = (float) bbox.x + dx_vec[i] * delta_time;
            float new_y = (float) bbox.y + dy_vec[i] * delta_time;
            if (new_x > 0) bbox.x = new_x;
            else bbox.x = 0;
            if (new_y > 0) bbox.y = new_y;
            else bbox.y = 0;
        }
        return result_vec;
    }

};


void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names,
    int current_det_fps = -1, int current_cap_fps = -1)
{
    int const colors[6][3] = { { 1,0,1 },{ 0,0,1 },{ 0,1,1 },{ 0,1,0 },{ 1,1,0 },{ 1,0,0 } };

    for (auto &i : result_vec) {
        cv::Scalar color = obj_id_to_color(i.obj_id);
        cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 2);
        if (obj_names.size() > i.obj_id) {
            std::string obj_name = obj_names[i.obj_id];
            if (i.track_id > 0) obj_name += " - " + std::to_string(i.track_id);
            cv::Size const text_size = getTextSize(obj_name, cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, 2, 0);
            int const max_width = (text_size.width > i.w + 2) ? text_size.width : (i.w + 2);
            cv::rectangle(mat_img, cv::Point2f(std::max((int)i.x - 1, 0), std::max((int)i.y - 30, 0)),
                cv::Point2f(std::min((int)i.x + max_width, mat_img.cols-1), std::min((int)i.y, mat_img.rows-1)),
                color, CV_FILLED, 8, 0);
            putText(mat_img, obj_name, cv::Point2f(i.x, i.y - 10), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, cv::Scalar(0, 0, 0), 2);
        }
    }
    if (current_det_fps >= 0 && current_cap_fps >= 0) {
        std::string fps_str = "FPS detection: " + std::to_string(current_det_fps) + "   FPS capture: " + std::to_string(current_cap_fps);
        putText(mat_img, fps_str, cv::Point2f(10, 20), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, cv::Scalar(50, 255, 0), 2);
    }
}
#endif    // OPENCV


static void show_console_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
    for (auto &i : result_vec) {
        if (obj_names.size() > i.obj_id) std::cout << obj_names[i.obj_id] << " - ";
        std::cout << "obj_id = " << i.obj_id << ",  x = " << i.x << ", y = " << i.y
                  << ", w = " << i.w << ", h = " << i.h
                  << std::setprecision(3) << ", prob = " << i.prob << std::endl;
    }
}

static std::vector<std::string> objects_names_from_file(std::string const filename) {
    std::ifstream file(filename);
    std::vector<std::string> file_lines;
    if (!file.is_open()) return file_lines;
    for(std::string line; getline(file, line);) file_lines.push_back(line);
    std::cout << "object names loaded \n";
    return file_lines;
}


static void CUDA_Detect_VisionDataet( std::vector<bbox_t> detect_Data , VisionDataset dataset ){

    int count_enemy = 0;
    int detection_num = 0;
    for (auto &i : detect_Data) {
       //cv::Scalar color = obj_id_to_color(i.obj_id);
       //cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 2);  //이 둘다 필요없는것.
       if (i.prob > confThreshold) {
            if ( i.obj_id == enemy_id ) {
                count_enemy = count_enemy + 1;
                detection_num = detection_num +1 ;
                dataset.height[count_enemy] = i.h;
                dataset.width[count_enemy] = i.w;
                dataset.Center_X[count_enemy] = i.x + 0.5*(i.w);
                dataset.Center_Y[count_enemy] = i.y + 0.5*(i.h);

            }
            else{
                detection_num = detection_num +1;

                dataset.height[0] = i.h;
                dataset.width[0] = i.w;
                dataset.Center_X[0] = i.x + 0.5*(i.w);
                dataset.Center_Y[0] = i.y + 0.5*(i.h);


            }
       }
    }

    dataset.number_of_detection = detection_num;





}




/* how to use this file on computer? */

/*
#ifdef ITMUSTNOTDEFINE

// insert file name
    std::string  names_file = "data/coco.names";
    std::string  cfg_file = "cfg/yolov3.cfg";
    std::string  weights_file = "yolov3.weights";
    std::string filename;





#endif
*/
#endif //PROJECT_CUDA_DETECTION_HPP
