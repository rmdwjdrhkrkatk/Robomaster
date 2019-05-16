#!/usr/bin/env python

from __future__ import print_function

import roslib; roslib.load_manifest('teleop_twist_keyboard')
import rospy
import numpy as np
from icra_roboin_decision_modules.roboin_behavior_service_module import SetBehaviorClient, SetGoalClient, GetInfoClient
from geometry_msgs.msg import Twist

import sys, select, termios, tty

robot_name = "robot_0"


msg = """
---------------------------
Moving around:
   q    w    e
   a    s    d
   z    x    c

    j       l

j: positive yaw
l: negative yaw

anything else : stop
o/p : increase/decrease max speeds by 10%
CTRL-C to quit
"""

moveBindings = {
        'q':(-0.7,0.7,0,0),
        'w':(0,1,0,0),
        'e':(0.7,0.7,0,0),

        'a':(-1,0,0,0),
        's':(0,0,0,0),
        'd':(1,0,0,0),

        'z':(-0.7,-0.7,0,0),
        'x':(0,-1,0,0),
        'c':(0.7,-0.7,0,0),

    }

speedBindings={
        'o':(1.1,0),
        'p':(0.9,0),

    }

yawBindings={
        'j':(0.3,0),
        'l':(-0.3,0),
    }

def getKey():
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key


def vels(speed,yaw):
    return "currently:\tspeed %s\tyaw %s " % (speed,yaw)

if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)
    
    rospy.init_node('robot_control')

    SetBehaviorClient(2,robot_name)

    speed = rospy.get_param("~speed", 0.5)
    robot_name = rospy.get_param("~robot_name", "robot_0")

    x = 0
    y = 0
    z = 0
    th = 0
    status = 0
    yaw = 0

    try:
        print(msg)
        print(vels(speed,yaw))
        while(1):
            key = getKey()
            if key in moveBindings.keys():
                x = moveBindings[key][0]
                y = moveBindings[key][1]
                z = moveBindings[key][2]
                th = moveBindings[key][3]
            elif key in speedBindings.keys():
                speed = speed * speedBindings[key][0]
	    elif key in yawBindings.keys():
		yaw += yawBindings[key][0]

                print(vels(speed,yaw))
                if (status == 14):
                    print(msg)
                status = (status + 1) % 15
            else:
                x = 0
                y = 0
                z = 0
                th = 0
                if (key == '\x03'):
                    break

	    goal_ = np.array([speed*x,speed*y,yaw,0,0,0,0])
	    SetGoalClient(goal_,robot_name)


    except Exception as e:
        print(e)

    finally:
        SetBehaviorClient(3,robot_name)
        goal_ = np.array([0,0,3,0,0,0,0])
        SetGoalClient(goal_,robot_name)
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
