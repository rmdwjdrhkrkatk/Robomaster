import rospy
import roslib
import numpy as np
import rosnode
import rospy_message_converter
from icra_roboin_msgs.srv import SetGoal_2,BehaviorStyleSet,BlackboardGeneralInfo
from std_msgs.msg import Header

def SetGoalClient(goal_numpy):
    header = Header()
    header.frame_id="map"
    header.stamp=rospy.Time.now()
    
    rospy.wait_for_service("behavior_node/goal_select_service")
    try:
        service = rospy.ServiceProxy("behavior_node/goal_select_service",SetGoal_2)
        resp = service(header,goal_numpy[0],goal_numpy[1],goal_numpy[2],goal_numpy[3], \
	goal_numpy[4],goal_numpy[5],goal_numpy[6])
        return resp
    except rospy.ServiceException, e:
        print "Set Goal Failed: %s"%e

def SetBehaviorClient(behavior):
    rospy.wait_for_service("behavior_node/behavior_select_service")
    try:
        service = rospy.ServiceProxy("behavior_node/behavior_select_service",BehaviorStyleSet)
        resp = service(behavior)
        return resp
    except rospy.ServiceException, e:
        print "Set Behavior Failed: %s"%e

def GetInfoClient():
    rospy.wait_for_service("behavior_node/blackboard/general_info_service")
    try:
        service = rospy.ServiceProxy("behavior_node/blackboard/general_info_service",BlackboardGeneralInfo)
        resp = service(rospy.Time.now(),str(rosnode.get_node_names()))
        return rospy_message_converter.convert_ros_message_to_dictionary(resp)
    except rospy.ServiceException, e:
        print "Get Blackboard Info Failed: %s"%e
