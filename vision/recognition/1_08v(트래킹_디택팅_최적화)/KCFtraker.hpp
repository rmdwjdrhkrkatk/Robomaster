#pragma once
#include "allign.hpp"

using namespace cv;
using namespace std;
 
// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()



static Ptr<Tracker> createTrackerByName(string trackerType, Ptr<Tracker>& tracker)
{
	vector<string> trackerTypes = { "BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT" };

	

	if (trackerType == trackerTypes[0])
		tracker = TrackerBoosting::create();
	else if (trackerType == trackerTypes[1])
		tracker = TrackerMIL::create();
	else if (trackerType == trackerTypes[2])
		tracker = TrackerKCF::create();
	else if (trackerType == trackerTypes[3])
		tracker = TrackerTLD::create();
	else if (trackerType == trackerTypes[4])
		tracker = TrackerMedianFlow::create();
	else if (trackerType == trackerTypes[5])
		tracker = TrackerGOTURN::create();
	else if (trackerType == trackerTypes[6])
		tracker = TrackerMOSSE::create();
	else if (trackerType == trackerTypes[7])
		tracker = TrackerCSRT::create();
	else {
		cout << "Incorrect tracker name" << endl;
		cout << "Available trackers are: " << endl;
		for (vector<string>::iterator it = trackerTypes.begin(); it != trackerTypes.end(); ++it)
			std::cout << " " << *it << endl;
	}
	return tracker;
}


static bool Set_MultiTracker(Ptr<MultiTracker>& multiTracker, string trackerTypes , VisionDataset& dataset , Ptr<Tracker>& tracker) {
	static int index;
	vector<Rect> bboxes(dataset.number_of_detection);
	multiTracker = cv::MultiTracker::create(); //기존에 가지고 있는 create를 초기화한다. 

	/*object가 없어서 트래킹을 종료하는 것.*/
	bool showCrosshair = true;
	bool fromCenter = false;


	for (index = 0; index < dataset.number_of_detection; index++) {

		if (dataset.height[index] > 0 && dataset.width[index] > 0 && dataset.KCF_X[index] > 0 && dataset.KCF_Y[index] > 0) {


			
			Rect2d bbox(dataset.KCF_X[index], dataset.KCF_Y[index], dataset.width[index], dataset.height[index]);
			//Rect2d bbox(dataset.height[index], dataset.width[index], dataset.KCF_X[index], dataset.KCF_Y[index]);
			bboxes[index] = bbox;   
		}

	}
	if (bboxes.size() < 1)	return false; 
	



	/*multiTraker를 생성한다.*/

	
	for (int i = 0; i < bboxes.size(); i++)
		multiTracker->add(createTrackerByName(trackerTypes , tracker), dataset.detectimg, Rect2d(bboxes[i]));

	return true;

}



static bool KCFTraker_Run( VisionDataset& dataset , Ptr<MultiTracker> multiTracker )  //손봐야함
{
   static unsigned int index;

	/*
    // 비디오 파일 읽는 코드, 실제로는 사용하지 않음
    VideoCapture video("videos/chaplin.mp4");
     
    // Exit if video is not opened
    if(!video.isOpened())
    {
        cout << "Could not read video file" << endl; 
        return 1; 
    } */
    // 박스들을 정의한다. 

	/*새로운 이미지를 집어넣고, 결과를 출력한다.*/
	multiTracker->update(dataset.afterimg);  

	Rect2d result[3];
	/*트래킹 결과 출력 */

	
	int objects = multiTracker->getObjects().size();
	if (objects != dataset.number_of_detection) {
		dataset.number_of_detection = 0;
		return false;
	}

	VisionDataset_initialize(dataset);  //새로운 데이터를 넣기 전에 데이터 초기화 
	for (index = 0; index < objects; index++) {
		//if (index = multiTracker->getObjects().size()) { break; }    //여기에서 바로 튀어나와버린다.

		result[index] = multiTracker->getObjects()[index];
		dataset.height[index] = result[index].height;
		dataset.width[index] = result[index].width;
		dataset.Center_X[index] = (result[index].x + 0.5*result[index].width);
		dataset.Center_Y[index] = (result[index].y + 0.5*result[index].height);
		dataset.KCF_X[index] = result[index].x;
		dataset.KCF_Y[index] = result[index].y;
		if (result[index].x > 0 && result[index].y > 0) {
			dataset.number_of_detection = index + 1;
		}
		else {
			dataset.number_of_detection = 0;
		}

	}

	/* Draw tracked objects */
	for (unsigned i = 0; i < multiTracker->getObjects().size(); i++)
	{
			rectangle(dataset.display, multiTracker->getObjects()[i], Scalar(0, 0, 255) , 2, 1);
	}
	

#pragma region single traking
/*
   //  Rect2d bbox(*height, *width, *x, *y);
 
    // Uncomment the line below to select a different bounding box 
    // bbox = selectROI(frame, false); 
    // Display bounding box. 
    // rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );  사각형을 그릴 필요는 없다. 
 
    //imshow("Tracking", *frame);
    // tracker->init(*frame, bbox);


	//함수 자체안에서 while문으로 돌면 안된다. 따라서 이 함수는 한번만 돌려야하는데 계속 하는 것은 좋지 않을 것같다. KCFtraker는 한번만 만들어주는게 좋을 것같다. 
     
     
    // Start timer
    // double timer = (double)getTickCount();
     
    // Update the tracking result
    // bool ok = tracker->update(*frame2, bbox);
     
    // Calculate Frames per second (FPS)  >> 굳이 할 필요는 없음.
    // float fps = getTickFrequency() / ((double)getTickCount() - timer);
	if (ok)
	{
        // Tracking success : Draw the tracked object
        //rectangle(*frame2, bbox, Scalar( 255, 0, 0 ), 2, 1 );
		*height = bbox.height;
		*width = bbox.width;
		*x = bbox.x;
		*y = bbox.y;

    }
    else
    {
        // Tracking failure detected.  >> 이경우 다른 값을 반환하는 것이 필요할듯,. 
        putText(*frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);

    }
*/
#pragma endregion 단일 트래킹 코드 지금은 미사용 디텍트 값이 1개면 이코드를 돌리는 것이 속도가 훨씬 빠를 것이다.
	return true;
}

    
#pragma region trash
	//나중에 재귀함수 호출하는 방법도 좋은 시도일것 같다. 
     
    // Display tracker type on frame >> 무슨 트래커를 썻는지 집어 넣는 건데 연산 최소화를 위해서 필요없음
    //putText(frame, trackerType + " Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
     
    // Display FPS on frame >> 이것도 굳이 할 필요는 ㅇ벗음. 
    // putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
 
    // Display frame. >> 굳이 보여줄 필요 없음
    // imshow("Tracking", frame);
#pragma endregion 쓰래기 값들
     


