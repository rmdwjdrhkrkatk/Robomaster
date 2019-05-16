#pragma once
#include "pch.hpp"
#include "Data_Control.hpp"

using namespace cv;
using namespace std;
 
// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()


/*define trakcer`s type and configure it*/
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

/*define initial condition for Trakcer*/
static bool Set_MultiTracker(Ptr<MultiTracker>& multiTracker, string trackerTypes , VisionDataset& dataset , Ptr<Tracker>& tracker) {
	
	int index;
	int index2;
	short Total_Trakcing_num = 0;
	Total_Trakcing_num = dataset.number_of_detection + dataset.armour[1].number_of_armer + dataset.armour[2].number_of_armer;


	vector<Rect> bboxes(Total_Trakcing_num);   //number of total KCF trakcer
	multiTracker = cv::MultiTracker::create(); //initiallize Multi traker  

	/*if there are no object, stop traking*/
	bool showCrosshair = true;
	bool fromCenter = false;
	int realnumber;
	static int flage = 0;
	dataset.trakcer_data[0] = 4;
	dataset.trakcer_data[1] = 4;
	dataset.trakcer_data[2] = 4;

	// first/ flage have a input data
	// and restore after tracking

	// all tracking data`s number became numberofrobot + number_of_armers (need to release allay`s armer - done )
	// if bocome this porcess, enemy is detected 


	// main robot, input check 3 robot data
	for (index = 0; index < 3; index++) {

		if (dataset.height[index] > 0 && dataset.width[index] > 0 && dataset.KCF_X[index] > 0 && dataset.KCF_Y[index] > 0) {
			dataset.trakcer_data[flage] = index ;
			Rect2d bbox(dataset.KCF_X[index], dataset.KCF_Y[index], dataset.width[index], dataset.height[index]);
			//Rect2d bbox(dataset.height[index], dataset.width[index], dataset.KCF_X[index], dataset.KCF_Y[index]);
			bboxes[flage] = bbox;

			flage = flage +1 ;
		}

	}

	// to check armer data. and make it
	for (index = 1; index < 3; index++) {  //accese enemy robot data
		for (index2 = 0; index2 = dataset.armour[index].number_of_armer; index2++) { //I think it could be need to control zero value
			Rect2d bbox(dataset.armour[index].Center_x[index2] - 0.5 * dataset.armour[index].width[index2], dataset.armour[index].Center_y[index2] - 0.5 * dataset.armour[index].height[index2]
			, dataset.armour[index].width[index2] , dataset.armour[index].height[index2]);

			bboxes[flage] = bbox;
			flage = flage + 1;
		}

	}

	if (flage != Total_Trakcing_num) {
		std::cout << "KCF_Trakcer`s box number has porblem" << std::endl;
	}


// below codes for input data to KCF tracker
	if (bboxes.size() < 1) { return false; }

	/*generate MultiTraker*/
	
	for (int i = 0; i < bboxes.size(); i++)
		multiTracker->add(createTrackerByName(trackerTypes , tracker), dataset.detectimg, Rect2d(bboxes[i]));

	return true;

}


/*function for running KCF traker*/
static bool KCFTraker_Run( VisionDataset& dataset , Ptr<MultiTracker> multiTracker )  //error could be occur 
{
    static unsigned int index;
	static int flage;
	flage = 0;
	int count = 0;
	short NOD = 0;

	// Total_Trakcing_num = dataset.number_of_detection + dataset.armour[1].number_of_armer + dataset.armour[2].number_of_armer;
	/*
    // read video file but it is useless on this program
    VideoCapture video("videos/chaplin.mp4");
     
    // Exit if video is not opened
    if(!video.isOpened())
    {
        cout << "Could not read video file" << endl; 
        return 1; 
    } */

	


    // define boxes

	/* input new imf and extract result*/
	multiTracker->update(dataset.afterimg);  

	Rect2d result[3];
	/* display reult of traking */
	int objects = multiTracker->getObjects().size();
	if (objects != dataset.number_of_detection) {
		dataset.number_of_detection = 0;
		return false;
	}

	VisionDataset_initialize(dataset);  // before input new data, initialze VidionDataset 
	for (index = 0; index < objects; index++) {
		//if (index = multiTracker->getObjects().size()) { break; }    // if use this function, error occur

		result[index] = multiTracker->getObjects()[index];

		//result might be input order 
		//ù���� ����Ÿ ���� �����ϴ°�! 
		if (flage != 100) {
			for (count = 0; count < 3; count++) {
				if (dataset.trakcer_data[count] < 4) {
					flage = dataset.trakcer_data[count];
					dataset.trakcer_data[count] = 4;
					NOD++;  //count number of detection
					break;
				}
				flage = 100;
			}
		}

		if (flage != 100) {  //robot_state
			
			dataset.height[flage] = result[index].height;
			dataset.width[flage] = result[index].width;
			dataset.Center_X[flage] = (result[index].x + 0.5 * result[index].width);
			dataset.Center_Y[flage] = (result[index].y + 0.5 * result[index].height);
			dataset.KCF_X[flage] = result[index].x;
			dataset.KCF_Y[flage] = result[index].y;
			/*
			if (result[index].x > 0 && result[index].y > 0) {
				dataset.number_of_detection = index + 1;
			} else {
				dataset.number_of_detection = 0;
			}   // for old version. and it occur unintended funcion.
			*/
		}
		else if (dataset.number_of_detection  <= index && index < dataset.number_of_detection + dataset.armour[1].number_of_armer && dataset.armour[1].number_of_armer != 0) {
			// this is number 1`s armer data
			dataset.armour[1].Center_x[index - dataset.number_of_detection] = (result[index].x + 0.5 * result[index].width);
			dataset.armour[1].Center_y[index - dataset.number_of_detection] = (result[index].y + 0.5 * result[index].height);
			dataset.armour[1].height[index - dataset.number_of_detection] = result[index].height;
			dataset.armour[1].width[index - dataset.number_of_detection] = result[index].width;

		}
		else if (dataset.number_of_detection + dataset.armour[1].number_of_armer <= index && index < dataset.number_of_detection + dataset.armour[1].number_of_armer + dataset.armour[2].number_of_armer && dataset.armour[2].number_of_armer != 0) {
			dataset.armour[2].Center_x[index - dataset.number_of_detection] = (result[index].x + 0.5 * result[index].width);
			dataset.armour[2].Center_y[index - dataset.number_of_detection] = (result[index].y + 0.5 * result[index].height);
			dataset.armour[2].height[index - dataset.number_of_detection] = result[index].height;
			dataset.armour[2].width[index - dataset.number_of_detection] = result[index].width;
		}


	}

	// need more data 

	dataset.number_of_detection = NOD;

	std::cout << "Tracking complete, detected:" << dataset.number_of_detection << std::endl;

#ifdef DISPLAY
	/* Draw tracked objects */
	for (unsigned i = 0; i < multiTracker->getObjects().size(); i++)
	{
			rectangle(dataset.display, multiTracker->getObjects()[i], Scalar(0, 0, 255) , 2, 1);
	}
#endif

	dataset.trakcer_data[0] = 4;
	dataset.trakcer_data[1] = 4;
	dataset.trakcer_data[2] = 4;

#pragma region single traking
/*
   //  Rect2d bbox(*height, *width, *x, *y);
 
    // Uncomment the line below to select a different bounding box 
    // bbox = selectROI(frame, false); 
    // Display bounding box. 
    // rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 ); // we dont need to make rectangle  
 
    //imshow("Tracking", *frame);
    // tracker->init(*frame, bbox);


    // during function opperation, do not use while function beacuse it can`t breakout. and KCFtraker sutruct must be define only ones 
     
    // Start timer
    // double timer = (double)getTickCount();
     
    // Update the tracking result
    // bool ok = tracker->update(*frame2, bbox);
     
    // Calculate Frames per second (FPS)  // doesn`t needed
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
        // Tracking failure detected.  ,. 
        putText(*frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);

    }
*/
#pragma endregion 
	return true;
}

    
#pragma region trash
	// . 
     
    // Display tracker type on frame 
    //putText(frame, trackerType + " Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
     
    // Display FPS on frame  
    // putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
 
    // Display frame. 
	// imshow("Tracking", frame);
#pragma endregion 
     


