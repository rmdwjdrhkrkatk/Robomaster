#!/usr/bin/env python
import math
import rospy
import roslib
import numpy as np
from referee_modules.referee_interface import GetInfoClient, RefereeBuffClient,RefereeGameStatusClient,RefereeHitClient,RefereeReloadClient,YawToQuaternion,QuaternionToYaw
from icra_roboin_msgs.srv import BlackboardGeneralInfo
from nav_msgs.msg import Odometry
from std_msgs.msg import Header
from geometry_msgs.msg import Quaternion, PointStamped,PoseStamped
from tf.transformations import quaternion_from_euler, euler_from_quaternion
from roborts_msgs.msg import BonusStatus, GameResult, GameStatus, GameSurvivor, ProjectileSupply, RobotBonus, RobotDamage, RobotHeat, RobotShoot, RobotStatus, SupplierStatus, ShootInfo
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import Int32

class Robot:
    def __init__(self,robot_name = "",team="blue"):
        self.x = 0
        self.y = 0
        self.orientation = Quaternion()
        self.team = team
        self.robot_name = robot_name
        self.hp = 0
        self.ammo = 0
        self.is_reloading = False
        self.reload_time = 0
        self.real_pose_subscriber = rospy.Subscriber(self.robot_name + "/base_pose_ground_truth",Odometry,self.RealPoseCB)
        self.pose_publisher = rospy.Publisher(self.robot_name + "/referee_pose",PoseStamped,queue_size=1)
        self.shootmark_pub = rospy.Publisher(self.robot_name + "/shoot_mark",PointStamped,queue_size=1)
	self.robot_damage_pub = rospy.Publisher(self.robot_name+"/robot_damage",RobotDamage,queue_size=10)
    def RealPoseCB(self,msg):
        self.x = msg.pose.pose.position.x
        self.y = msg.pose.pose.position.y
        self.orientation = msg.pose.pose.orientation
        pose = PoseStamped()
        pose.header.stamp = msg.header.stamp
        pose.header.frame_id = "referee_map"
        pose.pose = msg.pose.pose
        self.pose_publisher.publish(pose)


class Referee2vs2:
    def __init__(self):
        self.robot0=Robot(robot_name="robot_0",team="blue")
        self.robot1=Robot(robot_name="robot_1",team="red")
#        self.shoot_server_0 = rospy.Service("robot_0"+'/referee_shoot_service',RefereeShoot,self.ShootCB_0)
#        self.shoot_server_1 = rospy.Service("robot_1"+'/referee_shoot_service',RefereeShoot,self.ShootCB_1)
#        self.tag_server_0 = rospy.Service("robot_0"+'/referee_tag_service',RefereeTag,self.TagCB_0)
#        self.tag_server_1 = rospy.Service("robot_1"+'/referee_tag_service',RefereeTag,self.TagCB_1)
        self.hit_damage = 15
        self.start_ammo = 50
        self.start_hp = 1000
        self.game_state = 1   #dead ready play end
        self.game_start_time = 0
        self.winner = 0
        self.ReadyInit()
        
    def Run(self):
        if self.game_state == 3:
            print self.winner
            print "end->ready"
            self.game_state = 1
            self.ReadyInit()
        if self.game_state == 1:
            #print "ready check"
            if self.ReadyCheck():
                print "start"
                self.game_state = 2
                self.PlayInit()
        if self.game_state == 2:
            #print "playing"
            self.Play()     
                
    def PlayInit(self):
        self.robot0.hp = self.start_hp
        self.robot1.hp = self.start_hp
        RefereeGameStateClient(2,"robot_0")
        RefereeGameStateClient(2,"robot_1")
        self.game_start_time = rospy.Time.now()

            
        
    def Play(self):
        
        if self.robot0.is_reloading :
            if( (rospy.Time.now() - self.robot0.reload_time).to_sec() > 5 ):
                RefereeReloadClient("robot_0")
                self.robot0.is_reloading=False
        if self.robot1.is_reloading :
            if( (rospy.Time.now() - self.robot1.reload_time).to_sec() > 5 ):
                RefereeReloadClient("robot_1")
                self.robot1.is_reloading=False    
        
        
        if self.robot0.hp <= 0 and self.robot1.hp <= 0:
            RefereeGameStateClient(3,"robot_0")
            RefereeGameStateClient(3,"robot_1")
            self.game_state = 3
            self.winner = "winner: draw"
        if self.robot0.hp <= 0:
            RefereeGameStateClient(3,"robot_0")
            RefereeGameStateClient(3,"robot_1")
            self.game_state = 3
            self.winner = "winner: robot_1"
        elif self.robot1.hp <= 0:
            RefereeGameStateClient(3,"robot_0")
            RefereeGameStateClient(3,"robot_1")
            self.game_state = 3
            self.winner = "winner: robot_0"
    
    def ReadyInit(self):
        RefereeGameStatusClient("robot_0")
        RefereeGameStatusClient("robot_1")
        self.winner = 0
    def ReadyCheck(self):
        if (((self.robot0.x - 1) ** 2) + ((self.robot0.y-1) ** 2)) <= 0.3 and (((self.robot1.x - 7) ** 2) + ((self.robot1.y-4) ** 2)) <= 0.3:
            #print "ready"
            return True
        else:
            #print "not ready"
            return False
    
    
        
        
        
        
    def ShootCB_0(self,req):
        point = PointStamped()
        point.header.stamp = rospy.Time.now()
        point.header.frame_id = "referee_map"
        point.point.x= req.x
        point.point.y= req.y
        point.point.z= 0.1
        
        self.robot0.shootmark_pub.publish(point)
        if req.x <-4 and req.y < -4:
            return RefereeShootResponse(5,True)
        elif ((self.robot1.x - req.x)**2) + ((self.robot1.y - req.y)**2) < 0.25:
            
            
            self.robot1.hp -= self.hit_damage
            hit_angle =(math.atan2(self.robot0.y-self.robot1.y,self.robot0.x-self.robot1.x) - QuaternionToYaw(self.robot1.orientation)) % 6.283184
            if 0 <= hit_angle and hit_angle < 0.785398:
                #RefereeHitClient(0,self.robot1.hp,self.hit_damage,"robot_1")
		self.robot1.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.FORWARD)
                print "robot_1 hit: front armor"
            if 0.785398 <= hit_angle and hit_angle < 2.356194:
                #RefereeHitClient(1,self.robot1.hp,self.hit_damage,"robot_1")
		self.robot1.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.LEFT)
                print "robot_1 hit: left armor"
            if 2.356194 <= hit_angle and hit_angle < 3.92699:
                #RefereeHitClient(2,self.robot1.hp,self.hit_damage,"robot_1")
		self.robot1.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.BACKWARD)
                print "robot_1 hit: rear armor"
            if 3.92699 <= hit_angle and hit_angle < 5.497786:
                #RefereeHitClient(3,self.robot1.hp,self.hit_damage,"robot_1")
		self.robot1.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.RIGHT)
                print "robot_1 hit: right armor"
            if 5.497786 <= hit_angle and hit_angle < 6.3:
                #RefereeHitClient(0,self.robot1.hp,self.hit_damage,"robot_1")
		self.robot1.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.FORWARD)
                print "robot_1 hit: front armor"

            return RefereeShootResponse(1,True)
        else:
            return RefereeShootResponse(3,True)
        
        
        
    def ShootCB_1(self,req):
        point = PointStamped()
        point.header.stamp = rospy.Time.now()
        point.header.frame_id = "referee_map"
        point.point.x= 8-req.x
        point.point.y= 5-req.y
        point.point.z= 0.1
        
        self.robot1.shootmark_pub.publish(point)
        if req.x < -4 and req.y < -4:
            return RefereeShootResponse(5,True)
        elif ((self.robot0.x - (8-req.x))**2) + ((self.robot0.y - (5-req.y))**2) < 0.25:
            
            self.robot0.hp -= self.hit_damage
            hit_angle =(math.atan2(self.robot1.y-self.robot0.y,self.robot1.x-self.robot0.x) - QuaternionToYaw(self.robot0.orientation)) % 6.283184
            if 0 <= hit_angle and hit_angle < 0.785398:
                #RefereeHitClient(0,self.robot0.hp,self.hit_damage,"robot_0")
		self.robot0.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.FORWARD)
                print "robot_0 hit: front armor"
            if 0.785398 <= hit_angle and hit_angle < 2.356194:
                #RefereeHitClient(1,self.robot0.hp,self.hit_damage,"robot_0")
		self.robot0.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.LEFT)
                print "robot_0 hit: left armor"
            if 2.356194 <= hit_angle and hit_angle < 3.92699:
                #RefereeHitClient(2,self.robot0.hp,self.hit_damage,"robot_0")
		self.robot0.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.BACKWARD)
                print "robot_0 hit: rear armor"
            if 3.92699 <= hit_angle and hit_angle < 5.497786:
                #RefereeHitClient(3,self.robot0.hp,self.hit_damage,"robot_0")
		self.robot0.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.RIGHT)
                print "robot_0 hit: right armor"
            if 5.497786 <= hit_angle and hit_angle < 6.3:
                #RefereeHitClient(0,self.robot0.hp,self.hit_damage,"robot_0")
		self.robot0.robot_damage_pub.publish(RobotDamage.ARMOR,RobotDamage.FORWARD)
                print "robot_0 hit: front armor"
            
            
            return RefereeShootResponse(1,True)
        else:
            return RefereeShootResponse(3,True)
        
    def TagCB_0(self,req):
        
        if ((self.robot0.x - 4)**2) + ((self.robot0.y - 4.5)**2) <0.25:
            self.robot0.is_reloading = True
            self.robot0.reload_time = rospy.Time.now()
            return RefereeTagResponse(1,True)
        else:
            return RefereeTagResponse(0,True)
        
    def TagCB_1(self,req):
        if ((self.robot1.x - 4)**2) + ((self.robot1.y - 0.5)**2) <0.25:
            self.robot1.is_reloading = True
            self.robot1.reload_time = rospy.Time.now()
            return RefereeTagResponse(1,True)
        else:
            return RefereeTagResponse(0,True)
        


if __name__ == '__main__':

	rospy.init_node('referee_test')
	rospy.Rate(0.3).sleep()
	ref_obj = Referee2vs2()
	rate = rospy.Rate(20)

	while not rospy.is_shutdown():
		ref_obj.Run()
		rate.sleep()
