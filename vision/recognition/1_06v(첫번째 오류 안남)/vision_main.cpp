//���� �ڵ�
#include "KCFtraker.hpp"

using namespace cv;     //opencv ���� �Լ� ���
using namespace dnn;    //dnn�Լ� ���
using namespace std;    //cpp�⺻ �Լ� ���̺귯�� ���

//void postprocess(VisionDataset dataset, const vector<Mat> &outs  , Mat& detectimg);



int main(int argc, char * argv[]) try
{
	
	#pragma region initialization 
	/*�̹��� �ػ� ����*/
	int Width = 640;
	int Height = 480;

	/*ī�޶� �ʱ� ����*/
	
	rs2::context ctx;
	auto list = ctx.query_devices();
	if (list.size() == 0)
	throw std::runtime_error("��ġ�� �߰ߵ��� �ʾҽ��ϴ�.");

	rs2::colorizer color_map;
	rs2::pipeline pipe;
	rs2::config cfg;
	
	cfg.enable_stream(RS2_STREAM_COLOR, Width, Height, RS2_FORMAT_BGR8, 30);
	cfg.enable_stream(RS2_STREAM_DEPTH, Width, Height, RS2_FORMAT_Z16, 30);
	rs2::pipeline_profile profile = pipe.start(cfg);
	
	/*align����*/
	float depth_scale = get_depth_scale(profile.get_device());
	rs2_stream align_to = find_stream_to_align(profile.get_streams());
	rs2::align align(align_to);
	#pragma endregion ī�޶� �ʱ� ����
	
	std::cout << "ī�޶� �ʱ�ȭ �Ϸ�" << endl;

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
	
	std::cout << "������ ������ �ҷ����� �Ϸ�" << endl;
	

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
	bool Detecting = true;   //true�϶� Ʈ��ŷ
	int index;
	VisionDataset dataset;
	Mat detectimg;
	Mat afterimg;
	bool First_Tracking = false;  //true�϶��� �¾��� �ϵ��� �Ѵ�. 
	/*��ƼƮ��ŷ �÷��� ����*/
	Ptr<MultiTracker> multiTracker = cv::MultiTracker::create();

	std::cout << "KCFƮ��ŷ �غ� �Ϸ�." << endl;

	#pragma endregion ���� �ʱ�ȭ

	/*���� �����ڵ�*/
	while (waitKey(1) < 0 && cvGetWindowHandle(window_name))
	{
		
		#pragma region start camera
		/*���ص带 �Ҷ��� ������ ������ ��� �����Ѵ�.*/
		if (Detecting) {
			//VisionDataset_initialize(dataset);
			VisionDataset_initialize(dataset);
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
		if (!depth_frame || !color_frame)  continue;  //���� ��� ������ Ȯ��

		/*
		static int last_frame_number = 0;
		if (color_frame.get_frame_number() == last_frame_number) continue;
		last_frame_number = color_frame.get_frame_number();    //�÷� ���������θ� ���� �ڵ�Ȯ���ϱ�
		*/
		#pragma endregion ī�޶󿡼� ����Ÿ �޾ƿ���

	
		#pragma region update_frame



		/*realsense ������ opencv���갡���� �̹��� ��ķ� ��ȯ*/
		if (Detecting) {
			dataset.detectimg = frame_to_mat(color_frame);  //rs�̹����� cv�̹����� ��ȯ
			
			//dataset.detectimg = &detectimg; //dataset�� �Ҵ��ϱ�. 
		}
		else {

			afterimg = frame_to_mat(color_frame);
			dataset.afterimg = afterimg;
			//dataset.afterimg = &afterimg;
		}
		// cv::Mat depth_mat = depth_frame_to_meters(pipe, depth_frame);  //meter������ ��ȯ ��Ŀ� �Է� �㳪 �����δ� ������� �ʴ´�. 
		
		#pragma endregion RS2�Լ��� opencv�Լ��� ��ȯ


		

		if (Detecting) {

			#pragma region detecting
			

				/*������ ���� �Լ�*/
				blobFromImage((dataset.detectimg), blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);  //4D blob ���� cvsize(inpWidth ,inpHeight) �Լ� �������� ����
				net.setInput(blob);
				vector<Mat> outs;
				net.forward(outs, getOutputsNames(net));  //��� ����
				/*�����׵� �̹��� ��ó������ �� �ð����� �Է�*/
				//postprocess(dataset, outs , detectimg);     //���⼭ with hight ���� �����ؾ��Ѵ�. 
				postprocess( outs , dataset);

				std::cout << Detecting << " detecting �õ��� // �߰ߵ� �κ��� ��: " << dataset.number_of_detection << endl;

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
					imshow(window_name, dataset.detectimg);
					Detecting = true; continue;
				}
				else {
					Detecting = false;
					imshow(window_name, dataset.detectimg);
					VisionDataset_getDepth(dataset, depth_frame); //�Ÿ� ����Ÿ ��� 
					First_Tracking = true;


#pragma endregion ��θ� �̿��Ͽ� ã�� �ڵ�
				
			}
				
				std::cout << Detecting << "  " << dataset.number_of_detection << endl;
			
		}
		else {

			#pragma region Tracking_code

			if (First_Tracking) {

				//���⿡ �Դٴ� ���� ���� ���� �νĵǾ��ٴ� ���̴�.
				Set_MultiTracker(multiTracker, "KCF", dataset, tracker);

			}


			KCFTraker_Run(dataset, multiTracker);  //KCF�ڵ� ������ �Լ�

			//KCFƮ��Ŀ ���ϴ� �ڵ� �պ����Ѵ�. 

			if (VisionDataset_checker(dataset.number_of_detection))  // tracking�� ���������� detection�� �Ѱ� ó����ġ�� ����������. 
			{
				Detecting = true; continue;
				std::cout << Detecting << " Ʈ��ŷ ���� ��õ��� " << dataset.number_of_detection << endl;
			}
			else {

				Detecting = false; // �߰��� ���Ƿ� detect�� �Ѵ� �Լ��� �ʿ��ϴ�. 

				VisionDataset_getDepth(dataset, depth_frame); //�Ÿ� ����Ÿ ��� 
				VisionDataset_continueTraking(dataset); //���Լ��� �ֽ� �������� ������� ��� ������ �����ϴ� �Լ��̴�. 


			#pragma endregion KCFƮ��ŷ�� �ϴ� �ڵ�
				
			}

			std::cout << Detecting << " Ʈ��ŷ �õ��� " << dataset.number_of_detection << endl;
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
		std::cout << Detecting <<"�߰ߵ� ����Ÿ" << " ã�� ����: " << dataset.number_of_detection  <<endl;
		for (index = 0; index < dataset.number_of_detection; index++) {
			std::cout << "1������ ������ǥ:" << dataset.Center_X[index] << "," << dataset.Center_Y[index] << endl;
		}
		imshow(window_name, dataset.detectimg);
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

