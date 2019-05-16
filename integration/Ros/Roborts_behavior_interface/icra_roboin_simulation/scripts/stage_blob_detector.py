#!/usr/bin/env python
import roslib
import sys
import rospy
from stage_module import StageBlobDetection

if __name__ == '__main__':
	rospy.init_node('stage_blob_detector_node')
	stage_obj = StageBlobDetection.StageImageGrabber()

	try:
    		rospy.spin()
	except KeyboardInterrupt:
    		print("Shutting down")
