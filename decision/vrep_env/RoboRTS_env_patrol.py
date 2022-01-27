import numpy as np
import math, time
from api import vrep
from time import sleep
import random

class RoboRTS:

    def __init__(self):
        
        self.clientID = vrep.simxStart('127.0.0.1', 19995, True, True, 5000, 5)     # Connect to V-REP

        while True:
            print('Connected to remote API server')
            if self.clientID != -1:
                break
            else:
                sleep(0.2)
        
        self.joint_handle_ally_1 = [
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_bl_wheel_joint', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_br_wheel_joint', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fl_wheel_joint', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fr_wheel_joint', vrep.simx_opmode_blocking)[1]
        ]

        self.projector_handle_1 = [
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_middle_projector_link_joint', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'middle_projector_link_to_top_projector_link_joint', vrep.simx_opmode_blocking)[1]
        ]

        self.joint_handle_ally_2 = [
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_bl_wheel_joint#1', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_br_wheel_joint#1', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fl_wheel_joint#1', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fr_wheel_joint#1', vrep.simx_opmode_blocking)[1]
        ]

        self.projector_handle_2 = [
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_middle_projector_link_joint#1', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'middle_projector_link_to_top_projector_link_joint#1', vrep.simx_opmode_blocking)[1]
        ]

        self.joint_handle_ally_3 = [
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_bl_wheel_joint#0', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_br_wheel_joint#0', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fl_wheel_joint#0', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fr_wheel_joint#0', vrep.simx_opmode_blocking)[1]
        ]

        self.joint_handle_ally_4 = [
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_bl_wheel_joint#2', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_br_wheel_joint#2', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fl_wheel_joint#2', vrep.simx_opmode_blocking)[1],
            vrep.simxGetObjectHandle(self.clientID, 'base_link_to_fr_wheel_joint#2', vrep.simx_opmode_blocking)[1]
        ]


        self.robot_handle = vrep.simxGetObjectHandle(self.clientID, 'RoboRTS_Ally_1', vrep.simx_opmode_blocking)[1]
        self.goal_handle = vrep.simxGetObjectHandle(self.clientID, 'goal', vrep.simx_opmode_blocking)[1]
        self.kinect_rgb_handle = vrep.simxGetObjectHandle(self.clientID, 'kinect_rgb', vrep.simx_opmode_blocking)[1]
        self.kinect_depth_handle = vrep.simxGetObjectHandle(self.clientID, 'kinect_depth', vrep.simx_opmode_blocking)[1]


    def streaming(self):
        
        vrep.simxGetStringSignal(self.clientID, 'measurement', vrep.simx_opmode_streaming)

        vrep.simxGetVisionSensorImage(self.clientID, self.kinect_depth_handle, 1, vrep.simx_opmode_buffer)[2]
        
        vrep.simxGetVisionSensorImage(self.clientID, self.kinect_rgb_handle, 1, vrep.simx_opmode_buffer)[2]
        
        self.rgb_value = vrep.simxReadVisionSensor(self.clientID, self.kinect_rgb_handle, vrep.simx_opmode_buffer)


    def getLidarData(self):
        e, lrf = vrep.simxGetStringSignal(self.clientID, 'measurement', vrep.simx_opmode_streaming)  
        self.lidar_data = np.array(vrep.simxUnpackFloats(lrf), dtype=float)
    
        return self.lidar_data


    def setMotorSpeeds1(self, action):
        a = 0.395 / 2       # the length in x-axis between the center point of vehicle and the center point of Mecanum wheel
        b = 0.415 / 2       # the length in y-axis between the center point of vehicle and the center point of Mecanum wheel

        speed_x = action[0]          # x-axis speed 
        speed_y = action[1]          # y-axis speed 
        w = action[2]                # angular velocity of vehicle

        bl_wheel_velocity = speed_y - speed_x - w * (a + b)
        br_wheel_velocity = speed_y + speed_x + w * (a + b)
        fl_wheel_velocity = speed_y + speed_x - w * (a + b)
        fr_wheel_velocity = speed_y - speed_x + w * (a + b)
        

        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_1[0], bl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_1[1], br_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_1[2], fl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_1[3], fr_wheel_velocity, vrep.simx_opmode_oneshot)
    
    def projectorcontrol1(self, action):
        vrep.simxSetJointTargetVelocity(self.clientID, self.projector_handle_1[0], action, vrep.simx_opmode_oneshot)

    def setMotorSpeeds2(self, action):
        a = 0.395 / 2       # the length in x-axis between the center point of vehicle and the center point of Mecanum wheel
        b = 0.415 / 2       # the length in y-axis between the center point of vehicle and the center point of Mecanum wheel

        speed_x = action[0]          # x-axis speed 
        speed_y = action[1]          # y-axis speed 
        w = action[2]                # angular velocity of vehicle
        
        bl_wheel_velocity = speed_y - speed_x - w * (a + b)
        br_wheel_velocity = speed_y + speed_x + w * (a + b)
        fl_wheel_velocity = speed_y + speed_x - w * (a + b)
        fr_wheel_velocity = speed_y - speed_x + w * (a + b)
        

        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_2[0], bl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_2[1], br_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_2[2], fl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_2[3], fr_wheel_velocity, vrep.simx_opmode_oneshot)        

    def projectorcontrol2(self, action):
        vrep.simxSetJointTargetVelocity(self.clientID, self.projector_handle_2[0], action, vrep.simx_opmode_oneshot)
 
    def setMotorSpeeds3(self, action):
        a = 0.395 / 2       # the length in x-axis between the center point of vehicle and the center point of Mecanum wheel
        b = 0.415 / 2       # the length in y-axis between the center point of vehicle and the center point of Mecanum wheel

        speed_x = action[0]          # x-axis speed 
        speed_y = action[1]          # y-axis speed 
        w = action[2]                # angular velocity of vehicle
        
        bl_wheel_velocity = speed_y - speed_x - w * (a + b)
        br_wheel_velocity = speed_y + speed_x + w * (a + b)
        fl_wheel_velocity = speed_y + speed_x - w * (a + b)
        fr_wheel_velocity = speed_y - speed_x + w * (a + b)
        

        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_3[0], bl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_3[1], br_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_3[2], fl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_3[3], fr_wheel_velocity, vrep.simx_opmode_oneshot)        
    
    def setMotorSpeeds4(self, action):
        a = 0.395 / 2       # the length in x-axis between the center point of vehicle and the center point of Mecanum wheel
        b = 0.415 / 2       # the length in y-axis between the center point of vehicle and the center point of Mecanum wheel

        speed_x = action[0]          # x-axis speed 
        speed_y = action[1]          # y-axis speed 
        w = action[2]                # angular velocity of vehicle
        
        bl_wheel_velocity = speed_y - speed_x - w * (a + b)
        br_wheel_velocity = speed_y + speed_x + w * (a + b)
        fl_wheel_velocity = speed_y + speed_x - w * (a + b)
        fr_wheel_velocity = speed_y - speed_x + w * (a + b)
        

        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_4[0], bl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_4[1], br_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_4[2], fl_wheel_velocity, vrep.simx_opmode_oneshot)
        vrep.simxSetJointTargetVelocity(self.clientID, self.joint_handle_ally_4[3], fr_wheel_velocity, vrep.simx_opmode_oneshot)        


    def isDanger(self):
        self.getLidarData()
        In_danger_left = 0
        In_danger_right = 0
        
        for i in range(450,540):
            theta = (180-i) * math.pi/180
            if self.lidar_data[i] < (3 / math.sin(theta)) and self.lidar_data[i] < 8:
                In_danger_left += 1
        
        for i in range(541,630):
            theta = (i-180) * math.pi/180
            if self.lidar_data[i] < (3 / math.sin(theta)) and self.lidar_data[i] < 8:
                In_danger_right += 1
        
        if In_danger_left and In_danger_right:
            if self.lidar_data[150] < self.lidar_data[210]:
                return [0.7, 6]
            if self.lidar_data[150] > self.lidar_data[210]:
                return [-0.7, 6]
        
        elif In_danger_left:
            return [0.7, 6]
        
        elif In_danger_right:
            return [-0.7, 6]
        
        else :
            return [0, 8]


    def Detection(self):
        if (self.rgb_value[2][0][8:9] < [0.92]) and (self.rgb_value[2][0][6:7] > [0.92]):
            vrep.simxSynchronousTrigger(self.clientID)
            print("FOUND THE ENEMY")                
            
            detection = True

            self.detection = detection
        
        return self.detection

    def collidable(self):
        self.getLidarData()
        collidable = False
        if np.min(self.lidar_data[160:200]) < 0.6:
            collidable = True
        if collidable:
            print('collide alert')
            if np.min(self.lidar_data[120:180]) < np.min(self.lidar_data[180:240]):
                self.avoid = [0.7, 6]
            elif np.min(self.lidar_data[120:180]) > np.min(self.lidar_data[180:240]):
                self.avoid = [-0.7, 6]
            else:
                self.avoid = [0,6]
            return True
        else :
            return False


    def step(self):
        # for i in range(40):
        #     self.setMotorSpeeds1([0.,0.,0.])
        #     self.setMotorSpeeds2([0.,0.,0.])
        
        #     self.setMotorSpeeds3([0.,0.,0.])
        #     self.setMotorSpeeds4([0.,0.,0.])

        #     self.projectorcontrol1(10.)
        #     self.projectorcontrol2(10.)

        #     vrep.simxSynchronousTrigger(self.clientID)
        for i in range(30):
            print('| robot1 : ', 'patrol' , ' | robot2 : ','patrol |')
            self.setMotorSpeeds1([0.,0.,5.])
            self.setMotorSpeeds2([0.,0.,-3.])
        
            self.setMotorSpeeds3([0.,0.1,1.])
            self.setMotorSpeeds4([0.,0.1,5.])

            self.projectorcontrol1(10.)
            self.projectorcontrol2(10.)

            vrep.simxSynchronousTrigger(self.clientID)
        print(1)
        for i in range(30):
            print('| robot1 : ', 'patrol' , ' | robot2 : ','patrol |')
            self.setMotorSpeeds1([0.,1.5,-5.])
            self.setMotorSpeeds2([0.,2.,3.])

            self.setMotorSpeeds3([0.,0.,5.])
            self.setMotorSpeeds4([0.,0.,-5.])

            self.projectorcontrol1(-10.)
            self.projectorcontrol2(-10.)

            vrep.simxSynchronousTrigger(self.clientID)

        for i in range(30):
            print('| robot1 : ', 'patrol' , ' | robot2 : ','patrol |')
            self.setMotorSpeeds1([0.,1.,9.])
            self.setMotorSpeeds2([0.,4.,0.])

            self.setMotorSpeeds3([0.,0.,-5.])
            self.setMotorSpeeds4([0.,0.,5.])

            vrep.simxSynchronousTrigger(self.clientID)
        for i in range(30):
            print('| robot1 : ', 'patrol' , ' | robot2 : ','patrol |')
            self.setMotorSpeeds1([0.,1,-3.])
            self.setMotorSpeeds2([0.,2.1,0])

            self.setMotorSpeeds3([0.,0.,5.])
            self.setMotorSpeeds4([0.,0.,-1.])
            vrep.simxSynchronousTrigger(self.clientID)
        for i in range(10):
            print('| robot1 : ', 'patrol' , ' | robot2 : ','patrol |')
            self.setMotorSpeeds1([0.,3.5,0])
            self.setMotorSpeeds2([0.,0.5,0.])

            self.setMotorSpeeds3([0.,0,-5.])
            self.setMotorSpeeds4([0.,0.,3.])
            vrep.simxSynchronousTrigger(self.clientID)
        for i in range(20):
            print('| robot1 : ', 'patrol' , ' | robot2 : ','patrol |')
            self.setMotorSpeeds1([0.,8.,0.])
            self.setMotorSpeeds2([0.,0.5,5.])
            

            self.setMotorSpeeds3([0.,0.,-8.])
            self.setMotorSpeeds4([0.,0.,3.])
            self.projectorcontrol1(-10.)
            self.projectorcontrol2(-10.)
            vrep.simxSynchronousTrigger(self.clientID)

        for i in range(20):
            print('| robot1 : ', 'fight' , ' | robot2 : ','fight |')
            self.setMotorSpeeds1([0.,0.,10.])
            self.setMotorSpeeds2([0.,0.,-5.])
            

            self.setMotorSpeeds3([0.,0.5,-8.])
            self.setMotorSpeeds4([0.,0.,3.])
            self.projectorcontrol1(-10.)
            self.projectorcontrol2(-10.)
            vrep.simxSynchronousTrigger(self.clientID)

        for i in range(20):
            print('| robot1 : ', 'fight' , ' | robot2 : ','fight |')
            self.setMotorSpeeds1([0.,0.,-5.])
            self.setMotorSpeeds2([0.,0.,10.])

            self.setMotorSpeeds3([0.,0,-5.])
            self.setMotorSpeeds4([0.,0.,3.])
        # for i in range(20):
        #     print('| robot1 : ', 'defense zone' , ' | robot2 : ','defense zone cover |')
        #     self.setMotorSpeeds1([0.,0.,0.])
        #     self.setMotorSpeeds2([0.,-1.,0.])

        #     self.setMotorSpeeds3([0.,0.,0.])
        #     self.setMotorSpeeds4([0.,0.,0.])

            vrep.simxSynchronousTrigger(self.clientID)
        
        
         
        return True


    def reset(self):
        vrep.simxSynchronous(self.clientID, True)
        print("ENV reset")
        vrep.simxStopSimulation(self.clientID, vrep.simx_opmode_blocking)
        print('sim stopped')
        time.sleep(0.5)
        self.streaming()

        vrep.simxSynchronousTrigger(self.clientID)
        vrep.simxSynchronousTrigger(self.clientID)
        vrep.simxSynchronousTrigger(self.clientID)


        vrep.simxStartSimulation(self.clientID, vrep.simx_opmode_blocking)
        print('sim started')
        time.sleep(0.2)

        vrep.simxSynchronousTrigger(self.clientID)
        vrep.simxSynchronousTrigger(self.clientID)
        vrep.simxSynchronousTrigger(self.clientID)
        vrep.simxSynchronousTrigger(self.clientID)
        time.sleep(1)

        self.getLidarData()

        
        return True

    def finishCheck(self):

        if self.detection == True:
            print("ENEMY DETECTED")
            return True

        else:
            return False









































# class Previous_version():

#     # if __name__=='__main__':
#     #     try:
#     #         vrep.simxFinish(-1) # just in case, close all opened connections
#     #     except:
#     #         pass

#     clientID = vrep.simxStart('127.0.0.1', 19997, True, True, 5000, 5) # Connect to V-REP

#     if clientID != -1:
#         print('Connected to remote API server')

#         # Enable the synchronous mode on the client:
#         vrep.simxSynchronous(clientID, True)
        
#         # ROBORTS_ALLY_1의 WHEEL JOINT
#         joint_handle_ally = [
#             vrep.simxGetObjectHandle(clientID, 'base_link_to_bl_wheel_joint', vrep.simx_opmode_streaming)[1],
#             vrep.simxGetObjectHandle(clientID, 'base_link_to_br_wheel_joint', vrep.simx_opmode_streaming)[1],
#             vrep.simxGetObjectHandle(clientID, 'base_link_to_fl_wheel_joint', vrep.simx_opmode_streaming)[1],
#             vrep.simxGetObjectHandle(clientID, 'base_link_to_fr_wheel_joint', vrep.simx_opmode_streaming)[1]
#         ]

#         # ROBORTS_ALLY_1의 PROJECTOR JOINT
#         projector_handle = [
#             vrep.simxGetObjectHandle(clientID, 'base_link_to_middle_projector_link_joint', vrep.simx_opmode_streaming)[1],
#             vrep.simxGetObjectHandle(clientID, 'middle_projector_link_to_top_projector_link_joint', vrep.simx_opmode_streaming)[1]
#         ]
        
#         kinect_rgb_handle = vrep.simxGetObjectHandle(clientID, 'kinect_rgb', vrep.simx_opmode_streaming)[1]
#         kinect_depth_handle = vrep.simxGetObjectHandle(clientID, 'kinect_depth', vrep.simx_opmode_streaming)[1]

#         red_and_blue_detected = False
#         red_detected = False
#         blue_detected = False

#         robot_handle = vrep.simxGetObjectHandle(clientID, 'RoboRTS_Ally_1', vrep.simx_opmode_streaming)[1]

#         # start the simulation:
#         vrep.simxStartSimulation(clientID,vrep.simx_opmode_streaming)

#         while True:
#             try:    
#                 robot_handle = vrep.simxGetObjectHandle(clientID, 'RoboRTS_Ally_1', vrep.simx_opmode_streaming)[1]

#                 while True:
#                     vrep.simxSynchronousTrigger(clientID)
#                     robot_position = vrep.simxGetObjectPosition(clientID, robot_handle, -1, vrep.simx_opmode_streaming)[1]
#                     robot_handle = vrep.simxGetObjectHandle(clientID, 'RoboRTS_Ally_1', vrep.simx_opmode_streaming)[1]
                    
#                     print(robot_position)
#                     e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_oneshot)

#                     # Bullet
#                     bullet_handle = vrep.simxGetObjectHandle(clientID, 'bullet', vrep.simx_opmode_streaming)[1]     

#                     # Control the rotation of the middle / top projector joint
#                     vrep.simxSetJointTargetVelocity(clientID, projector_handle[0], 0, vrep.simx_opmode_streaming)
#                     vrep.simxSetJointTargetVelocity(clientID, projector_handle[1], 0, vrep.simx_opmode_streaming)      
        
#                     # Control the velocity of the Wheel
#                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 2, vrep.simx_opmode_streaming)
#                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 2, vrep.simx_opmode_streaming)
#                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 2, vrep.simx_opmode_streaming)
#                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 2, vrep.simx_opmode_streaming)

#                     kinect_rgb_handle = vrep.simxGetObjectHandle(clientID, 'kinect_rgb', vrep.simx_opmode_buffer)[1]
#                     kinect_depth_handle = vrep.simxGetObjectHandle(clientID, 'kinect_depth', vrep.simx_opmode_buffer)[1]

#                     vision_handle = [kinect_rgb_handle, kinect_depth_handle]

#                     # k = vrep.simxGetVisionSensorDepthBuffer(clientID, kinect_depth_handle, vrep.simx_opmode_buffer)
                    
#                     image = vrep.simxGetVisionSensorImage(clientID, kinect_depth_handle, 1, vrep.simx_opmode_buffer)[2]
#                     image_1 = vrep.simxGetVisionSensorImage(clientID, kinect_rgb_handle, 1, vrep.simx_opmode_buffer)[2]
#                     rgb_value = vrep.simxReadVisionSensor(clientID, kinect_rgb_handle, vrep.simx_opmode_buffer)

                    
#                     enemy_armor_handle = vrep.simxGetObjectHandle(clientID, 'enemy_armor', vrep.simx_opmode_streaming)[1]
#                     enemy_armor_position = vrep.simxGetObjectPosition(clientID, enemy_armor_handle, -1, vrep.simx_opmode_buffer)[1]

#                     #print("R: {}, G: {}, B: {}".format(rgb_value[2][0][6:7], rgb_value[2][0][7:8], rgb_value[2][0][8:9]))
                    

#                     try:
#                         joint_handle_ally = [
#                                             vrep.simxGetObjectHandle(clientID, 'base_link_to_bl_wheel_joint', vrep.simx_opmode_streaming)[1],
#                                             vrep.simxGetObjectHandle(clientID, 'base_link_to_br_wheel_joint', vrep.simx_opmode_streaming)[1],
#                                             vrep.simxGetObjectHandle(clientID, 'base_link_to_fl_wheel_joint', vrep.simx_opmode_streaming)[1],
#                                             vrep.simxGetObjectHandle(clientID, 'base_link_to_fr_wheel_joint', vrep.simx_opmode_streaming)[1]
#                                         ]
#                         while True:
#                             vrep.simxSynchronousTrigger(clientID)
#                             e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)

#                             # Control the velocity of the Wheel
#                             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 1, vrep.simx_opmode_streaming)
#                             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 3, vrep.simx_opmode_streaming)
#                             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 1, vrep.simx_opmode_streaming)
#                             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)
                            
#                             for t in range(20):
#                                 vrep.simxSynchronousTrigger(clientID)
#                                 e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)

#                                 # Control the velocity of the Wheel
#                                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 3, vrep.simx_opmode_streaming)
#                                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 3, vrep.simx_opmode_streaming)
#                                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)

                        
#                                 while (rgb_value[2][0][8:9] < [0.92]) and (rgb_value[2][0][6:7] > [0.92]):
#                                     vrep.simxSynchronousTrigger(clientID)
#                                     e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                                     print("FOUND IT")

#                                     # Control the velocity of the Wheel
#                                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 0, vrep.simx_opmode_streaming)
#                                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 0, vrep.simx_opmode_streaming)
#                                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 0, vrep.simx_opmode_streaming)
#                                     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 0, vrep.simx_opmode_streaming)

#                                     red_detected == True
#                                     print("RED DETECTED")
#                         # while np.min(lrf) < 1.2:
#                         #     vrep.simxSynchronousTrigger(clientID)
                            
#                         #     e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #     print("[WARNING] GETTING CLOSER TO FRONT LEFT OBSTACLE!")
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 3, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 10, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 3, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 5, vrep.simx_opmode_streaming)

#                         #     #print(np.min(lrf[90:180]))
#                         #     while np.min(lrf[90:180]) < 0.5:
#                         #         vrep.simxSynchronousTrigger(clientID)
                            
#                         #         e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #         print("[WARNING] GETTING CLOSER TO FRONT LEFT OBSTACLE!")
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 1, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 1, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)


                        
#                         # while (np.min(lrf[180:270]) < np.min(lrf[90:180])) and (np.min(lrf[180:270]) < 2):
#                         #     vrep.simxSynchronousTrigger(clientID)
                            
#                         #     e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #     print("[WARNING] GETTING CLOSER TO FRONT LEFT OBSTACLE!")
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 1, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 1, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)

#                         #     while ((np.min(lrf[90:180])) < 1) and (0 < np.min(lrf[180:270]) < 1):
#                         #         vrep.simxSynchronousTrigger(clientID)
                                
#                         #         e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #         print("TURNING RIGHT")
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 6, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 8, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)

#                         #         while ((np.min(lrf[90:180])) > 0.5) and (np.min(lrf[180:270]) < 0.5):
#                         #             vrep.simxSynchronousTrigger(clientID)
                                    
#                         #             e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #             print("TURNING RIGHT RAPIDLY")
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 10, vrep.simx_opmode_streaming)
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 10, vrep.simx_opmode_streaming)
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)
                                    
#                         #             while np.min(lrf) < 0.3:
#                         #                 vrep.simxSynchronousTrigger(clientID)
                                        
#                         #                 e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #                 print("ABOUT TO COLLIDE")
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 0, vrep.simx_opmode_streaming)
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 0, vrep.simx_opmode_streaming)
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 0, vrep.simx_opmode_streaming)
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 0, vrep.simx_opmode_streaming)
                                
                        
#                         # while (np.min(lrf[180:270]) > np.min(lrf[90:180])) and (np.min(lrf[90:180]) < 1.5):
#                         #     vrep.simxSynchronousTrigger(clientID)
#                         #     e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #     print("[WARNING] GETTING CLOSER TO FRONT RIGHT OBSTACLE!")
#                         #     # print(np.min(lrf[90:180]))

#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 1, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 1, vrep.simx_opmode_streaming)
#                         #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)
                        
#                         #     #print(np.min(lrf[90:180]))
#                         #     while ((np.min(lrf[180:270])) > 1) and (0.54 < np.min(lrf[90:180]) < 1):
#                         #         vrep.simxSynchronousTrigger(clientID)
#                         #         e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #         print("TURNING LEFT")
#                         #         #print(np.min(lrf[180:270]))
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 8, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 6, vrep.simx_opmode_streaming)
#                         #         vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)
                                
#                         #         while ((np.min(lrf[180:270])) > 0.5) and (np.min(lrf[90:180]) < 0.5):
#                         #             vrep.simxSynchronousTrigger(clientID)
#                         #             e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #             print("TURNING LEFT RAPIDLY")
#                         #             #print(np.min(lrf[180:270]))
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 10, vrep.simx_opmode_streaming)
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 1, vrep.simx_opmode_streaming)
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 10, vrep.simx_opmode_streaming)
#                         #             vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 1, vrep.simx_opmode_streaming)

#                         #             while np.min(lrf) < 0.3:
#                         #                 vrep.simxSynchronousTrigger(clientID)
#                         #                 e, lrf = readLiDAR(clientID, 'measurement', vrep.simx_opmode_streaming)
#                         #                 print("ABOUT TO COLLIDE")
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 0, vrep.simx_opmode_streaming)
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 0, vrep.simx_opmode_streaming)
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 0, vrep.simx_opmode_streaming)
#                         #                 vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 0, vrep.simx_opmode_streaming)

#                     except:
#                         pass





#                     # while (rgb_value[2][0][6:7] > [0.92]) and (rgb_value[2][0][8:9] > [0.92]):
#                     #     red_and_blue_detected == True
#                     #     print("BLUE AND RED BOTH DETECTED")
#                     #     break
                    
#                     # while (rgb_value[2][0][8:9] > [0.92]) and (rgb_value[2][0][6:7] < [0.92]):
#                     #     blue_detected == True
#                     #     print("BLUE DETECTED")

#                     # while (rgb_value[2][0][8:9] < [0.92]) and (rgb_value[2][0][6:7] > [0.92]):
#                     #     vrep.simxSynchronousTrigger(clientID)
#                     #     joint_handle_ally = [
#                     #         vrep.simxGetObjectHandle(clientID, 'base_link_to_bl_wheel_joint', vrep.simx_opmode_streaming)[1],
#                     #         vrep.simxGetObjectHandle(clientID, 'base_link_to_br_wheel_joint', vrep.simx_opmode_streaming)[1],
#                     #         vrep.simxGetObjectHandle(clientID, 'base_link_to_fl_wheel_joint', vrep.simx_opmode_streaming)[1],
#                     #         vrep.simxGetObjectHandle(clientID, 'base_link_to_fr_wheel_joint', vrep.simx_opmode_streaming)[1]
#                     #     ]

#                     #     # Control the velocity of the Wheel
#                     #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[0], 5, vrep.simx_opmode_streaming)
#                     #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[1], 3, vrep.simx_opmode_streaming)
#                     #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[2], 6, vrep.simx_opmode_streaming)
#                     #     vrep.simxSetJointTargetVelocity(clientID, joint_handle_ally[3], 2, vrep.simx_opmode_streaming)

#                     #     red_detected == True
#                     #     print("RED DETECTED")


#             except KeyboardInterrupt:
#                 vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)
#                 print ("Crtl + C 사용하는 습관을 들이자")

#     else:
#         print ('Failed connecting to remote API server')
#     print ('Program ended')
