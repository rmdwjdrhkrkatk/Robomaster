//���� �ڵ�

#include "KCFtraker.hpp"
#include "SendData_Control.hpp"
#include <ros/ros.h>											///ROS
#include "icra_roboin_msgs/YoloDetectionInfo.h"					///ROS

using namespace cv;     //opencv ���� �Լ� ���
using namespace dnn;    //dnn�Լ� ���
using namespace std;    //cpp�⺻ �Լ� ���̺귯�� ���

//void postprocess(VisionDataset dataset, const vector<Mat> &outs  , Mat& detectimg);


int main(int argc, char** argv) try
{
	sendDataset send_;											
	
	#pragma region initialization 
	/*�̹��� �ػ� ����*/
	int Width = 640;  //640
	int Height = 480; //480 �⺻��  

	//�Ÿ�ȭ���� 1280*720 �̴�.

	/*ī�޶� �ʱ� ����*/
	
	rs2::context ctx;
	auto list = ctx.query_devices();
	if (list.size() == 0)
	throw std::runtime_error("vision: Device not found");


	////////////////ROS////////////////////////////
	//Init ros action server
	ros::init(argc,argv,"yolo_detection_node");																		
	ros::NodeHandle nh;																								
	ros::Publisher pub = nh.advertise<icra_roboin_msgs::YoloDetectionInfo>("enemy_info",1);
	ros::Rate rate(10);
	int publish_count=0;
	/////////////////////////////////////////////////

	rs2::colorizer color_map;
	rs2::pipeline pipe;
	rs2::config cfg;
	
	cfg.enable_stream(RS2_STREAM_COLOR, Width, Height, RS2_FORMAT_BGR8, 60);
	cfg.enable_stream(RS2_STREAM_DEPTH, Width, Height, RS2_FORMAT_Z16, 60);
	rs2::pipeline_profile profile = pipe.start(cfg);
	
	/*align����*/
	float depth_scale = get_depth_scale(profile.get_device());
	rs2_stream align_to = find_stream_to_align(profile.get_streams());
	rs2::align align(align_to);
	#pragma endregion ī�޶� �ʱ� ����
	
	std::cout << "vision: Camera initialized" << endl;

	#pragma region deeplearning seting
	Mat blob;
	double scale = 1 / 255; // 1������ chennel�� ���⼭ ä���� rgb���� 1~255�� �ǹ�
	/*�����׵� ����Ÿ ���*/
		
		
	string classesFile = "yolo/yolo3.names"; //Ŭ���� �̸� ���⿡ ��� �������
	ifstream ifs(classesFile.c_str());
	string line;
	while (getline(ifs, line)) classes.push_back(line);
	String modelConfiguration = "yolo/yolov3.cfg";  //cfg���ϰ� weights���� ��� ����
	String modelWeights = "yolo/yolov3.weights";
	/*������ ��Ʈ��ũ �ε�*/
	Net net = readNetFromDarknet(modelConfiguration, modelWeights);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);
	
	std::cout << "vision: loaded Deep Learning data successfully" << endl;
	

	#pragma endregion ������ ����

	#pragma region KCFTraking seting
	/*KCFTraking �ʱ�ȭ*/
	Ptr<Tracker> tracker;
	tracker = createTrackerByName("KCF", tracker);
	#pragma endregion KCFƮ��Ŀ ����

	#pragma region var initialization
	/*��� �̹���â ����*/
	const auto window_name = "Display Image";
	namedWindow(window_name, WINDOW_AUTOSIZE);
	/*�߰� ����*/
	   //true�϶� Ʈ��ŷ
	int index;
	VisionDataset dataset;
	dataset.Detection = true;
	Mat detectimg;
	Mat afterimg;
	bool First_Tracking = false;  //true�϶��� �¾��� �ϵ��� �Ѵ�. 
	/*��ƼƮ��ŷ �÷��� ����*/
	Ptr<MultiTracker> multiTracker = cv::MultiTracker::create();

	int number_frame = 0;
	dataset.how_old = 0;



	std::cout << "vision: KCF tracking ready." << endl;

	#pragma endregion ���� �ʱ�ȭ

	/*���� �����ڵ�*/
	while (waitKey(1) < 0 && cvGetWindowHandle(window_name) || ros::ok())
	{
		



		#pragma region start camera
		/*���ص带 �Ҷ��� ������ ������ ��� �����Ѵ�.*/
		if (dataset.Detection) {
			//VisionDataset_initialize(dataset);
			VisionDataset_initialize(dataset);
			dataset.how_old = 0; //������ old������ ������.(Ʈ��ŷ�� �Լ�)
			First_Tracking = true; //����Ʈ ���¿����� First Tracking���� �׻� ���̿����Ѵ�.
		}


		/*ī�޶󿡼� ������ ȹ��*/
		rs2::frameset data = pipe.wait_for_frames();

		/*������ ���Ľ�Ű��*/
		if (profile_changed(pipe.get_active_profile().get_streams(), profile.get_streams()))
		{
			//If the profile was changed, update the align object, and also get the new device's depth scale
			profile = pipe.get_active_profile();
			align_to = find_stream_to_align(profile.get_streams());
			align = rs2::align(align_to);
			depth_scale = get_depth_scale(profile.get_device());
		}
		auto processed = align.process(data);   //���� �����Լ�

		/*����Ÿ �����Ӻ� �ɰ���*/
		rs2::video_frame color_frame = data.get_color_frame();
		rs2::depth_frame depth_frame = data.get_depth_frame();


		/*�������� ���޾��� �� �ٽ� �õ�*/ //�ΰ��� ����� ������, ȿ���� Ȯ��
		if (!depth_frame || !color_frame) {
			continue;  //���� ��� ������ Ȯ��
		}
		/*
		static int last_frame_number = 0;
		if (color_frame.get_frame_number() == last_frame_number) continue;
		last_frame_number = color_frame.get_frame_number();    //�÷� ���������θ� ���� �ڵ�Ȯ���ϱ�
		*/
		#pragma endregion ī�޶󿡼� ����Ÿ �޾ƿ���

	
		#pragma region update_frame



		/*realsense ������ opencv���갡���� �̹��� ��ķ� ��ȯ*/
		if (dataset.Detection) {
			dataset.detectimg = frame_to_mat(color_frame);  //rs�̹����� cv�̹����� ��ȯ
			dataset.display = frame_to_mat(color_frame);
			
			//dataset.detectimg = &detectimg; //dataset�� �Ҵ��ϱ�. 
		}
		else {

			dataset.afterimg = frame_to_mat(color_frame);
			dataset.display = frame_to_mat(color_frame);
			
			//dataset.afterimg = &afterimg;
		}
		// cv::Mat depth_mat = depth_frame_to_meters(pipe, depth_frame);  //meter������ ��ȯ ��Ŀ� �Է� �㳪 �����δ� ������� �ʴ´�. 
		
		#pragma endregion RS2�Լ��� opencv�Լ��� ��ȯ


		

		if (dataset.Detection == true) {

			#pragma region detecting
			

				/*������ ���� �Լ�*/
				blobFromImage((dataset.detectimg), blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);  //4D blob ���� cvsize(inpWidth ,inpHeight) �Լ� �������� ����
				net.setInput(blob);
				vector<Mat> outs;
				net.forward(outs, getOutputsNames(net));  //��� ����
				/*�����׵� �̹��� ��ó������ �� �ð����� �Է�*/
				//postprocess(dataset, outs , detectimg);     //���⼭ with hight ���� �����ؾ��Ѵ�. 
				postprocess( outs , dataset);

				std::cout << dataset.Detection << "vision: trying detection // number of found robots: " << dataset.number_of_detection << endl;

				/*
				// �ð� ������ �����ͼ� ����ϴ��Լ�. (���� �̹����� �Ѽ��ϹǷ� �����Ѵ�)
				vector<double> layersTimes;
				double freq = getTickFrequency() / 1000;
				double t = net.getPerfProfile(layersTimes) / freq;
				string label = format("Inference time for a frame : %.2f ms", t);
				putText(*dataset.detectimg, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
				*/



				if (VisionDataset_checker(dataset.number_of_detection))  //detecting�� ���������� detecting�� �Ѱ� ó����ġ�� ����������. 
				{
					imshow(window_name, dataset.display);
					// std::cout << "�κ� ���ؼ� ����" << endl;

					dataset.Detection = true; continue;
					std::cout << "vision: robot detection failed" << endl;
				}
				else {
					dataset.Detection = false;
					imshow(window_name, dataset.display);
					VisionDataset_getDepth(dataset, depth_frame); //�Ÿ� ����Ÿ ��� 
					


#pragma endregion ��θ� �̿��Ͽ� ã�� �ڵ�
				
			}
				
				
			
		}
		else {

			#pragma region Tracking_code

			std::cout << dataset.Detection << " vision: attempting Tracking " << dataset.number_of_detection << endl;

			if (First_Tracking) {
				// traking�Ҷ� �ʱ�ȭ�� ���Ѿ��Ѵ�. 
				//���⿡ �Դٴ� ���� ���� ���� �νĵǾ��ٴ� ���̴�.
				if (Set_MultiTracker(multiTracker, "KCF", dataset, tracker) == false) {
					std::cout << "vision: MultiTracker setting failed" << endl;
					dataset.Detection = true; continue;
				}
				First_Tracking = false; //�ѹ��� ��Ƽ Ʈ��Ŀ �����Ѵ�. 

			}


			KCFTraker_Run(dataset, multiTracker);  //KCF�ڵ� ������ �Լ�

			//KCFƮ��Ŀ ���ϴ� �ڵ� �պ����Ѵ�. 

			if (VisionDataset_checker(dataset.number_of_detection))  // tracking�� ���������� detection�� �Ѱ� ó����ġ�� ����������. 
			{
				std::cout << "vision: tracking failed"<< "number of found robots:"<< dataset.number_of_detection << endl;
				dataset.Detection = true; continue;

			}
			else {

				dataset.Detection = false; // �߰��� ���Ƿ� detect�� �Ѵ� �Լ��� �ʿ��ϴ�. 

				VisionDataset_getDepth(dataset, depth_frame); //�Ÿ� ����Ÿ ��� 
				VisionDataset_continueTraking(dataset); //���Լ��� �ֽ� �������� ������� ��� ������ �����ϴ� �Լ��̴�. 


			#pragma endregion KCFƮ��ŷ�� �ϴ� �ڵ�
				
			}

			
		}
	
		/*
		rs2::frame depth_c = data.get_depth_frame().apply_filter(color_map);
		// Query frame size (width and height)
		const int w = depth_c.as<rs2::video_frame>().get_width();
		const int h = depth_c.as<rs2::video_frame>().get_height();
		// Create OpenCV matrix of size (w,h) from the colorized depth data
		Mat image(Size(w, h), CV_8UC3, (void*)depth_c.get_data(), Mat::AUTO_STEP);   //dapth�̹����� �÷��� ���������.
		*/  
		// �Ÿ� �����͸� �÷��� �ٲ��ִ� �Լ�, ���⼭�� �ʿ����

		#pragma region data_out


		std::cout << dataset.Detection <<"vision: found data" << " found number: " << dataset.number_of_detection  <<endl;

		for (index = 0; index < dataset.number_of_detection; index++) {
			std::cout << index + 1 <<"vision: central coordinate of dataset:" << dataset.Center_X[index] << "," << dataset.Center_Y[index] << ", �Ÿ�:" <<dataset.distance[index] << endl;
		}

		#pragma endregion ������ ���

		#pragma region escape_Traking

		if (dataset.number_of_detection == 0) {
			dataset.Detection = true;
			std::cout << "vision: changing to dataset.number_of_detection == 0" << endl;
		}

		if (dataset.Detection == false && First_Tracking == false ) {
			//ù��° Ʈ��ŷ�� �ƴҶ��� ���´�.
			VisionDataset_avoid_fail_KCF(dataset);
			VisionDataset_KCF_old_control(dataset);
		}
		
		if (dataset.Detection == false && First_Tracking == true) {
			// Ʈ��ŷ�� ó�� ������ false�� �ٲ۴�. �׷��� ������ ���� �ø��� �ֵ� ã�ƺ����Ѵ�.
			First_Tracking == false;
		}
		number_frame++;

		if ((number_frame % 60) == 0) {
			dataset.Detection = true;
			std::cout << "vision: filled 60 frames and changing to detection" << endl;
		}

		#pragma endregion Ʈ��ŷ Ż������

		imshow(window_name, dataset.display);


		/////////////////////////////////////////////////////
		/////////////////////////ROS/////////////////////////
		if(publish_count%3==0){
			

			sendData_Maker(dataset,send_);
			icra_roboin_msgs::YoloDetectionInfo ros_msg;
			ros_msg.stamp = ros::Time();
			ros_msg.number_of_detection= send_.number_of_detection;


			ros_msg.infochecker[1] = send_.data_1.infochecker;
			ros_msg.enemy[1] = send_.data_1.enemy;
			ros_msg.angle_hori[1] = send_.data_1.angle_hori;
			ros_msg.angle_verti[1] = send_.data_1.angle_verti;
			ros_msg.Pixel_X[1] = send_.data_1.Pixel_X;
			ros_msg.Pixel_Y[1] = send_.data_1.Pixel_Y;
			ros_msg.Pixel_width[1] = send_.data_1.Pixel_width;
			ros_msg.Pixel_height[1] = send_.data_1.Pixel_height;
			ros_msg.real_width[1] = send_.data_1.real_width;
			ros_msg.real_height[1] = send_.data_1.real_height;
			ros_msg.distance[1] = send_.data_1.distance;


			ros_msg.infochecker[2] = send_.data_2.infochecker;
			ros_msg.enemy[2] = send_.data_2.enemy;
			ros_msg.angle_hori[2] = send_.data_2.angle_hori;
			ros_msg.angle_verti[2] = send_.data_2.angle_verti;
			ros_msg.Pixel_X[2] = send_.data_2.Pixel_X;
			ros_msg.Pixel_Y[2] = send_.data_2.Pixel_Y;
			ros_msg.Pixel_width[2] = send_.data_2.Pixel_width;
			ros_msg.Pixel_height[2] = send_.data_2.Pixel_height;
			ros_msg.real_width[2] = send_.data_2.real_width;
			ros_msg.real_height[2] = send_.data_2.real_height;
			ros_msg.distance[2] = send_.data_2.distance;


			ros_msg.infochecker[3] = send_.data_3.infochecker;
			ros_msg.enemy[3] = send_.data_3.enemy;
			ros_msg.angle_hori[3] = send_.data_3.angle_hori;
			ros_msg.angle_verti[3] = send_.data_3.angle_verti;
			ros_msg.Pixel_X[3] = send_.data_3.Pixel_X;
			ros_msg.Pixel_Y[3] = send_.data_3.Pixel_Y;
			ros_msg.Pixel_width[3] = send_.data_3.Pixel_width;
			ros_msg.Pixel_height[3] = send_.data_3.Pixel_height;
			ros_msg.real_width[3] = send_.data_3.real_width;
			ros_msg.real_height[3] = send_.data_3.real_height;
			ros_msg.distance[3] = send_.data_3.distance;
			


			pub.publish(ros_msg);
		}
		publish_count++;
		/////////////////////////////////////////////////////
		/////////////////////////ROS/////////////////////////





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

#pragma endregion ī�޶� ȣ�� ���н� ����ڵ�

