//main code
#include "allhpp.hpp"

using namespace cv;     //opencv function 
using namespace dnn;    //dnn function
using namespace std;    //cpp basic function

//void postprocess(VisionDataset dataset, const vector<Mat> &outs  , Mat& detectimg);



int main(int argc, char * argv[]) try
{

#pragma region initialization 
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
	rs2::align align(align_to);

	std::cout << "vision: Camera initialized" << endl;

#pragma endregion 

#pragma region deeplearning setting
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

	std::cout << "vision: loaded Deep Learning data successfully" << endl;


#pragma endregion

#pragma region KCFTraking seting
	/*KCFTraker initialize*/
	Ptr<Tracker> tracker;
	tracker = createTrackerByName("KCF", tracker);
#pragma endregion 

#pragma region var initialization
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
	/*multi Traker platform initialze*/
	Ptr<MultiTracker> multiTracker = cv::MultiTracker::create();

	int number_frame = 0;
	dataset.how_old = 0;

	sendDataset send_;


	std::cout << "vision: KCF tracking ready." << endl;

#pragma endregion 

	/*processing*/
	while (waitKey(1) < 0 && cvGetWindowHandle(window_name))
	{

#pragma region start camera
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
		if (profile_changed(pipe.get_active_profile().get_streams(), profile.get_streams()))
		{
			//If the profile was changed, update the align object, and also get the new device's depth scale
			profile = pipe.get_active_profile();
			align_to = find_stream_to_align(profile.get_streams());
			align = rs2::align(align_to);
			depth_scale = get_depth_scale(profile.get_device());
		}
		auto processed = align.process(data);   // align function

		/*data frame processing*/
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
#pragma endregion 


#pragma region update_frame



		/*change realsense img to opencv Img Mat*/
		if (dataset.Detection) {
			dataset.detectimg = frame_to_mat(color_frame);  //rs img to opencv img
			dataset.display = frame_to_mat(color_frame);    //not necessary %%%%%%%%%%%%%%%%%%%%%%%%%

			//dataset.detectimg = &detectimg; // assign dataset
		}
		else {

			dataset.afterimg = frame_to_mat(color_frame);
			dataset.display = frame_to_mat(color_frame); //not necessary %%%%%%%%%%%%%%%%%%%%%%%%%

			//dataset.afterimg = &afterimg;
		}
		// cv::Mat depth_mat = depth_frame_to_meters(pipe, depth_frame);  //based on meter but useless work. 

#pragma endregion 


		if (dataset.Detection == true) {

#pragma region detecting


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



			if (VisionDataset_checker(dataset.number_of_detection))  // if there are no object then strat detecting mode and try again. 
			{
				imshow(window_name, dataset.display); // <<<<<<<<<<<<<<<<<< imshow fucntion not necessary %%%%%%%%%%%%%%%%%%%%%%%%
				// std::cout << "vision: robot detection failed" << endl;

				dataset.Detection = true; continue;
				std::cout << "vision: robot detection failed" << endl;
			}
			else {
				dataset.Detection = false;
				imshow(window_name, dataset.display); // <<<<<<<<<<<<<<<<<< imshow fucntion not necessary %%%%%%%%%%%%%%%%%%%%%%%%
				VisionDataset_getDepth(dataset, depth_frame); // get distance date form camera



#pragma endregion 

			}

		}
		else {

#pragma region Tracking_code

			std::cout << dataset.Detection << " vision: attempting Tracking " << dataset.number_of_detection << endl;

			if (First_Tracking) {
				// before traking we must be initialize tracker. 
				// at this moment there are some object on img.
				if (Set_MultiTracker(multiTracker, "KCF", dataset, tracker) == false) {
					std::cout << "vision: MultiTracker setting failed" << endl;
					dataset.Detection = true; continue;
				}
				First_Tracking = false; //set the traker only one time 

			}


			KCFTraker_Run(dataset, multiTracker);  //run KCF trakcer


			if (VisionDataset_checker(dataset.number_of_detection))  // if there are no tracking object, detect again
			{
				std::cout << "vision: tracking failed" << endl;
				dataset.Detection = true; continue;

			}
			else {

				dataset.Detection = false; // we need some function which change traking mode to detecting mode 

				VisionDataset_getDepth(dataset, depth_frame); //get depth data
				VisionDataset_continueTraking(dataset); //this function presurlbe old img. 


#pragma endregion 

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

#pragma region data_out


		std::cout << dataset.Detection << "vision: found data" << " number of detection: " << dataset.number_of_detection << endl;

		for (index = 0; index < dataset.number_of_detection; index++) {
			std::cout << index + 1 << "`s center coordinate:" << dataset.Center_X[index] << "," << dataset.Center_Y[index] << ", distance:" << dataset.distance[index] << endl;
		}

#pragma endregion

#pragma region escape_Traking

		if (dataset.number_of_detection == 0) {
			dataset.Detection = true;
			std::cout << "dataset.number_of_detection == 0 , detecting mode one" << endl;
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
			std::cout << "vision: we trakck more than 60 frames so changing to detection" << endl;
		}

#pragma endregion 


//////////data_send//////////////
		sendData_Maker(dataset, send_);  //send_data maker




////////////////////////////////


		imshow(window_name, dataset.display);  //not necessary %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	}


}

#pragma region error


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

#pragma endregion 

