#!/usr/bin/env python
import roslib
import sys
import rospy
from sensor_msgs.msg import LaserScan

if __name__ == '__main__':
    rospy.init_node('stage_laser_topic_transcriber_node')
    pub0 = rospy.Publisher("robot_0/scan",LaserScan,queue_size=1)
    pub1 = rospy.Publisher("robot_1/scan",LaserScan,queue_size=1)
    pub2 = rospy.Publisher("robot_2/scan",LaserScan,queue_size=1)
    pub3 = rospy.Publisher("robot_3/scan",LaserScan,queue_size=1)


    def CB0(data):
        data_ = data
        data_.header.frame_id = "robot_0/base_laser_link"
        pub0.publish(data_)
    def CB1(data):
        data_ = data
        data_.header.frame_id = "robot_1/base_laser_link"
        pub1.publish(data_)
    def CB2(data):
        data_ = data
        data_.header.frame_id = "robot_2/base_laser_link"
        pub2.publish(data_)
    def CB3(data):
        data_ = data
        data_.header.frame_id = "robot_3/base_laser_link"
        pub3.publish(data_)
    
    rospy.Subscriber("robot_0/base_scan",LaserScan,CB0)
    rospy.Subscriber("robot_1/base_scan",LaserScan,CB1)
    rospy.Subscriber("robot_2/base_scan",LaserScan,CB2)
    rospy.Subscriber("robot_3/base_scan",LaserScan,CB3)

    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
