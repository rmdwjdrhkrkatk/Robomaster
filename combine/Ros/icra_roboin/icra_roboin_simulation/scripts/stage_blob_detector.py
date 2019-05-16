#!/usr/bin/env python
import roslib
import sys
import rospy
from stage_module import StageBlobDetection

if __name__ == '__main__':
	rospy.init_node('stage_blob_detector_node')
	my_color = rospy.get_param('~my_color')
	ally_color = rospy.get_param('~ally_color')
	enemy1_color = rospy.get_param('~enemy1_color')
	enemy2_color = rospy.get_param('~enemy2_color')

	

	stage_obj = StageBlobDetection.StageImageGrabber(my_color,ally_color,enemy1_color,enemy2_color)

	try:
    		rospy.spin()
	except KeyboardInterrupt:
    		print("Shutting down")
