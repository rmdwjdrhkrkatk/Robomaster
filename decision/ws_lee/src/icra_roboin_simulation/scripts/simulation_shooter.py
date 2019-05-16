#!/usr/bin/env python
import roslib
import sys
import rospy
from referee_modules.referee_interface import GetInfoClient, AmmoConsumeClient    #, ShootClient

if __name__ == '__main__':
	rospy.init_node('simulate_shooter')
	ns = rospy.get_namespace()
	rate = rospy.Rate(8)  ##Shooting rate in hz
	count = 0
	while not rospy.is_shutdown():
		try:	
			info = GetInfoClient(ns)
                        if info["is_enemy_1_detected"] and info["ammo"] > 0 and info["game_state"] == 4:
				if count % 2 == 1:
#					ShootClient(info["enemy_pose1"]["pose"]["position"]["x"],info["enemy_pose1"]["pose"]["position"]["y"],ns)
					count += 1
					AmmoConsumeClient(1,ns)
				else:
#					ShootClient(-5.0,-5.0,ns)
					count += 1
			rate.sleep()
		except:
			rate.sleep()
