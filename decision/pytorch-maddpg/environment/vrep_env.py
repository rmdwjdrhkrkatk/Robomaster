from .env_modules import vrep
import numpy as np
import time

class Env():
    def __init__(self, port):
        self.clientID = vrep.simxStart('127.0.0.1', port, True, True, 5000, 5)
        self.ego_handles = {}
        self.risky_handles = {}
        self.rear_handles = {}
        self.lateral_handles = {}
        self.left0_handles = {}
        self.left1_handles = {}
        self.opposite_handles = {}
        self.right0_handles = {}
        self.collision_handles = {}
        self.lidar_handles = {}

        self.pos_ponus_ego = [1.7,3.25,0.0]
        self.pos_ponus_ego = [6.3,1.75,0.0]

        self.motor_list = ['rollingJoint_rl', 'rollingJoint_rr', 'rollingJoint_fl', 'rollingJoint_fr']
        self.collision_list = ['ego1','ego2','oppo1','oppo2']
        self.lidar_list = ['fastHokuyo','fastHokuyo#0','fastHokuyo#1','fastHokuyo#2']
        
        # Set handles
        self.ego_handle_1 = vrep.simxGetObjectHandle(self.clientID, 'ego1', vrep.simx_opmode_blocking)[1]
        self.ego_handle_2 = vrep.simxGetObjectHandle(self.clientID, 'ego2', vrep.simx_opmode_blocking)[1]
        self.oppo_handle_1 = vrep.simxGetObjectHandle(self.clientID, 'oppo1', vrep.simx_opmode_blocking)[1]
        self.oppo_handle_2 = vrep.simxGetObjectHandle(self.clientID, 'oppo2', vrep.simx_opmode_blocking)[1]


        for name in self.motor_list:
            self.ego_handles_1[name] = vrep.simxGetObjectHandle(self.clientID, 'ego1_' + name, vrep.simx_opmode_blocking)[1]
            self.ego_handles_2[name] = vrep.simxGetObjectHandle(self.clientID, 'ego2_' + name, vrep.simx_opmode_blocking)[1]
            self.oppo_handles_1[name] = vrep.simxGetObjectHandle(self.clientID, 'oppo1_' + name, vrep.simx_opmode_blocking)[1]
            self.oppo_handles_2[name] = vrep.simxGetObjectHandle(self.clientID, 'oppo2_' + name, vrep.simx_opmode_blocking)[1]
            

        for name in self.collision_list:
            self.collision_handles[name] = vrep.simxGetCollisionHandle(self.clientID, name, vrep.simx_opmode_blocking)[1]

        for name in self.lidar_list:
            self.lidar_handles[name] = vrep.simxGetObjectHandle(self.clientID, name, vrep.simx_opmode_blocking)[1]

        vrep.simxSynchronous(self.clientID, True)

        # Set some constants

    def get_lidar(self):
        lidar_array = []
        for name in self.lidar_list:
            buffer = vrep.simxGetVisionSensorDepthBuffer(self.clientID, self.lidar_handles[name], vrep.simx_opmode_blocking)[2]
            lidar_array += buffer
        return lidar_array

    def reset(self):
        vrep.simxSynchronous(self.clientID, True)
        time.sleep(0.5)
        vrep.simxStartSimulation(self.clientID, vrep.simx_opmode_oneshot)
        

        self.lidar_sequence = []

        vrep.simxSetObjectPosition(self.clientID, self.ego_handle_1, -1, (46.0, 2.0, 0.3677), vrep.simx_opmode_oneshot)
        vrep.simxSetObjectPosition(self.clientID, self.ego_handle_2, -1, (46.0, 2.0, 0.3677), vrep.simx_opmode_oneshot)
        vrep.simxSetObjectPosition(self.clientID, self.oppo_handle_1, -1, (46.0, 2.0, 0.3677), vrep.simx_opmode_oneshot)
        vrep.simxSetObjectPosition(self.clientID, self.oppo_handle_2, -1, (46.0, 2.0, 0.3677), vrep.simx_opmode_oneshot)

        pos_ego1 = vrep.simxGetObjectPosition(self.clientID, self.ego_handle_1, -1, vrep.simx_opmode_blocking)[1]
        pos_ego2 = vrep.simxGetObjectPosition(self.clientID, self.ego_handle_2, -1, vrep.simx_opmode_blocking)[1]
        pos_oppo1 = vrep.simxGetObjectPosition(self.clientID, self.oppo_handle_1, -1, vrep.simx_opmode_blocking)[1]
        pos_oppo2 = vrep.simxGetObjectPosition(self.clientID, self.oppo_handle_2, -1, vrep.simx_opmode_blocking)[1]

        vrep.simxPauseCommunication(self.clientID, 1)
        self.set_action('ego1', [0.0, 0.0, 0.0])
        self.set_action('ego2', [0.0, 0.0, 0.0])
        self.set_action('oppo1', [0.0, 0.0, 0.0])
        self.set_action('oppo2', [0.0, 0.0, 0.0])
        vrep.simxPauseCommunication(self.clientID, 0)
        vrep.simxSynchronousTrigger(self.clientID)
            
        for i in range(4):
            vrep.simxSynchronousTrigger(self.clientID)
            self.lidar_sequence += self.get_lidar()
        # 35 steps of turning and then straight

        # target_position = vrep.simxGetObjectPosition(self.clientID, self.target_handle ,self.ego_handle, vrep.simx_opmode_blocking)[1]
        # target_x = target_position[1]
        # target_y = target_position[2]
        # dist_target = (target_x**2 + target_y**2)**0.5
        # target_state = [target_x/30.0, target_y/30.0]
        state = self.lidar_sequence + [-0.4, 0.0]# + target_state
        velocity = vrep.simxGetObjectVelocity(self.clientID, self.ego_handle, vrep.simx_opmode_blocking)[1]
        speed = (velocity[0]**2 + velocity[1]**2 + velocity[2]**2)**0.5
        # self.prev_distance = dist_target
        # self.prev_velocity = velocity
        self.prev_speed = speed
        return state

    def step(self, action, timestep):
        done = False

        vrep.simxPauseCommunication(self.clientID, 1)
        self.set_action('ego', action)
        if self.scenario_num == 2 and timestep == 31:
            self.set_action('risky', [0.5, 0.0])
        vrep.simxPauseCommunication(self.clientID, 0)
        vrep.simxSynchronousTrigger(self.clientID)

        self.lidar_sequence = self.lidar_sequence[96:] + self.get_lidar()
        
        # target_position = vrep.simxGetObjectPosition(self.clientID, self.target_handle ,self.ego_handle, vrep.simx_opmode_blocking)[1]
        # target_x = target_position[1]
        # target_y = target_position[2]
        # dist_target = (target_x**2 + target_y**2)**0.5
        # target_state = [target_x/30.0, target_y/30.0]
        state1 = self.lidar_sequence + action.tolist()# + target_state

        velocity = vrep.simxGetObjectVelocity(self.clientID, self.ego_handle, vrep.simx_opmode_blocking)[1]
        speed = (velocity[0]**2 + velocity[1]**2 + velocity[2]**2)**0.5
        
        # Get collision area
        collision = {}
        for name in self.collision_list:
            collision[name] = vrep.simxReadCollision(self.clientID, self.collision_handles[name], vrep.simx_opmode_blocking)[1]
        
        # Get alpha
        if collision['rear'] or collision['far'] or collision['near']:
            if collision['rear']:
                alpha = 1.991
            if collision['far']:
                alpha = 2.038
            if collision['near']:
                alpha = 2.698
            
            vrep.simxSynchronousTrigger(self.clientID)
            vrep.simxSynchronousTrigger(self.clientID)
            velocity1 = vrep.simxGetObjectVelocity(self.clientID, self.ego_handle, vrep.simx_opmode_blocking)[1]
            speed1 = (velocity1[0]**2 + velocity1[1]**2 + velocity1[2]**2)**0.5
            
            deltaV = speed1 - self.prev_speed
            collision_reward = -np.exp(2.011*10**(-7)*0.5*836.0*deltaV**2 + alpha)
            done = True
        elif timestep > 50:
            done = True
            collision_reward = 0.0
        else:
            collision_reward = 0.0
        
        # target_reward = self.prev_distance - dist_target
        reward = collision_reward# + target_reward

        # print('collision:',collision_reward, 'target:',target_reward)
        
        if done == True:
            vrep.simxPauseCommunication(self.clientID, 1)
            self.set_action('ego', [-1.0, 0.0])
            self.set_action('risky', [-1.0, 0.0])
            self.set_action('rear', [-1.0, 0.0])
            self.set_action('opposite', [-1.0, 0.0])
            vrep.simxPauseCommunication(self.clientID, 0)
            vrep.simxSynchronousTrigger(self.clientID)
            vrep.simxStopSimulation(self.clientID, vrep.simx_opmode_blocking)

        # Update prev_distance, velocity
        # self.prev_velocity = velocity
        self.prev_speed = speed
        # self.prev_distance = dist_target
        return state1, reward, done

    # Send action signal to simulator
    def set_action(self, type, action):
        d = 0.755
        l = 2.5772
        desiredSpeed, desiredSteeringAngle = action
        desiredSpeed = 25. * desiredSpeed + 25
        desiredSteeringAngle = 0.785 * desiredSteeringAngle

        if desiredSteeringAngle != 0.:
            steeringAngleLeft = np.arctan(l / (-d + l / np.tan(desiredSteeringAngle)))
            steeringAngleRight = np.arctan(l / (d + l / np.tan(desiredSteeringAngle)))
        else:
            steeringAngleLeft = 0.
            steeringAngleRight = 0.
        
        if type == 'ego':
            vrep.simxSetJointTargetVelocity(self.clientID, self.ego_handles['motorLeft'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetVelocity(self.clientID, self.ego_handles['motorRight'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.ego_handles['steeringLeft'], steeringAngleLeft, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.ego_handles['steeringRight'], steeringAngleRight, vrep.simx_opmode_oneshot)
        elif type == 'risky':
            vrep.simxSetJointTargetVelocity(self.clientID, self.risky_handles['motorLeft'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetVelocity(self.clientID, self.risky_handles['motorRight'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.risky_handles['steeringLeft'], steeringAngleLeft, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.risky_handles['steeringRight'], steeringAngleRight, vrep.simx_opmode_oneshot)
        elif type == 'rear':
            vrep.simxSetJointTargetVelocity(self.clientID, self.rear_handles['motorLeft'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetVelocity(self.clientID, self.rear_handles['motorRight'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.rear_handles['steeringLeft'], steeringAngleLeft, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.rear_handles['steeringRight'], steeringAngleRight, vrep.simx_opmode_oneshot)
        elif type == 'opposite':
            vrep.simxSetJointTargetVelocity(self.clientID, self.opposite_handles['motorLeft'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetVelocity(self.clientID, self.opposite_handles['motorRight'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.opposite_handles['steeringLeft'], steeringAngleLeft, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.opposite_handles['steeringRight'], steeringAngleRight, vrep.simx_opmode_oneshot)
        elif type == 'lateral':
            vrep.simxSetJointTargetVelocity(self.clientID, self.lateral_handles['motorLeft'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetVelocity(self.clientID, self.lateral_handles['motorRight'], desiredSpeed, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.lateral_handles['steeringLeft'], steeringAngleLeft, vrep.simx_opmode_oneshot)
            vrep.simxSetJointTargetPosition(self.clientID, self.lateral_handles['steeringRight'], steeringAngleRight, vrep.simx_opmode_oneshot)


    def close(self):
        for name in self.collision_list:
            vrep.simxReadCollision(self.clientID, self.collision_handles[name], vrep.simx_opmode_discontinue)
        vrep.simxGetObjectOrientation(self.clientID, self.ego_handle, self.risky_handle, vrep.simx_opmode_discontinue)
        vrep.simxGetObjectPosition(self.clientID, self.ego_handle, -1, vrep.simx_opmode_discontinue)
        for name in self.lidar_list:
            vrep.simxGetVisionSensorDepthBuffer(self.clientID, self.lidar_handles[name], vrep.simx_opmode_discontinue)
        vrep.simxStopSimulation(self.clientID, vrep.simx_opmode_blocking)
        time.sleep(0.5)        