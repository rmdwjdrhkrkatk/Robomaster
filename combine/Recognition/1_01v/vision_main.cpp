//���� �ڵ�
#include "allign.hpp"

using namespace cv;     //opencv ���� �Լ� ���
using namespace dnn;    //dnn�Լ� ���
using namespace std;    //cpp�⺻ �Լ� ���̺귯�� ���

int main(int argc, char * argv[]) try
{
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

	/*�����׵� ����Ÿ ���*/
	Mat blob;
	double scale = 1 / 255; // 1������ chennel�� ���⼭ ä���� rgb���� 1~255�� �ǹ�
	string classesFile = "yolofile/yolo3.names"; //Ŭ���� �̸� ���⿡ ��� �������
	ifstream ifs(classesFile.c_str());
	string line;
	while (getline(ifs, line)) classes.push_back(line);
	String modelConfiguration = "yolofile/yolov3.cfg";  //cfg���ϰ� weights���� ��� ����
	String modelWeights = "yolofile/yolov3.weights";
	/*������ ��Ʈ��ũ �ε�*/
	Net net = readNetFromDarknet(modelConfiguration, modelWeights);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	/*��� �̹���â ����*/
	const auto window_name = "Display Image";
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/*�߰� ����*/
	int X, Y;
	double distance = 0;

	/*���� �����ڵ�*/
	while (waitKey(1) < 0 && cvGetWindowHandle(window_name))
	{
		X = 0;
		Y = 0;
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
		if (!depth_frame || !color_frame)    //���� ��� ������ Ȯ��
		{
			continue;
		}
		/*
		static int last_frame_number = 0;
		if (color_frame.get_frame_number() == last_frame_number) continue;
		last_frame_number = color_frame.get_frame_number();    //�÷� ���������θ� ���� �ڵ�Ȯ���ϱ�
		*/
		
		/*realsense ������ opencv���갡���� �̹��� ��ķ� ��ȯ*/
		cv::Mat color_mat = frame_to_mat(color_frame);  //RGB�� ��ȯ
		cv::Mat depth_mat = depth_frame_to_meters(pipe, depth_frame);  //meter������ ��ȯ ��Ŀ� �Է�
		
		/*������ ���� �Լ�*/
		blobFromImage(color_mat, blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);  //4D blob ����
		net.setInput(blob);  
		vector<Mat> outs; 
		net.forward(outs, getOutputsNames(net));  //��� ����

		/*�����׵� �̹��� ��ó������ �� �ð����� �Է�*/
		postprocess(color_mat, outs,&X,&Y);  
		vector<double> layersTimes;
		double freq = getTickFrequency() / 1000;
		double t = net.getPerfProfile(layersTimes) / freq;
		string label = format("Inference time for a frame : %.2f ms", t);
		putText(color_mat, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));

		/*�Ÿ��� ����*/
		if (!X == 0 || !Y == 0) {
			distance = depth_frame.get_distance(X, Y);
			std::cerr << "distance info (mm) : "<< distance << std::endl;
		}

	
		/*
		rs2::frame depth_c = data.get_depth_frame().apply_filter(color_map);
		// Query frame size (width and height)
		const int w = depth_c.as<rs2::video_frame>().get_width();
		const int h = depth_c.as<rs2::video_frame>().get_height();
		// Create OpenCV matrix of size (w,h) from the colorized depth data
		Mat image(Size(w, h), CV_8UC3, (void*)depth_c.get_data(), Mat::AUTO_STEP);   //dapth�̹����� �÷��� ���������.
		*/

		imshow(window_name, color_mat);
	}




}
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