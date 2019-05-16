//메인 코드
#include "KCFtraker.hpp"

using namespace cv;     //opencv 관련 함수 사용
using namespace dnn;    //dnn함수 사용
using namespace std;    //cpp기본 함수 라이브러리 사용

//void postprocess(VisionDataset dataset, const vector<Mat> &outs  , Mat& detectimg);



int main(int argc, char * argv[]) try
{
	
	#pragma region initialization 
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
	#pragma endregion 카메라 초기 셋팅
	
	std::cout << "카메라 초기화 완료" << endl;

	#pragma region deeplearning seting
	Mat blob;
	double scale = 1 / 255; // 1나누기 chennel수 여기서 채널은 rgb내부 1~255를 의미
	/*딥러닝된 데이타 사용*/
		
		
	string classesFile = "yolo/yolo3.names"; //클래스 이름 여기에 경로 넣으면됨
	ifstream ifs(classesFile.c_str());
	string line;
	while (getline(ifs, line)) classes.push_back(line);
	String modelConfiguration = "yolo/yolov3.cfg";  //cfg파일과 weights파일 경로 설정
	String modelWeights = "yolo/yolov3.weights";
	/*딥러닝 네트워크 로딩*/
	Net net = readNetFromDarknet(modelConfiguration, modelWeights);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);
	
	std::cout << "딥러닝 데이터 불러오기 완료" << endl;
	

	#pragma endregion 딥러닝 셋팅

	#pragma region KCFTraking seting
	/*KCFTraking 초기화*/
	Ptr<Tracker> tracker;
	tracker = createTrackerByName("KCF", tracker);
	#pragma endregion KCF트래커 셋팅

	#pragma region var initialization
	/*띄울 이미지창 설정*/
	const auto window_name = "Display Image";
	namedWindow(window_name, WINDOW_AUTOSIZE);
	/*추가 변수*/
	bool Detecting = true;   //true일때 트래킹
	int index;
	VisionDataset dataset;
	Mat detectimg;
	Mat afterimg;
	bool First_Tracking = false;  //true일때만 셋업을 하도록 한다. 
	/*멀티트래킹 플랫폼 형성*/
	Ptr<MultiTracker> multiTracker = cv::MultiTracker::create();

	std::cout << "KCF트래킹 준비 완료." << endl;

	#pragma endregion 변수 초기화

	/*실제 실행코드*/
	while (waitKey(1) < 0 && cvGetWindowHandle(window_name))
	{
		
		#pragma region start camera
		/*디텍드를 할때는 기존의 정보를 모두 제거한다.*/
		if (Detecting) {
			//VisionDataset_initialize(dataset);
			VisionDataset_initialize(dataset);
		}


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
		if (!depth_frame || !color_frame)  continue;  //버퍼 기반 프레임 확인

		/*
		static int last_frame_number = 0;
		if (color_frame.get_frame_number() == last_frame_number) continue;
		last_frame_number = color_frame.get_frame_number();    //컬러 프레임으로만 직전 코드확인하기
		*/
		#pragma endregion 카메라에서 데이타 받아오기

	
		#pragma region update_frame



		/*realsense 정보를 opencv연산가능한 이미지 행렬로 변환*/
		if (Detecting) {
			dataset.detectimg = frame_to_mat(color_frame);  //rs이미지를 cv이미지로 변환
			
			//dataset.detectimg = &detectimg; //dataset에 할당하기. 
		}
		else {

			afterimg = frame_to_mat(color_frame);
			dataset.afterimg = afterimg;
			//dataset.afterimg = &afterimg;
		}
		// cv::Mat depth_mat = depth_frame_to_meters(pipe, depth_frame);  //meter법으로 변환 행렬에 입력 허나 실제로는 사용하지 않는다. 
		
		#pragma endregion RS2함수를 opencv함수로 변환


		

		if (Detecting) {

			#pragma region detecting
			

				/*딥러닝 내부 함수*/
				blobFromImage((dataset.detectimg), blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);  //4D blob 생성 cvsize(inpWidth ,inpHeight) 함수 형식으로 받음
				net.setInput(blob);
				vector<Mat> outs;
				net.forward(outs, getOutputsNames(net));  //결과 생성
				/*딥러닝된 이미지 전처리과정 및 시간정보 입력*/
				//postprocess(dataset, outs , detectimg);     //여기서 with hight 값도 축출해야한다. 
				postprocess( outs , dataset);

				std::cout << Detecting << " detecting 시도중 // 발견된 로봇의 수: " << dataset.number_of_detection << endl;

				/*
				// 시간 데이터 가져와서 출력하는함수. (원본 이미지를 훼손하므로 제거한다)
				vector<double> layersTimes;
				double freq = getTickFrequency() / 1000;
				double t = net.getPerfProfile(layersTimes) / freq;
				string label = format("Inference time for a frame : %.2f ms", t);
				putText(*dataset.detectimg, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
				*/



				if (VisionDataset_checker(dataset.number_of_detection))  //detecting이 되지않으면 detecting을 켜고 처음위치로 돌려버린다. 
				{
					imshow(window_name, dataset.detectimg);
					Detecting = true; continue;
				}
				else {
					Detecting = false;
					imshow(window_name, dataset.detectimg);
					VisionDataset_getDepth(dataset, depth_frame); //거리 데이타 취득 
					First_Tracking = true;


#pragma endregion 욜로를 이용하여 찾는 코드
				
			}
				
				std::cout << Detecting << "  " << dataset.number_of_detection << endl;
			
		}
		else {

			#pragma region Tracking_code

			if (First_Tracking) {

				//여기에 왔다는 것은 무언가 적이 인식되었다는 뜻이다.
				Set_MultiTracker(multiTracker, "KCF", dataset, tracker);

			}


			KCFTraker_Run(dataset, multiTracker);  //KCF코드 돌리는 함수

			//KCF트래커 런하는 코드 손봐야한다. 

			if (VisionDataset_checker(dataset.number_of_detection))  // tracking이 되지않으면 detection을 켜고 처음위치로 돌려버린다. 
			{
				Detecting = true; continue;
				std::cout << Detecting << " 트래킹 실패 재시도중 " << dataset.number_of_detection << endl;
			}
			else {

				Detecting = false; // 중간에 임의로 detect를 켜는 함수가 필요하다. 

				VisionDataset_getDepth(dataset, depth_frame); //거리 데이타 취득 
				VisionDataset_continueTraking(dataset); //이함수는 최신 프레임을 기반으로 계속 추적을 유도하는 함수이다. 


			#pragma endregion KCF트래킹을 하는 코드
				
			}

			std::cout << Detecting << " 트래킹 시도중 " << dataset.number_of_detection << endl;
		}
	
		/*
		rs2::frame depth_c = data.get_depth_frame().apply_filter(color_map);
		// Query frame size (width and height)
		const int w = depth_c.as<rs2::video_frame>().get_width();
		const int h = depth_c.as<rs2::video_frame>().get_height();
		// Create OpenCV matrix of size (w,h) from the colorized depth data
		Mat image(Size(w, h), CV_8UC3, (void*)depth_c.get_data(), Mat::AUTO_STEP);   //dapth이미지를 컬러로 변경시켜줌.
		*/  
		// 거리 데이터를 컬러로 바꿔주는 함수, 여기서는 필요없음
		std::cout << Detecting <<"발견된 데이타" << " 찾은 숫자: " << dataset.number_of_detection  <<endl;
		for (index = 0; index < dataset.number_of_detection; index++) {
			std::cout << "1번적의 중점좌표:" << dataset.Center_X[index] << "," << dataset.Center_Y[index] << endl;
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

#pragma endregion 카메라 호출 실패시 출력코드

