#!/usr/bin/env python
import roslib
import sys
import rospy
from stage_module import StageBlobDetection

if __name__ == '__main__':
	rospy.init_node('stage_blob_detector_node')
        my_color = 'blue'
        ally_color = 'blue'
        enemy1_color = 'red'
        enemy2_color = 'red'

	

	stage_obj = StageBlobDetection.StageImageGrabber(my_color,ally_color,enemy1_color,enemy2_color)

	try:
    		rospy.spin()
	except KeyboardInterrupt:
    		print("Shutting down")
