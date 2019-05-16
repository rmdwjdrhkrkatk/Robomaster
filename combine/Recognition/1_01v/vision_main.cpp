//메인 코드
#include "allign.hpp"

using namespace cv;     //opencv 관련 함수 사용
using namespace dnn;    //dnn함수 사용
using namespace std;    //cpp기본 함수 라이브러리 사용

int main(int argc, char * argv[]) try
{
	/*이미지 해상도 셋팅*/
	int Width = 640;
	int Height = 480;

	/*카메라 초기 셋팅*/
	rs2::context ctx;
	auto list = ctx.query_devices();
	if (list.size() == 0)
	throw std::runtime_error("장치가 발견되지 않았습니다.");
	rs2::colorizer color_map;
	rs2::pipeline pipe;
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, Width, Height, RS2_FORMAT_BGR8, 30);
	cfg.enable_stream(RS2_STREAM_DEPTH, Width, Height, RS2_FORMAT_Z16, 30);
	rs2::pipeline_profile profile = pipe.start(cfg);

	/*align셋팅*/
	float depth_scale = get_depth_scale(profile.get_device());
	rs2_stream align_to = find_stream_to_align(profile.get_streams());
	rs2::align align(align_to);

	/*딥러닝된 데이타 사용*/
	Mat blob;
	double scale = 1 / 255; // 1나누기 chennel수 여기서 채널은 rgb내부 1~255를 의미
	string classesFile = "yolofile/yolo3.names"; //클래스 이름 여기에 경로 넣으면됨
	ifstream ifs(classesFile.c_str());
	string line;
	while (getline(ifs, line)) classes.push_back(line);
	String modelConfiguration = "yolofile/yolov3.cfg";  //cfg파일과 weights파일 경로 설정
	String modelWeights = "yolofile/yolov3.weights";
	/*딥러닝 네트워크 로딩*/
	Net net = readNetFromDarknet(modelConfiguration, modelWeights);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	/*띄울 이미지창 설정*/
	const auto window_name = "Display Image";
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/*추가 변수*/
	int X, Y;
	double distance = 0;

	/*실제 실행코드*/
	while (waitKey(1) < 0 && cvGetWindowHandle(window_name))
	{
		X = 0;
		Y = 0;
		/*카메라에서 데이터 획득*/
		rs2::frameset data = pipe.wait_for_frames();

		/*공간상 정렬시키기*/
		if (profile_changed(pipe.get_active_profile().get_streams(), profile.get_streams()))
		{
			//If the profile was changed, update the align object, and also get the new device's depth scale
			profile = pipe.get_active_profile();
			align_to = find_stream_to_align(profile.get_streams());
			align = rs2::align(align_to);
			depth_scale = get_depth_scale(profile.get_device());
		}
		auto processed = align.process(data);   //실제 정렬함수

		/*데이타 프레임별 쪼개기*/
		rs2::video_frame color_frame = data.get_color_frame();
		rs2::depth_frame depth_frame = data.get_depth_frame();


		/*프래임을 못받았을 때 다시 시도*/ //두가지 방식이 있으며, 효율성 확인
		if (!depth_frame || !color_frame)    //버퍼 기반 프레임 확인
		{
			continue;
		}
		/*
		static int last_frame_number = 0;
		if (color_frame.get_frame_number() == last_frame_number) continue;
		last_frame_number = color_frame.get_frame_number();    //컬러 프레임으로만 직전 코드확인하기
		*/
		
		/*realsense 정보를 opencv연산가능한 이미지 행렬로 변환*/
		cv::Mat color_mat = frame_to_mat(color_frame);  //RGB로 변환
		cv::Mat depth_mat = depth_frame_to_meters(pipe, depth_frame);  //meter법으로 변환 행렬에 입력
		
		/*딥러닝 내부 함수*/
		blobFromImage(color_mat, blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);  //4D blob 생성
		net.setInput(blob);  
		vector<Mat> outs; 
		net.forward(outs, getOutputsNames(net));  //결과 생성

		/*딥러닝된 이미지 전처리과정 및 시간정보 입력*/
		postprocess(color_mat, outs,&X,&Y);  
		vector<double> layersTimes;
		double freq = getTickFrequency() / 1000;
		double t = net.getPerfProfile(layersTimes) / freq;
		string label = format("Inference time for a frame : %.2f ms", t);
		putText(color_mat, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));

		/*거리값 축출*/
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
		Mat image(Size(w, h), CV_8UC3, (void*)depth_c.get_data(), Mat::AUTO_STEP);   //dapth이미지를 컬러로 변경시켜줌.
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