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
	multiTracker = cv::MultiTracker::create(); //������ ������ �ִ� create�� �ʱ�ȭ�Ѵ�. 

	/*object�� ��� Ʈ��ŷ�� �����ϴ� ��.*/
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
	



	/*multiTraker�� �����Ѵ�.*/

	
	for (int i = 0; i < bboxes.size(); i++)
		multiTracker->add(createTrackerByName(trackerTypes , tracker), dataset.detectimg, Rect2d(bboxes[i]));

	return true;

}



static bool KCFTraker_Run( VisionDataset& dataset , Ptr<MultiTracker> multiTracker )  //�պ�����
{
   static unsigned int index;

	/*
    // ���� ���� �д� �ڵ�, �����δ� ������� ����
    VideoCapture video("videos/chaplin.mp4");
     
    // Exit if video is not opened
    if(!video.isOpened())
    {
        cout << "Could not read video file" << endl; 
        return 1; 
    } */
    // �ڽ����� �����Ѵ�. 

	/*���ο� �̹����� ����ְ�, ����� ����Ѵ�.*/
	multiTracker->update(dataset.afterimg);  

	Rect2d result[3];
	/*Ʈ��ŷ ��� ��� */

	
	int objects = multiTracker->getObjects().size();
	if (objects != dataset.number_of_detection) {
		dataset.number_of_detection = 0;
		return false;
	}

	VisionDataset_initialize(dataset);  //���ο� �����͸� �ֱ� ���� ������ �ʱ�ȭ 
	for (index = 0; index < objects; index++) {
		//if (index = multiTracker->getObjects().size()) { break; }    //���⿡�� �ٷ� Ƣ��͹�����.

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
    // rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );  �簢���� �׸� �ʿ�� ����. 
 
    //imshow("Tracking", *frame);
    // tracker->init(*frame, bbox);


	//�Լ� ��ü�ȿ��� while������ ���� �ȵȴ�. ���� �� �Լ��� �ѹ��� �������ϴµ� ��� �ϴ� ���� ���� ���� �Ͱ���. KCFtraker�� �ѹ��� ������ִ°� ���� �Ͱ���. 
     
     
    // Start timer
    // double timer = (double)getTickCount();
     
    // Update the tracking result
    // bool ok = tracker->update(*frame2, bbox);
     
    // Calculate Frames per second (FPS)  >> ���� �� �ʿ�� ����.
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
        // Tracking failure detected.  >> �̰�� �ٸ� ���� ��ȯ�ϴ� ���� �ʿ��ҵ�,. 
        putText(*frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);

    }
*/
#pragma endregion ���� Ʈ��ŷ �ڵ� ������ �̻�� ����Ʈ ���� 1���� ���ڵ带 ������ ���� �ӵ��� �ξ� ���� ���̴�.
	return true;
}

    
#pragma region trash
	//���߿� ����Լ� ȣ���ϴ� ����� ���� �õ��ϰ� ����. 
     
    // Display tracker type on frame >> ���� Ʈ��Ŀ�� ������ ���� �ִ� �ǵ� ���� �ּ�ȭ�� ���ؼ� �ʿ����
    //putText(frame, trackerType + " Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
     
    // Display FPS on frame >> �̰͵� ���� �� �ʿ�� ������. 
    // putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
 
    // Display frame. >> ���� ������ �ʿ� ����
    // imshow("Tracking", frame);
#pragma endregion ������ ����
     


