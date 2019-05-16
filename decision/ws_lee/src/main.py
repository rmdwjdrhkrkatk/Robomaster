# -*- coding: utf-8 -*-
"""
Created on Tue Apr 16 22:31:28 2019

@author: SHF_W
"""

#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import rules
import time
#import cv2

import rospy
import roslib
from icra_roboin_decision_modules.roboin_behavior_service_module import SetBehaviorClient, SetGoalClient
from icra_roboin_decision_modules.roboin_behavior_service_module import GetInfoClient
from geometry_msgs.msg import PoseWithCovarianceStamped



rospy.init_node('decision_test')



def my_pose(pose):
    global xxx
    global yyy
    xxx = pose.pose.pose.position.x
    yyy = pose.pose.pose.position.y
    

 
def initialize():    
    global startTime
    startTime = time.time()   
    
    #SetBehaviorClient(behav_,"robot_0")

def now_time(start):    
    return time.time() - start

attack_hold_value = 10
attack_hold_degre = 3 # 초당 value 10씩 감소, 최대 3번, 한 자리에서 계속 공격하지 않게 하는 값. value가 
occupy_hold_value = 50


if __name__ == '__main__':
    
    
    team = 'blue'
    robot1 = rules.rules([100,160], team)
    
    '''
    ==================================================
    Get Value from Black Board
    ==================================================
    '''
    initialize()
    #stance = 'passive'
    stance = 'aggressive'
    
    my_position = [.500, 4.500]
    
    e1 = [7.500, .500]
    e2 = [.500, .500]
        
    buff_time = 0
    ammo_left = False
    behav = 4
    value = attack_hold_value + robot1.raw().getValue(my_position)
    xxx=my_position[0]
    yyy=my_position[1]
    print('start')
    while now_time(startTime) < 25:
        # blackboard
	print("shibal")
        state = GetInfoClient("robot_0",1)
        #state_1 = GetInfoClient("robot_1",1)
        print(state)
        #print(state_1)
        #state = GetInfoClient()
        #print('======================================================')
        #my_position = [state['my_pose']['pose']['position']['x'], state['my_pose']['pose']['position']['y']]
	
        rospy.Subscriber("/robot_0/amcl_pose",PoseWithCovarianceStamped, my_pose)
        rospy.Subscriber("/robot_1/amcl_pose",PoseWithCovarianceStamped, my_pose)
        my_position = [xxx, yyy]    
       
        f1 = now_time(startTime)
        #e1 = [ state["enemy_pose1"]['pose']['position']['x'], state("robot_0",1)["enemy_pose1"]['pose']['position']['y']]
        
        robot1.init()
        robot1.bonus_zone(buff_time, 2, False, 200)
        robot1.enemy_zone(stance, e1, 90,  1.00, 50)   
        #robot1.enemy_zone(stance, e2, 90,  .700, 50)   
        
        robot1.reload_zone(stance, now_time(startTime), ammo_left, 50, 100)    
        robot1.move_cost(stance, my_position, 10)
        #robot1.enemy_overlap(e1, e2, 50)
        
        robot1.wall_limit()
        
        if now_time(startTime) > 15:
            ammo_left = True
        
        '''
        ==================================================
        test variable change - black board information
        ==================================================
        '''
        flags = np.zeros([10])
        if now_time(startTime) >= 5 and now_time(startTime) < 35:
            buff_time = 35-now_time(startTime)
        if now_time(startTime) >= 5:
            buff_time = 65-now_time(startTime)
                
        b = robot1.raw().getPoint()       # [value, [x, y]]  
        c = robot1.raw().getValue(my_position)
        #print('my_pos : ', c, my_position, 'Max :' , b)
        pt = now_time(startTime) - f1    
        
        value = attack_hold_value + robot1.raw().getValue(my_position)

        behav = 4
        
        x = b[1][0]
        y = b[1][1]
        
        if value < b[0]:
            behav = 2
            
            goal = np.array([x,y,0,0,0,0,0])   
            SetGoalClient(goal, "robot_0")   
            SetBehaviorClient(behav,"robot_0")

            goal_1 = np.array([x,y,0,0,0,0,0])
            SetGoalClient(goal_1, "robot_1")
            SetBehaviorClient(behav,"robot_1")
            

            goal_2 = np.array([x,y,0,0,0,0,0])
            SetGoalClient(goal_2, "robot_2")
            SetBehaviorClient(behav,"robot_2")

            goal_3 = np.array([x,y,0,0,0,0,0])
            SetGoalClient(goal_3, "robot_3")
            SetBehaviorClient(behav,"robot_3")
                
        else:
            behav = 1
            SetGoalClient(goal,"robot_0") 
            SetBehaviorClient(behav,"robot_0")
            
            goal_ = np.array([5,3,1,0,0,0,0])
                
            
       
        print('Time:', now_time(startTime), ammo_left)
        print(my_position)
        print(x,y)
        print(behav, goal, '|', value, 'max:',b)
        print('Process Time : ', pt , 'FPS:', int(10/pt)/10.0 )
        
       # robot1.plot()
        plt.pause(1)
        
        

