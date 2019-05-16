//V3.01
#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP


#include "pch.hpp"
#include "Data_control.hpp"
#include "Vision_ros.hpp"

#ifdef ADD_DEEPLEARNING
#include "object_detection.hpp"
//#include "/home/nvidia/robomaster_extra/darknet/include/yolo_v2_class.hpp"
#endif

inline bool exists_test3(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

/*this class manage realsense camera or GZbot vertual camera*/
class vision_camera {
public:
#ifndef VIRTUAL
    //for real world, realsense camera use
    rs2::context ctx;
    rs2::device_list list;
    rs2::colorizer color_map;
    rs2::pipeline pipe;
    rs2::config cfg;
    rs2::pipeline_profile profile;
    cv::Mat frame_to_mat(const rs2::frame &f);
	cv::Mat depth_frame_to_meters(const rs2::pipeline& pipe, const rs2::depth_frame& f);


#else
//GZbot code

#endif

private:
    int Width = 640;
    int Height = 480;

    int numberofimg;
    
#ifdef MAKEING_IMG
    //for read img files to continue image write
    int find_img_number();
#endif
	/*directly get distance data*/
    float VisionDataset_avoid_zero(short x, short y, data_control& CT_data);
	/*the simple linial align, this function is made for realsense D435 and I was get data form experiment*/  //if you want to more exact data, then try search "librealsense align"
	float linial_align(short RGB_X, short RGB_Y, data_control& CT_data);

public:
    /*camera class init*/
    vision_camera(const ros::NodeHandle &nh) {
        this->numberofimg = 1;
#ifndef VIRTUAL

        this->list = this->ctx.query_devices();
        if (this->list.size() == 0) {
            throw std::runtime_error("vision: Device not found");
        }

        cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);

        this->cfg.enable_stream(RS2_STREAM_COLOR, this->Width, this->Height, RS2_FORMAT_BGR8, 60);
        this->cfg.enable_stream(RS2_STREAM_DEPTH, this->Width, this->Height, RS2_FORMAT_Z16, 60);
        this->profile = this->pipe.start(this->cfg);

#ifdef DEBUG
        std::cout << "vision_camera initialized" << std::endl;
#endif //!DEBUG


#else
        // for GZbot code
                ImageConverter sim_img(nh);
                DepthConverter sim_depth(nh);
#endif //!VIRTUAL
    }

    /*delete camera class*/
    ~vision_camera() = default;

    /*running camera*/
    void vision_camera_run(data_control &CT_data);
   
    /*get depth data*/
    void VisionDataset_getDepth(data_control &CT_data);
    /*for making lable img*/
    void making_img(data_control &CT_data);

};

cv::Mat vision_camera::frame_to_mat(const rs2::frame& f)
{
    using namespace cv;
    using namespace rs2;
    auto vf = f.as<video_frame>();
    const int w = vf.get_width();
    const int h = vf.get_height();
    if (f.get_profile().format() == RS2_FORMAT_BGR8)
    {
        return Mat(Size(w, h), CV_8UC3, (void*)f.get_data(), Mat::AUTO_STEP);
    }
    else if (f.get_profile().format() == RS2_FORMAT_RGB8)
    {
        auto r = Mat(Size(w, h), CV_8UC3, (void*)f.get_data(), Mat::AUTO_STEP);
        cvtColor(r, r, CV_RGB2BGR);
        return r;
    }
    else if (f.get_profile().format() == RS2_FORMAT_Z16)
    {
        return Mat(Size(w, h), CV_16UC1, (void*)f.get_data(), Mat::AUTO_STEP);
    }
    else if (f.get_profile().format() == RS2_FORMAT_Y8)
    {
        return Mat(Size(w, h), CV_8UC1, (void*)f.get_data(), Mat::AUTO_STEP);
    }
    throw std::runtime_error("Frame format is not supported yet!");	}

cv::Mat vision_camera::depth_frame_to_meters(const rs2::pipeline& pipe, const rs2::depth_frame& f)
{
	using namespace cv;
	using namespace rs2;

	Mat dm = frame_to_mat(f);
	dm.convertTo(dm, CV_64F);
	auto depth_scale = pipe.get_active_profile()
		.get_device()
		.first<depth_sensor>()
		.get_depth_scale();
	dm = dm * depth_scale;
	return dm;
}

float vision_camera::VisionDataset_avoid_zero(short x, short y, data_control& CT_data) {
    //to use this function, x andy must be larger then 3 and smaler than Max-3
    float Depth = 0;
    float tem_Depth = 0;
    short i = 0;
    short j = 0;
    short count = 0;
    for (i = x; i < x + 3; i++) {
        for (j = y; j < y + 3; j++) {
            tem_Depth = CT_data.dataset.depth_img.at<double>((i - 1), (j - 1));  //opencv_depth frame 
            if (tem_Depth > 0) {
                count++;
                Depth = Depth + tem_Depth;
            }
        }
    }
    if (count > 0) {
        Depth = Depth / count;
        return Depth;
    }
    else {
#ifdef DEBUG
        std::cout << "(VisionDataset_avoid_zero) distance is zero" << std::endl;
#endif
        return 0;
    }
}

int vision_camera::find_img_number() {
    std::cout << "try to read the last number of img" << std::endl;
    std::ostringstream check_name; //
    int number = 1;
    int numberofimg2 = 1;
    bool flag = true;
    while (flag) {
		check_name.str("");
		check_name.clear();
        if (numberofimg2 < 10) {
            check_name << "home/nvidia/img/" << "0000" << number << ".jpg";
        }
        else if (9 < numberofimg2 < 100) {
            check_name << "home/nvidia/img/" << "000" << number << ".jpg";
        }
        else if (99 < numberofimg2 < 1000) {
            check_name << "home/nvidia/img/" << "00" << number << ".jpg";
        }
        else if (999 < numberofimg2 < 10000) {
            check_name << "home/nvidia/img/" << "0" << number << ".jpg";
        }
        else {
            check_name << "home/nvidia/img/" << number << ".jpg";
        }
        number++;

        flag = exists_test3(check_name.str());
    }
    return number;
}

void vision_camera::vision_camera_run(data_control& CT_data) {

#ifndef VIRTUAL
    while (true) {
        rs2::frameset data = this->pipe.wait_for_frames();
        rs2::video_frame color_frame = data.get_color_frame();
        rs2::depth_frame depth_frame = data.get_depth_frame();
        if (!(depth_frame) || !(color_frame)) {
            continue;  // frame check based on buffer
        }
        CT_data.dataset.detectimg = this->frame_to_mat(color_frame);
		CT_data.dataset.depth_img = this->depth_frame_to_meters(this->pipe, depth_frame);

		

        break; //get new frame
    }
#else
    //insert GZbot code
		CT_data.dataset.detectimg = sim_img.GetImage(); // ros image get
#endif //!VIRTUAL

#ifdef DISPLAY
    CT_data.dataset.display = CT_data.dataset.detectimg; //making display image
#endif //!DISPLAY
}

float vision_camera::linial_align(short RGB_X, short RGB_Y, data_control& CT_data) {
    // based on 3m > 6 pixel moved and it is for 640*480
    short fake_depth_x = (RGB_X * 0.63125 + 112);

    short real_depth_y = (RGB_Y * 0.63125 + 88.5);
    float fake_distance = this->VisionDataset_avoid_zero(fake_depth_x, real_depth_y,CT_data);
    float distance = 0;


    if (fake_distance > 0) {
        short move_pixel = (17.72 / fake_distance);
        short real_depth_x = (RGB_X * 0.63125 + 118 - move_pixel);
        distance = this->VisionDataset_avoid_zero(real_depth_x, real_depth_y,CT_data);
    }

#ifdef DEBUG
    if (distance == 0) {
			std::cout << "(linial_align)_fail to get distance / distance = 0" << std::endl;
		}
#endif //!DEBUG
    return distance;
}

void vision_camera::VisionDataset_getDepth(data_control &CT_data) {
#ifndef VIRTUAL
    for (int index = 0; index < 6; index++) {
        if (CT_data.dataset.Center_X[index] > 0 && CT_data.dataset.Center_Y[index] > 0) {
            CT_data.dataset.distance[index] = this->linial_align(CT_data.dataset.Center_X[index], CT_data.dataset.Center_Y[index],CT_data);
            // std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  // we don`t need it reight now.
        }
    }
#else
    for (int index = 0; index < 6; index++) {
                if (CT_data.dataset.Center_X[index] > 0 && CT_data.dataset.Center_Y[index] > 0) {
                    CT_data.dataset.distance[index] = sim_depth.getDepthdata(dataset.Center_X[index], dataset.Center_Y[index]); // get depth data form slim
                    // std::cerr << index + 1 <<": distance info (m) : " << dataset.distance[index] << std::endl;  // we don`t need it reight now.
                }
                //GZbot code will insert
        }
#endif //!VIRTUAL
}

void vision_camera::making_img(data_control &CT_data) {
#ifdef MAKEING_IMG //this fucntion is making a img
    std::ostringstream img_name; // this is making img`s name
        char flag = 'n';
        if (this->numberofimg == 1) {
			std::cout << "wellcome to image making world!!" << std::endl;
            std::cout << "start making image "<< std::endl;
            std::cout << "if you want to continue form last img type (y) , start from 00001.jpg type (n) " << std::endl;
			std::cout << "enter yout answer" << std::endl;
            while (true) {
                std::cin >> flag;
                if (flag == 'n') {
                    std::cout << "directly start with number 00001.jpg" << std::endl;
                    break;
                }
                else if (flag == 'y') {
                    this->numberofimg = this->find_img_number(); //fine last number of img
                    std::cout << "the image file makeing is start form" <<this->numberofimg << ".jpg" << std::endl;
                    break;
                }
            }
        }


        try
        {
            if (this->numberofimg < 10) {
                img_name << "home/nvidia/img/" << "0000" << this->numberofimg << ".jpg";
            }
            else if (9 < this->numberofimg < 100) {
                img_name << "home/nvidia/img/" << "000" <<this-> numberofimg << ".jpg";
            }
            else if (99 < this->numberofimg < 1000) {
                img_name << "home/nvidia/img/" << "00" << this->numberofimg << ".jpg";
            }
            else if (999 < this->numberofimg < 10000) {
                img_name << "home/nvidia/img/" << "0" << this->numberofimg << ".jpg";
            }
            else {
                img_name << "home/nvidia/img/" <<this-> numberofimg << ".jpg";
            }
            this->numberofimg++;
            cv::imwrite(img_name.str(), CT_data.dataset.detectimg);
        }
        catch (cv::Exception& e)
        {
            std::cout << "error has been occured " << this->numberofimg - 1 << std::endl;
        }

#ifdef ADD_DEEPLEARNING  //this is for auto labeling when making image.

#endif //!ADD_DEEPLEARNING

#endif //!MAKEING_IMG
}

#endif //!CAMERA_HPP
