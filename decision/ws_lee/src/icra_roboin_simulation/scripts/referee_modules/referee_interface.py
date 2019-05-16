import rospy
import roslib
import numpy as np
import rosnode
import rospy_message_converter
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Int32
from icra_roboin_msgs.srv import BlackboardGeneralInfo
from std_msgs.msg import Header
from geometry_msgs.msg import Quaternion
from tf.transformations import quaternion_from_euler,euler_from_quaternion
from roborts_msgs.msg import BonusStatus, GameResult, GameStatus, GameSurvivor, ProjectileSupply, RobotBonus, RobotDamage, RobotHeat, RobotShoot, RobotStatus, SupplierStatus, ShootInfo

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
    behavior_set = Int32()
    behavior_set.data = behavior

    pub = rospy.Publisher(robot_name + "/behavior_set",Int32, queue_size=20)
    pub.publish(behavior_set)

def GetInfoClient(robot_name="",confirm=0):
    rospy.wait_for_service(robot_name + "/blackboard/general_info_service")
    try:
        service = rospy.ServiceProxy(robot_name + "/blackboard/general_info_service",BlackboardGeneralInfo)
        resp = service(rospy.Time.now(),str(rosnode.get_node_names()),confirm)
        return rospy_message_converter.convert_ros_message_to_dictionary(resp)
    except rospy.ServiceException, e:
        print "Get Blackboard Info Failed: %s"%e


def RefereeBuffClient(robot_name=""):
    referee_buff = RobotBonus()
    referee_buff.bonus = 1

    pub = rospy.Publisher(robot_name + "/robot_bonus",RobotBonus, queue_size=20)
    pub.publish(referee_buff)



def RefereeGameStatusClient(robot_name=""):
    referee_gamestatus = GameStatus()
    referee_gamestatus.game_status = 4

    pub = rospy.Publisher(robot_name + "/game_status",GameStatus, queue_size=20)
    pub.publish(referee_gamestatus)


def RefereeHitClient(which_armor,your_hp,damage=50,bonus=0,robot_name=""):
    referee_robot_damage = RobotDamage()
    referee_robot_damage.damage_type = 0
    referee_robot_damage.damage_source = which_armor
    referee_robot_status = RobotStatus()

    if bonus:
        referee_robot_status.remaing_hp = your_hp - 25
    else:
        referee_robot_status.remaing_hp = your_hp - 50
        

    pub_1 = rospy.Publisher(robot_name + "/robot_damage",RobotDamage, queue_size=20)
    pub_2 = rospy.Publisher(robot_name + "/robot_status",RobotStatus, queue_size=20)
    pub_1.publish(referee_robot_damage)
    pub_2.publish(referee_robot_status)


#def RobotDamagePublisher(damage_type="ARMOR",damage_source="FORWARD",robot_name=""):
#    dicts = {"ARMOR":RobotDamage.ARMOR,"BACKWARD":RobotDamage.BACKWARD,"EXCEED_HEAT":RobotDamage.EXCEED_HEAT,"EXCEED_POWER":RobotDamage.EXCEED_POWER,"FORWARD":RobotDamage.FORWARD,"LEFT":RobotDamage.LEFT,"OFFLINE":RobotDamage.OFFLINE,"RIGHT":RobotDamage.RIGHT}
#    pub = rospy.Publisher(robot_name+"/robot_damage",RobotDamage,queue_size=10)
#    rate=r


def RefereeReloadClient(robot_name=""):
    referee_reload = ProjectileSupply()
    referee_reload.supply = 1


    pub = rospy.Publisher(robot_name + "/projectile_supply",ProjectileSupply, queue_size=20)
    pub.publish(referee_reload)
###   have to fix this part  ####
#def ShootClient(x,y,robot_name=""):
#    rospy.wait_for_service(robot_name + "/referee_shoot_service")
#    try:
#        service = rospy.ServiceProxy(robot_name + "/referee_shoot_service",RefereeShoot)
#        resp = service(x,y)
#        return resp.judgement
#    except rospy.ServiceException, e:
#        print "Shoot Service Failed: %s"%e

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

### have to fix it
def AmmoConsumeClient(ammo,robot_name=""):
    referee_reload = ShootInfo()
    referee_reload.remain_bullet = ammo-1


    pub = rospy.Publisher(robot_name + "/shoot_info",ShootInfo, queue_size=20)
    pub.publish(referee_reload)
