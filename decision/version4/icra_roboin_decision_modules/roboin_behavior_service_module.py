#!/usr/bin/env python

import rospy
import roslib
import numpy as np
import rosnode
import rospy_message_converter
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Int32
from icra_roboin_msgs.srv import BlackboardGeneralInfo #SetGoal_2,BehaviorStyleSet,RefereeShoot,RefereeTag,ConfirmHit
from std_msgs.msg import Header
from std_srvs.srv import SetBool

def SetGoalClient(goal_numpy,robot_name=""):
    goal = PoseStamped()
    goal.header.frame_id=robot_name + "/map"
    goal.header.stamp=rospy.Time.now()
    goal.pose.position.x=goal_numpy[0]
    goal.pose.position.y=goal_numpy[1]
    goal.pose.position.z=0
    goal.pose.orientation.w=0
    goal.pose.orientation.x=0
    goal.pose.orientation.y=0
    goal.pose.orientation.z=goal_numpy[2]

    pub = rospy.Publisher(robot_name + "/goal_set",PoseStamped, queue_size=20)
    pub.publish(goal)

def SetBehaviorClient(behavior,robot_name=""):

    '''rospy.wait_for_service(robot_name + "/behavior_set")
    
    try:
        service = rospy.ServiceProxy(robot_name + "/behavior_set",SetBool)
        service(behavior)
        
    except rospy.ServiceException, e:
        print "Set Goal Failed: %s"%e
    '''

    behavior_set = Int32()
    behavior_set.data = behavior

    pub = rospy.Publisher(robot_name + "/behavior_set",Int32, queue_size=20)
    pub.publish(behavior_set)



def GetInfoClient(robot_name="",confirm=1):
    rospy.wait_for_service(robot_name + "/blackboard/general_info_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/blackboard/general_info_service",BlackboardGeneralInfo)
        resp = service(rospy.Time.now(),str(rosnode.get_node_names()),confirm)
	return rospy_message_converter.convert_ros_message_to_dictionary(resp)
    except rospy.ServiceException, e:
        print "Get Blackboard Info Failed: %s"%e


