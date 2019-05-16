import rospy
import roslib
import numpy as np
import rosnode
import rospy_message_converter
from icra_roboin_msgs.srv import SetGoal_2,BehaviorStyleSet,BlackboardGeneralInfo,RefereeBuff,RefereeGameState,RefereeHit,RefereePenalty,RefereeShoot,RefereeTag,RefereeReload,RefereeShoot,RefereeTag,AmmoConsume
from icra_roboin_msgs.msg import GoalDescription
from std_msgs.msg import Header
from geometry_msgs.msg import Quaternion
from tf.transformations import quaternion_from_euler,euler_from_quaternion

def SetGoalClient(goal_numpy,robot_name=""):
    goal = GoalDescription()
    goal.header.frame_id=robot_name + "/map"
    goal.header.stamp=rospy.Time.now()
    goal.x=goal_numpy[0]
    goal.y=goal_numpy[1]
    goal.yaw=goal_numpy[2]
    goal.xa=goal_numpy[3]
    goal.ya=goal_numpy[4]
    goal.yawa=goal_numpy[5]
    goal.etc=goal_numpy[6]
    rospy.wait_for_service(robot_name + "/behavior_node/goal_select_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/behavior_node/goal_select_service",SetGoal_2)
        resp = service(goal)
        return resp
    except rospy.ServiceException, e:
        print "Set Goal Failed: %s"%e

def SetBehaviorClient(behavior,robot_name=""):
    rospy.wait_for_service(robot_name + "/behavior_node/behavior_select_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/behavior_node/behavior_select_service",BehaviorStyleSet)
        resp = service(behavior)
        return resp
    except rospy.ServiceException, e:
        print "Set Behavior Failed: %s"%e

def GetInfoClient(robot_name="",confirm=0):
    rospy.wait_for_service(robot_name + "/behavior_node/blackboard/general_info_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/behavior_node/blackboard/general_info_service",BlackboardGeneralInfo)
        resp = service(rospy.Time.now(),str(rosnode.get_node_names()),confirm)
        return rospy_message_converter.convert_ros_message_to_dictionary(resp)
    except rospy.ServiceException, e:
        print "Get Blackboard Info Failed: %s"%e


def RefereeBuffClient(buff_type=0, damage_multiplier = 0.5,robot_name=""):
    rospy.wait_for_service(robot_name + "/referee_buff_service")
    header = Header()
    header.frame_id = "/referee_map"
    header.stamp = rospy.Time.now()
    try:
        service = rospy.ServiceProxy(robot_name + "/referee_buff_service",RefereeBuff)
        resp = service(header,buff_type,damage_multiplier)
        return resp
    except rospy.ServiceException, e:
        print "Referee Buff Service Failed: %s"%e    

def RefereeGameStateClient(game_state,robot_name=""):
    rospy.wait_for_service(robot_name + "/referee_game_state_service")
    header = Header()
    header.frame_id = "/referee_map"
    header.stamp = rospy.Time.now()
    try:
        service = rospy.ServiceProxy(robot_name + "/referee_game_state_service",RefereeGameState)
        resp = service(header,game_state)
        return resp
    except rospy.ServiceException, e:
        print "Referee Game State Service Failed: %s"%e    

def RefereeHitClient(which_armor,your_hp,damage=50,robot_name=""):
    rospy.wait_for_service(robot_name + "/referee_hit_service")
    header = Header()
    header.frame_id = "/referee_map"
    header.stamp = rospy.Time.now()
    try:
        service = rospy.ServiceProxy(robot_name + "/referee_hit_service",RefereeHit)
        resp = service(header,damage,your_hp,which_armor)
        return resp
    except rospy.ServiceException, e:
        print "Referee Hit Service Failed: %s"%e 

def RefereePenaltyClient(penalty=0, damage = 1000,robot_name=""):
    rospy.wait_for_service(robot_name + "/referee_penalty_service")
    header = Header()
    header.frame_id = "/referee_map"
    header.stamp = rospy.Time.now()
    try:
        service = rospy.ServiceProxy(robot_name + "/referee_penalty_service",RefereePenalty)
        resp = service(header,penalty,damage)
        return resp
    except rospy.ServiceException, e:
        print "Referee Penalty Service Failed: %s"%e

def RefereeReloadClient(robot_name=""):
    rospy.wait_for_service(robot_name + "/referee_reload_service")
    header = Header()
    header.frame_id = "/referee_map"
    header.stamp = rospy.Time.now()
    try:
        service = rospy.ServiceProxy(robot_name + "/referee_reload_service",RefereeReload)
        resp = service(header)
        return resp
    except rospy.ServiceException, e:
        print "Referee Reload Service Failed: %s"%e

def ShootClient(x,y,robot_name=""):
    rospy.wait_for_service(robot_name + "/referee_shoot_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/referee_shoot_service",RefereeShoot)
        resp = service(x,y)
        return resp.judgement
    except rospy.ServiceException, e:
        print "Shoot Service Failed: %s"%e

def TagClient(robot_name=""):
    rospy.wait_for_service(robot_name + "/referee_tag_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/referee_tag_service",RefereeTag)
        resp = service()
        return resp.info
    except rospy.ServiceException, e:
        print "Tag Service Failed: %s"%e

def YawToQuaternion(yaw):
	quat_tf = quaternion_from_euler(0,0,yaw)
	#type(pose) = geometry_msgs.msg.Pose
	#pose.orientation.x = quaternion[0]
	#pose.orientation.y = quaternion[1]
	#pose.orientation.z = quaternion[2]
	#pose.orientation.w = quaternion[3]
	return Quaternion(quat_tf[0],quat_tf[1],quat_tf[2],quat_tf[3])

def QuaternionToYaw(quaternion):
	#type(pose) = geometry_msgs.msg.Pose
	#quaternion = (
	#    pose.orientation.x,
	#    pose.orientation.y,
	#    pose.orientation.z,
	#    pose.orientation.w)
	#euler = tf.transformations.euler_from_quaternion(quaternion)
	#roll = euler[0]
	#pitch = euler[1]
	#yaw = euler[2]
	quat_tf = (quaternion.x,quaternion.y,quaternion.z,quaternion.w)
	return (euler_from_quaternion(quat_tf))[2]


def AmmoConsumeClient(shots=1,robot_name=""):
    rospy.wait_for_service(robot_name + "/behavior_node/ammo_consume_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/behavior_node/ammo_consume_service",AmmoConsume)
        resp = service(shots)
        return resp.success
    except rospy.ServiceException, e:
        print "Ammo Consume Service Failed: %s"%e


