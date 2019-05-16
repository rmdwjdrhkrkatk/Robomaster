//���� �ڵ�
#include "KCFtraker.hpp"

using namespace cv;     //opencv ���� �Լ� ���
using namespace dnn;    //dnn�Լ� ���
using namespace std;    //cpp�⺻ �Լ� ���̺귯�� ���

//void postprocess(VisionDataset dataset, const vector<Mat> &outs  , Mat& detectimg);

void postprocess(Mat& frame, const vector<Mat>& outs , VisionDataset& dataset);
void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);
vector<String> getOutputsNames(const Net& net);

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
	Ptr<Tracker> tracker = createTrackerByName("KCF");
	#pragma endregion KCFƮ��Ŀ ����

	#pragma region var initialization
	/*��� �̹���â ����*/
	const auto window_name = "Display Image";
	namedWindow(window_name, WINDOW_AUTOSIZE);
	/*�߰� ����*/
	bool Detecting = true;
	int index;
	VisionDataset dataset;
	Mat detectimg;
	Mat afterimg;
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
			dataset.number_of_detection = 0;

			for (int index = 0; index < 3; index++) {

				dataset.Center_X[index] = 0;
				dataset.Center_Y[index] = 0;
				dataset.height[index] = 0;
				dataset.width[index] = 0;
				dataset.KCF_X[index] = 0;
				dataset.KCF_Y[index] = 0;
				dataset.distance[index] = 0;
			}
			
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
			detectimg = frame_to_mat(color_frame);  //rs�̹����� cv�̹����� ��ȯ
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
				blobFromImage(detectimg, blob, 1 / 255.0, cvSize(inpWidth, inpHeight), Scalar(0, 0, 0), true, false);  //4D blob ���� cvsize(inpWidth ,inpHeight) �Լ� �������� ����
				net.setInput(blob);
				vector<Mat> outs;
				net.forward(outs, getOutputsNames(net));  //��� ����
				/*�����׵� �̹��� ��ó������ �� �ð����� �Է�*/
				//postprocess(dataset, outs , detectimg);     //���⼭ with hight ���� �����ؾ��Ѵ�. 
				postprocess(detectimg, outs , dataset);

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
					imshow(window_name, (detectimg));
					Detecting = true; continue;
				}
				else {
					Detecting = false;
					imshow(window_name, (detectimg));
					VisionDataset_getDepth(dataset, depth_frame); //�Ÿ� ����Ÿ ��� 

#pragma endregion ��θ� �̿��Ͽ� ã�� �ڵ�
				
			}
				
				std::cout << Detecting << "  " << dataset.number_of_detection << endl;
			
		}
		else {

			#pragma region Tracking_code



			 //���⿡ �Դٴ� ���� ���� ���� �νĵǾ��ٴ� ���̴�.
			Set_MultiTracker(multiTracker, "KCF", dataset);

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
			std::cout << " , 1������ ������ǥ:" << dataset.Center_X[index] << "," << dataset.Center_Y[index] << endl;
		}
		imshow(window_name, (detectimg));
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


/*
void postprocess(VisionDataset dataset, const vector<Mat> &outs , Mat& detectimg)
{
	

	int index;

	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<Rect> boxes;




	for (size_t i = 0; i < outs.size(); ++i)
	{
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		float* data = (float*)outs[i].data;
		for (static int j = 0, index = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);


			if (confidence > confThreshold || index < 3)
			{
				int centerX = (int)(data[0] * detectimg.cols);
				int centerY = (int)(data[1] * detectimg.rows);
				int width = (int)(data[2] * detectimg.cols);
				int height = (int)(data[3] * detectimg.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, width, height));


			}
		}
	}

	// Perform non maximum suppression to eliminate redundant overlapping boxes with
	// lower confidences
	std::vector<int> indices;
	NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0, index = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];



		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, detectimg);
		//�ڽ��׸��� �Լ��� ������. �̹��� ���� ȳ�� ������

		dataset.Center_X[index] = (box.x + box.width*0.5);
		dataset.Center_Y[index] = (box.y + box.height*0.5);

		dataset.height[index] = (double)box.height;
		dataset.width[index] = (double)box.width;
		index++;   //��ġ�� �ֵ� ó�����Ŀ� �� �����͸� �����´�. �� 3���� �޾ƿ�

		dataset.number_of_detection = index;

	}
	VisionDataset_KCFCORMaker(dataset); //kcf�� ��ǥ�� ��ȯ �ڵ嵵 ���⼭ �����Ѵ�.
}

*/

void postprocess(Mat& frame, const vector<Mat>& outs, VisionDataset& dataset)
{
	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > confThreshold)
			{
				int centerX = (int)(data[0] * frame.cols);
				int centerY = (int)(data[1] * frame.rows);
				int width = (int)(data[2] * frame.cols);
				int height = (int)(data[3] * frame.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, width, height));
			}

			
		}
	}

	// Perform non maximum suppression to eliminate redundant overlapping boxes with
	// lower confidences
	vector<int> indices;
	NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];
		drawPred(classIds[idx], confidences[idx], box.x, box.y,
			box.x + box.width, box.y + box.height, frame);

		dataset.Center_X[idx] = (box.x + box.width*0.5);
		dataset.Center_Y[idx] = (box.y + box.height*0.5);

		dataset.height[idx] = (double)box.height;
		dataset.width[idx] = (double)box.width;
		  //��ġ�� �ֵ� ó�����Ŀ� �� �����͸� �����´�. �� 3���� �޾ƿ�

		dataset.number_of_detection = idx +1;

	}

	VisionDataset_KCFCORMaker(dataset);
}

// Draw the predicted bounding box
void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
	//Draw a rectangle displaying the bounding box
	rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);

	//Get the label for the class name and its confidence
	string label = format("%.2f", conf);
	if (!classes.empty())
	{
		CV_Assert(classId < (int)classes.size());
		label = classes[classId] + ":" + label;
	}

	//Display the label at the top of the bounding box
	int baseLine;
	Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
	top = max(top, labelSize.height);
	rectangle(frame, Point(left, top - round(1.5*labelSize.height)), Point(left + round(1.5*labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
	putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
}

// Get the names of the output layers
vector<String> getOutputsNames(const Net& net)
{
	static vector<String> names;
	if (names.empty())
	{
		//Get the indices of the output layers, i.e. the layers with unconnected outputs
		vector<int> outLayers = net.getUnconnectedOutLayers();

		//get the names of all the layers in the network
		vector<String> layersNames = net.getLayerNames();

		// Get the names of the output layers in names
		names.resize(outLayers.size());
		for (size_t i = 0; i < outLayers.size(); ++i)
			names[i] = layersNames[outLayers[i] - 1];
	}
	return names;
}
