//main code
//2.22v
// made by Kwak dong hwan , Lee chang min, Lee hyun woo. 




//void postprocess(VisionDataset dataset, const vector<Mat> &outs  , Mat& detectimg);

#ifndef CUDA_YOLO

#define CUDA_YOLO    //if use this we can use darkent cuda+yolo version deeplearing

#endif



#ifndef OPENCV  //define opencv

#define OPENCV

#endif





/**************************************define what you want*************************************/

/***********************************************************************************************/

#define DISPLAY

#define ROS  //to build ROS

//#define DEBUG

//#define SIMULATION  //for simulation

//#define TRACKER // for tracking   (can`t use with simulation@@@@@@@@@@)

/***********************************************************************************************/





#include "allhpp.hpp"





using namespace darknet;



#ifndef SIMULATION

using namespace dnn;    //dnn function

#endif



using namespace std;    //cpp basic function









int main(int argc, char * argv[]) try

{







#ifdef ROS

    // ros init //

    ros::init(argc, argv, "vision_node");

    ros::NodeHandle nh;



    //	ros::ServiceClient cmd_shoot_client = nh.serviceClient<roborts_msgs::ShootCmd>("cmd_shoot");

    //	roborts_msgs::ShootCmd shoot_cmd;



    cmd_shoot_client = nh.serviceClient<roborts_msgs::ShootCmd>("cmd_shoot");



    ros::ServiceClient cmd_fric_whl_client = nh.serviceClient<roborts_msgs::FricWhl>("cmd_fric_wheel");

    setFricWhl(cmd_fric_whl_client);





    ros::Publisher cmd_gimbal_angle_pub = nh.advertise<roborts_msgs::GimbalAngle>("cmd_gimbal_angle", 1);

    ros::Publisher enemy_info_pub = nh.advertise<icra_roboin_msgs::YoloDetectionInfo>("enemy_info", 1);





    ros::ServiceServer yaw_server = nh.advertiseService("yaw_gain", &SetYawGainCallback);

    ros::ServiceServer pitch_server = nh.advertiseService("pitch_gain", &SetPitchGainCallback);

    // ros::Rate rate(10);



#ifdef SIMULATION

    ImageConverter sim_img(nh);

	DepthConverter sim_depth(nh);

#endif





#endif



    // ros init end //





#ifndef SIMULATION

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////// initialization  ////////////////////////////////////////

    /*img resolution setting*/

    int Width = 640;  //640

    int Height = 480; //480 (defult)



    //depth camera resolution is 1280*720



    /*camera initialize setting*/



    rs2::context ctx;

    auto list = ctx.query_devices();

    if (list.size() == 0)

        throw std::runtime_error("vision: Device not found");



    rs2::colorizer color_map;

    rs2::pipeline pipe;

    rs2::config cfg;



    cfg.enable_stream(RS2_STREAM_COLOR, Width, Height, RS2_FORMAT_BGR8, 60);

    cfg.enable_stream(RS2_STREAM_DEPTH, Width, Height, RS2_FORMAT_Z16, 60);

    rs2::pipeline_profile profile = pipe.start(cfg);



    /*align setting */  // it need to use cuda align <<<<<<<<<<<<<<<<<<<<<<<<<

    float depth_scale = get_depth_scale(profile.get_device());

    rs2_stream align_to = find_stream_to_align(profile.get_streams());



//#ifndef CUDA_YOLO

    rs2::align align(align_to);  //normal alige

    /*

#else

    librealsense::align_cuda  align(align_to);  //cuda align and it need to build librealsense with cuda

#endif

*/



#ifdef DEBUG

    std::cout << "vision: Camera initialized" << std::endl;

#endif

/////////////////////////////////////////////////////////////////////////////////////////



#else  //for Simulation

    //SIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATION

		/*img resolution setting*/

	int Width = 640;  //640

	int Height = 480; //480 (defult)







//SIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATION

#endif  // intitialize setting





///////////////////////////////  deeplearning setting ///////////////////////////////



#ifdef CUDA_YOLO  // using darknet for yolo

    std::string  names_file = "/home/nvidia/CLionProjects/vision_dev/yolo/yolo3.names";    // class file path (name of objects)

    std::string  cfg_file = "/home/nvidia/CLionProjects/vision_dev/yolo/yolov3.cfg";  //cfg File and weights File path setting

    std::string  weights_file = "/home/nvidia/CLionProjects/vision_dev/yolo/yolov3-tiny.backup";



    std::vector<bbox_t> detect_Data;



    darknet::Detector detector(cfg_file, weights_file);  // initialize darkent detector  code in CUDA_detection.hp

    detector.nms = nmsThreshold;  // configure overraped objects

    auto obj_names = objects_names_from_file(names_file);  //load img file name

#ifdef DEBUG

    std::cout << "vision: YOLO_with_CUDA initialized" << std::endl;

#endif



#else  // only cpu used in yolo





    Mat blob;

    double scale = 1 / 255; // 1/ number of chennel (chennel means rgb 1~255)





    /* using deeplearning data*/

    string classesFile = "yolo/yolo3.names"; // class file path (name of objects)

    ifstream ifs(classesFile.c_str());

    string line;

    while (getline(ifs, line)) classes.push_back(line);

    String modelConfiguration = "yolo/yolov3.cfg";  //cfg File and weights File path setting

    String modelWeights = "yolo/yolov3.weights";

    /*Loading deeplearing network*/

    Net net = readNetFromDarknet(modelConfiguration, modelWeights);

    net.setPreferableBackend(DNN_BACKEND_OPENCV);

    net.setPreferableTarget(DNN_TARGET_CPU);



    std::cout << "vision: loaded Deep Learning data successfully" << endl;  //only for CPU USE

#endif





/////////////////////////////////////////////////////////////////////////////////////////





#ifndef SIMULATION

///////////////////////////////  KCFTraking seting ///////////////////////////////

    /*KCFTraker initialize*/

    Ptr<Tracker> tracker;

    tracker = createTrackerByName("KCF", tracker);

/////////////////////////////////////////////////////////////////////////////////////////

#endif



///////////////////////////////  var initialization ///////////////////////////////

    /*img show (visualization)*/  //<<<<<<<<<<<< not necessary

    const auto window_name = "Display Image";

    namedWindow(window_name, WINDOW_AUTOSIZE);

    /*addtional value*/

    //true => traking

    int index;

    VisionDataset dataset;

    dataset.Detection = true;

    Mat detectimg;

    Mat afterimg;

    bool First_Tracking = false;  // setup when true vlaue



#ifndef SIMULATION

    /*multi Traker platform initialze*/

    Ptr<MultiTracker> multiTracker = cv::MultiTracker::create();

#endif



    int number_frame = 0;

    dataset.how_old = 0;

    dataset.trakcer_data[0] = 4;    //for using trakcer we need to configure aliy or enemy

    dataset.trakcer_data[1] = 4;

    dataset.trakcer_data[2] = 4;



    sendDataset send_;

    int target = 0;

    Sendinfo gimbal;

    yamiinfo_initialize(gimbal);



#ifdef DEBUG

    std::cout << "vision: KCF tracking ready." << endl;

#endif

/////////////////////////////////////////////////////////////////////////////////////////



    /*processing*/



    // ros //











#ifdef ROS

    while (waitKey(1) < 0 && cvGetWindowHandle(window_name) && ros::ok())

        // while (waitKey(1) < 0 && cvGetWindowHandle(window_name))

#else



        while (waitKey(1) < 0 && cvGetWindowHandle(window_name))

#endif

    {



#ifndef SIMULATION  //for realworld

        auto start = std::chrono::steady_clock::now();





///////////////////////////////  start camera ///////////////////////////////

        /*delete all info when start detecting*/

        if (dataset.Detection) {

            //VisionDataset_initialize(dataset);

            VisionDataset_initialize(dataset);

            dataset.how_old = 0; //delete old value (it used for traking algo)

            First_Tracking = true; //based on this algo when detecting condition, value must be true.

        }





        /*get data from realsense camera*/

        rs2::frameset data = pipe.wait_for_frames();





        /*align (matching RGB angle and Depth angle)*/

//		if (profile_changed(pipe.get_active_profile().get_streams(), profile.get_streams()))

//		{

//			//If the profile was changed, update the align object, and also get the new device's depth scale

//			profile = pipe.get_active_profile();

//			align_to = find_stream_to_align(profile.get_streams());

//			align = rs2::align(align_to);

//			depth_scale = get_depth_scale(profile.get_device());

//		}

//		auto processed = align.process(data);   // align function



        /*data frame processing*/    //aligen funtion use

        //rs2::video_frame color_frame = data.first_or_default(align_to);

        rs2::video_frame color_frame = data.get_color_frame();

        rs2::depth_frame depth_frame = data.get_depth_frame();







        /*if there are no frame , try again*/

        if (!depth_frame || !color_frame) {

            continue;  // frame check based on buffer

        }

        /*

        static int last_frame_number = 0;

        if (color_frame.get_frame_number() == last_frame_number) continue;

        last_frame_number = color_frame.get_frame_number();    //only use Color frame

        */

/////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////  update_frame ///////////////////////////////











        /*change realsense img to opencv Img Mat*/

        if (dataset.Detection) {

            dataset.detectimg = frame_to_mat(color_frame);  //rs img to opencv img

#ifdef DISPLAY

            dataset.display = frame_to_mat(color_frame);    //not necessary %%%%%%%%%%%%%%%%%%%%%%%%%

#endif

            //dataset.detectimg = &detectimg; // assign dataset

        }

        else {



            dataset.afterimg = frame_to_mat(color_frame);

#ifdef DISPLAY

            dataset.display = frame_to_mat(color_frame); //not necessary %%%%%%%%%%%%%%%%%%%%%%%%%

#endif

            //dataset.afterimg = &afterimg;

        }

        // cv::Mat depth_mat = depth_frame_to_meters(pipe, depth_frame);  //based on meter but useless work.



/////////////////////////////////////////////////////////////////////////////////////////





#else  //for simulation

        //SIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATION



			if (dataset.Detection) {

				dataset.detectimg = sim_img.GetImage();  //wait until message arrives and when arrives, get image

#ifdef DISPLAY

				dataset.display = dataset.detectimg;  //wait until message arrives and when arrives, get image

#endif

			//dataset.detectimg = &detectimg; // assign dataset

		}

			else {



				dataset.afterimg = sim_img.GetImage();  //wait until message arrives and when arrives, get image

#ifdef DISPLAY

				dataset.display = dataset.afterimg;  //wait until message arrives and when arrives, get image

#endif

			//dataset.afterimg = &afterimg;

			}





//SIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATIONSIMULATION  //for SIM  //for simulation

#endif



        if (dataset.Detection == true) {



/////////////////////////////// detecting ///////////////////////////////









#ifdef CUDA_YOLO  //darknet main useage







#ifdef DEBUG

            auto start = std::chrono::steady_clock::now();

#endif

            detect_Data =  detector.detect(dataset.detectimg, 0.2 , false);



#ifdef DEBUG

            auto end = std::chrono::steady_clock::now();

			std::chrono::duration<double> spent = end - start;



			std::cout << "vision:  trying detection" <<" Time: " << spent.count() << " sec \n";

#endif



#ifdef DISPLAY

            //if visualize wanted

            draw_boxes(dataset.display , detect_Data , obj_names);

#endif

            CUDA_Detect_VisionDataet( detect_Data , dataset );

            if ((dataset.Center_X[1] > 0) || (dataset.Center_X[2] > 0)) {

#ifdef DEBUG

                std::cout<<"enemy is founed "<<std::endl;

#endif

                //if there are enemy data

                VisionDataset_KCFCORMaker(dataset);

#ifndef SIMULATION

                armour_assign(detect_Data, dataset);   //in simulation condition, there are no armour data.

                configure_number_robot(dataset);

                VisionDataset_KCFCORMaker(dataset); // re Cor Maker

#endif



            }

            else {

#ifdef DISPLAY
				//cv::cvtColor(dataset.display, dataset.display, BGR2RGB);  //it is for BGR to RGB
                imshow(window_name, dataset.display); // <<<<<<<<<<<<<<<<<< imshow fucntion not necessary %%%%%%%%%%%%%%%%%%%%%%%%

                //no data will be display

#endif



                continue; //if no enemy data then detect again

            }







#else  // only cpu useage and this code use detection.hpp

            /*Deep Learning internal function*/

			blobFromImage((dataset.detectimg), blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);  //making 4D blob cvsize(inpWidth ,inpHeight) function format

			net.setInput(blob);

			vector<Mat> outs;

			net.forward(outs, getOutputsNames(net));  //make output

			/* post process deep Learninged img */

			//postprocess(dataset, outs , detectimg);

			postprocess(outs, dataset);



			std::cout << dataset.Detection << " vision: trying detection" << endl;



			/*

			// write time on img . (it can damage to img)

			vector<double> layersTimes;

			double freq = getTickFrequency() / 1000;

			double t = net.getPerfProfile(layersTimes) / freq;

			string label = format("Inference time for a frame : %.2f ms", t);

			putText(*dataset.detectimg, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));

			*/

#endif





            if (VisionDataset_checker(dataset.number_of_detection))  // if there are no object then strat detecting mode and try again.

            {

#ifdef DISPLAY
				//cv::cvtColor(dataset.display, dataset.display, BGR2RGB);  //it is for BGR to RGB
                imshow(window_name, dataset.display); // <<<<<<<<<<<<<<<<<< imshow fucntion not necessary %%%%%%%%%%%%%%%%%%%%%%%%

                // std::cout << "vision: robot detection failed" << endl;

#endif

                dataset.Detection = true; continue;



#ifdef DEBUG

                std::cout << "vision: robot detection failed" << endl;

#endif

            }

            else {



#ifdef TRACKER



                dataset.Detection = false;  // use with Trakcer

#else

                dataset.Detection = true;  // only detecting



#endif





#ifdef DISPLAY
				//cv::cvtColor(dataset.display, dataset.display, BGR2RGB);  //it is for BGR to RGB
                imshow(window_name, dataset.display); // <<<<<<<<<<<<<<<<<< imshow fucntion not necessary %%%%%%%%%%%%%%%%%%%%%%%%

#endif



#ifndef SIMULATION



                VisionDataset_getDepth(dataset, depth_frame); // get distance date form camera

#else



                for (index = 0; index < 3; index++) {

					if (dataset.Center_X[index] > 0 && dataset.Center_Y[index]) {

						dataset.distance = sim_depth.getDepthdata(dataset.Center_X[index], dataset.Center_Y[index]);

					}

				}

#endif

/////////////////////////////////////////////////////////////////////////////////////////



            }



        }

        else {

#ifndef SIMULATION

/////////////////////////////// region Tracking_code ///////////////////////////////

#ifdef DEBUG

            std::cout << dataset.Detection << " vision: attempting Tracking " << dataset.number_of_detection << endl;

#endif

            VisionDataset_KCFCORMaker(dataset);



            if (First_Tracking) {

                // before traking we must be initialize tracker.

                // at this moment there are some object on img.

                if (!Set_MultiTracker(multiTracker, "KCF", dataset, tracker)) {



#ifdef DEBUG

                    std::cout << "vision: MultiTracker setting failed" << endl;

#endif

                    dataset.Detection = true; continue;

                }

                First_Tracking = false; //set the traker only one time



            }





            KCFTraker_Run(dataset, multiTracker);  //run KCF trakcer





            if (VisionDataset_checker(dataset.number_of_detection))  // if there are no tracking object, detect again

            {

#ifdef DEBUG

                std::cout << "vision: tracking failed" << endl;

#endif

                dataset.Detection = true; continue;



            }

            else {



                dataset.Detection = false; // we need some function which change traking mode to detecting mode

#ifndef SIMULATION

                VisionDataset_getDepth(dataset, depth_frame); //get depth data

#endif

                VisionDataset_continueTraking(dataset); //this function presurlbe old img.





////////////////////////////////////////////////////////////////////////////

#endif

            }



        }



        /*

        rs2::frame depth_c = data.get_depth_frame().apply_filter(color_map);

        // Query frame size (width and height)

        const int w = depth_c.as<rs2::video_frame>().get_width();

        const int h = depth_c.as<rs2::video_frame>().get_height();

        // Create OpenCV matrix of size (w,h) from the colorized depth data

        Mat image(Size(w, h), CV_8UC3, (void*)depth_c.get_data(), Mat::AUTO_STEP);   //dapth to coloar img.

        */

        // change depth img to color img but it is not necessary



///////////////////////////////data_out ///////////////////////////////





        // std::cout << dataset.Detection << "vision: found data" << " number of detection: " << dataset.number_of_detection << endl;

#ifdef DEBUG

        std::cout << "number_of_detection" << dataset.number_of_detection << endl;

		for (index = 0; index < 3; index++) {

			std::cout << index  << "`s center coordinate:" << dataset.Center_X[index] << "," << dataset.Center_Y[index] << ", distance:" << dataset.distance[index] << endl;

		}

#endif



////////////////////////////////////////////////////////////////////////////





///////////////////////////////  escape_Traking///////////////////////////////

#ifdef TRACKER

        if (dataset.number_of_detection == 0) {

            dataset.Detection = true;

#ifdef DEBUG

            std::cout << "dataset.number_of_detection is zero , detecting mode on" << endl;

#endif

        }



        if (dataset.Detection == false && First_Tracking == false) {

            //if it is not first tracking (control img`s age) (this function can answer: How old this img?)

            VisionDataset_avoid_fail_KCF(dataset);

            VisionDataset_KCF_old_control(dataset);

        }



        if (dataset.Detection == false && First_Tracking == true) {

            // after firest tracking change First Tracking flage to false

            First_Tracking = false;

        }

        number_frame++;



        if ((number_frame % 60) == 0) {

            dataset.Detection = true;

#ifdef DEBUG

            std::cout << "vision: we trakck more than 60 frames so changing to detection" << endl;

#endif

        }

#endif

////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////data_send/////////////////////////////////////////////

        sendData_Maker(dataset, send_);  //send_data maker

        select_target_robot_vision(dataset , target); //selsect target



#ifdef DEBUG

        std::cout<<"target:" << target << std::endl;

#endif





#ifndef SIMULATION



        armourdata_selector(dataset, gimbal, depth_frame, target); // now send gimbal to ros



#endif



//////////////////////////////////////////////////////////////////////////////////////////////



#ifdef DISPLAY
		//cv::cvtColor(dataset.display, dataset.display, BGR2RGB);  //it is for BGR to RGB
        imshow(window_name, dataset.display);  //not necessary %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

#ifdef ROS



        pubEnemyInfo(send_, enemy_info_pub);

#ifdef SIMULATION

        gimbal.Pixel_X = send_.sendinfo[1].Pixel_X;

		gimbal.Pixel_Y = send_.sendinfo[2].Pixel_Y;



		if (send_.sendinfo[1].Pixel_X > 0) {

			gimbal.infochecker = true;

		}

		else {

			gimbal.infochecker = false;

		}

		//During simulation condition, robot 1 main target

#endif



        rosPixelControl(send_.number_of_detection, gimbal, cmd_gimbal_angle_pub);



        ros::spinOnce();

        //rate.sleep();



        yamiinfo_initialize(gimbal);



        sendDataset_initialize(send_);



        // ros pixel control end //

#endif



#ifdef DEBUG

        auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> spent = end - start;



		std::cout << "vision:  trying detection" <<" Time: " << spent.count() << " sec \n";

#endif

    }





}



/////////////////////////////// region error ///////////////////////////////





catch (const rs2::error & e)

{

    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;

    return EXIT_FAILURE;

}

catch (const std::exception& e)

{

    std::cerr << e.what() << std::endl;

    return EXIT_FAILURE;

}



////////////////////////////////////////////////////////////////////////////