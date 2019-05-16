#pragma once
#include "allign.hpp"

// ���� ���� https://www.learnopencv.com/multitracker-multiple-object-tracking-using-opencv-c-python/


using namespace cv;
using namespace std;
 
// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()



static Ptr<Tracker> createTrackerByName(string trackerType)
{
	/*��밡���� opencv 3.4.1 ������ traker*/
	vector<string> trackerTypes = { "BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT" };
	Ptr<Tracker> Tracker;

	if (trackerType == trackerTypes[0])
		Tracker = TrackerBoosting::create();
	else if (trackerType == trackerTypes[1])
		Tracker = TrackerMIL::create();
	else if (trackerType == trackerTypes[2])
		Tracker = TrackerKCF::create();
	else if (trackerType == trackerTypes[3])
		Tracker = TrackerTLD::create();
	else if (trackerType == trackerTypes[4])
		Tracker = TrackerMedianFlow::create();
	else if (trackerType == trackerTypes[5])
		Tracker = TrackerGOTURN::create();
	else if (trackerType == trackerTypes[6])
		Tracker = TrackerMOSSE::create();
	else if (trackerType == trackerTypes[7])
		Tracker = TrackerCSRT::create();

	else {
		cout << "Incorrect tracker name" << endl;
		cout << "Available trackers are: " << endl;
		for (vector<string>::iterator it = trackerTypes.begin(); it != trackerTypes.end(); ++it)
			std::cout << " " << *it << endl;
	}
	return Tracker;
}



static bool Set_MultiTracker(Ptr<MultiTracker> multiTracker, Mat *frame /*base data*/, string trackerTypes ,double height[], double width[], double x[], double y[]) {
	static int index;
	vector<Rect2d> bboxes;
	

	/*object�� ��� Ʈ��ŷ�� �����ϴ� ��.*/


	for (index = 0; index < 3; index++) {


		Rect2d bbox(height[index], width[index], x[index], y[index]);;
		bboxes[index] = bbox;

	}
	if (bboxes.size() < 1)

		return false;
	
	bool showCrosshair = true;
	bool fromCenter = false;



	/*multiTraker�� �����Ѵ�.*/

	
	for (int i = 0; i < bboxes.size(); i++)
		multiTracker->add(createTrackerByName(trackerTypes), *frame, Rect2d(bboxes[i]));

	return true;

}







static int KCFTraker_Run(Mat *frame /*base data*/, Mat *frame2 /*detecting*/ , Ptr<MultiTracker> multiTracker, double height[], double width[], double x[], double y[])  //�պ�����
{
   static int index;

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

		
	multiTracker->update(*frame2);

	Rect2d result[3];
	/*Ʈ��ŷ ��� ��� */
	for (index = 0; index < 3; index++) {
		if (index = multiTracker->getObjects().size()) {
			break;
		}
		result[index] = multiTracker->getObjects()[index];

		height[index] = result[index].height;
		width[index] = result[index].width;
		x[index] = result[index].x;
		y[index] = result[index].y;

	}

	/* Draw tracked objects
	for (unsigned i = 0; i < multiTracker->getObjects().size(); i++)
	{
			rectangle(*frame, multiTracker->getObjects()[i], colors[i], 2, 1);
	}
	*/

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
#pragma endregion ���� Ʈ��ŷ �ڵ� ������ �̻��
     
}


    
#pragma region ������
	//���߿� ����Լ� ȣ���ϴ� ����� ���� �õ��ϰ� ����. 
     
    // Display tracker type on frame >> ���� Ʈ��Ŀ�� ������ ���� �ִ� �ǵ� ���� �ּ�ȭ�� ���ؼ� �ʿ����
    //putText(frame, trackerType + " Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
     
    // Display FPS on frame >> �̰͵� ���� �� �ʿ�� ������. 
    // putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
 
    // Display frame. >> ���� ������ �ʿ� ����
    // imshow("Tracking", frame);
#pragma endregion ������ ����
     

 
    


static void KCFTraker_Cordinate_control(int Center_X[], int Center_Y[], double height[], double width[], double KDF_X[], double KCF_Y[])
{
	static int index;
	for (index = 0; index < 3; index++) {
		if (!Center_X[index] == 0 || !Center_Y[index] == 0) {
			KDF_X[index] = (Center_X[index]) - ((width[index]) * 0.5);
			KCF_Y[index] = (Center_Y[index]) - ((height[index]) * 0.5);
		}
	}
}