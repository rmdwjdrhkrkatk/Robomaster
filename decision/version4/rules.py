# -*- coding: utf-8 -*-
"""
@author: SHF_W
"""

import value_assign as va
import math
from collections import deque
import numpy as np
import itertools

class rules():    
    def __init__(self, size, team):
        self.pm = va.potentialField(size) # pm : potential mplot        
        self.pm.rectangular_assign(0, 8.000, 0, 5.000, 50, mode='abs')
        self.robot_radius = 0.38
        self.team = team
        self.inner_wall_tuple = ((1.200,2.200, 3.750,4.000), (1.400,1.600,1.400,2.400), (3.250,3.500,0,1.000),(3.500,4.500,2.375,2.625),(5.800,6.800,1.000,1.250),(6.350,6.600,2.600,3.600),(4.500,4.750,4.000,5.000))
        
        self.stance = 'aggressive'
        self.health = 2000
        self.ammo = 40
        self.pos = [0, 0]   
        self.pos_set = deque([], 16)  
        
    def out(self):
        return self.pm.out()
    
    def raw(self):
        return self.pm
        
    def plot(self):
        self.pm.plot()
        
    def init(self, pos):
        self.pm.rectangular_assign(0, 8, 0, 5, 50, mode='abs')        
        self.pos_set.appendleft(np.round(pos, 2))
    
    def isIn(self, pos1, pos2, team, zone):
        if team == 'blue':
            p = [[1.700,3.250,0.300], [4.000,0.600,0.100]]
        else:
            p = [[6.300,1.750,0.300], [4.000,4.400, 0.100]]
        
        if zone == 'bonus': 
            p = p[0]
        else: 
            p = p[1]
        
        x = p[0]
        y = p[1]
        d = p[2]
        
        result = False
        
        if pos1[0] > x-d and pos1[0] < x+d+1 and pos1[1] > y-d and pos1[1] < y+d+1:
            result = True
            
        if pos2[0] > x-d and pos2[0] < x+d+1 and pos2[1] > y-d and pos2[1] < y+d+1:
            result = True
            
        return result
            
        
    def set_stance(self, health, ammo, time):
        stance = 'guarded'
        
        if health > 1200 and ammo > 0:
            if ammo > 10:
                stance = 'aggressive'
            else:
                stance = 'aggressive_low_ammo'
        elif health < 200 or ammo == 0:
            stance = 'passive'                
        elif ammo > 10:
            stance = 'aggressive_low_health'
        else:
            stance = 'guarded'      
        
        return stance
    
    def wall_limit(self): 
        r = self.robot_radius
        self.pm.rectangular_assign(0, r, 0, 5.000, 0, mode='abs')
        self.pm.rectangular_assign(8.000-r, 8.000, 0, 5.000 , 0, mode='abs')
        self.pm.rectangular_assign(r, 8.000-r, 0, r, 0, mode='abs')
        self.pm.rectangular_assign(r, 8.000-r, 5.000-r, 5.000, 0, mode='abs')
        
        
                
        for item in self.inner_wall_tuple:
            x1, x2, y1, y2 = item
            r = self.robot_radius
            self.pm.circle_assign(x1, y1, r, 0, mode='abs')
            self.pm.circle_assign(x2, y1, r, 0, mode='abs')
            self.pm.circle_assign(x1, y2, r, 0, mode='abs')
            self.pm.circle_assign(x2, y2, r, 0, mode='abs')
            
            if x2-x1 > y2-y1:
                self.pm.rectangular_assign(x1, x2, y1-r, y2+r, 0, mode='abs')
            else:
                self.pm.rectangular_assign(x1-r, x2+r, y1, y2, 0, mode='abs')
            
            self.pm.rectangular_assign(x1,x2,y1,y2, -50, mode='abs')
                
                
    def bonus_zone(self, team_pos, buff_left, buff_zone_count, has_buff, value):
        p = [1.700,3.250,0.200]
        e = [6.300,1.750,0.200] 
        if self.team == 'red':
            p, e = e, p         
        
        if not has_buff:
            value = value * 1.2 
            
        if buff_zone_count > 0:
            # 버프 남은 시간이 5초 이하일 경우 매우 높은 value
            if buff_left < 5:
                self.pm.square_assign_gradient(p[0], p[1], p[2]*10, value/3,2)
                self.pm.square_assign(p[0], p[1], p[2]/2, value, mode='abs')
            # 버프 남은 시간이 5~10초일 경우 근처에서 value가 높지만 미리 점령하면 안되므로 점령 지점은 value가 낮음
            elif buff_left < 10:
                self.pm.square_assign_gradient(p[0], p[1], p[2]*10, value,2)               
                self.pm.square_assign(p[0], p[1], p[2]*2.5, 0, mode='abs')
            else:                
                self.pm.square_assign(p[0], p[1], p[2]*2.5, -10)
            # 버프를 활성화 시키면 안될 때에는 일단 막고 있음
            # 혹시 상대 버프를 일부러 활성화 시켜야할지도?
        self.pm.square_assign(e[0], e[1], e[2]*2.5, -30)
               
    def enemy_zone(self, stance, enemy_pos, percentage, distance, value):
        # 확실하게 적을 포착할 수록 작은 구역에 더 높은 가치, 적의 위치를 잘 모를 경우 작아짐 
        if percentage > 90:
            constant = 1.5
        elif percentage > 70:
            constant = 2.5
        elif percentage > 50:
            constant = 3
        else:
            constant = 4
        
        # aggressive stance일 경우 최적 거리 distance에서 가장 높은 값을 가지고, 거기서 멀어지면 값이 작아짐.
        if stance == 'aggressive':
            self.pm.circle_assign_gradient(enemy_pos[0], enemy_pos[1], distance*constant, value/constant, constant*2)
            self.pm.circle_assign_gradient(enemy_pos[0], enemy_pos[1], distance, -1*value/constant, constant)
            if percentage > 70:
                self.pm.circle_assign(enemy_pos[0], enemy_pos[1], self.robot_radius*2, 0, mode='abs')
                
        # passive stance일 경우 그냥 적에서 멀어질수록 높은 값을 가짐
        elif stance == 'passive':
           #circle_assign(enemy_pos[0], enemy_pos[1], int(distance*constant*4), value/constant)
           self.pm.circle_assign_gradient(enemy_pos[0], enemy_pos[1], distance*constant*2, -value/constant, constant)
           
    def enemy_overlap(self, e1, e2, value):
        if e1 == None or e2 == None:
            return
        
        p2p = self.pm.p2pRelation(e1, e2)     
        if p2p[0] > 8:
            return        
        bisector = min(math.atan2(self.robot_radius,p2p[0]/2), math.pi/7.5)
        constant = max(p2p[0], 1)
        p = 3      
        if p2p[0] > 3:
            rc = 1
        else:
            rc = 1.5       
        self.pm.sector_assign(e1[0], e1[1], 0, p2p[0]/math.cos(p*bisector)/2, p2p[1], 2*p*bisector*rc, -value/constant)
        self.pm.sector_assign(e2[0], e2[1], 0, p2p[0]/math.cos(p*bisector)/2, p2p[2], 2*p*bisector*rc, -value/constant)
    
    #(robot.stance, reload_count, robot.ammo, rz)     
    def reload_zone(self, stance, team_pos, reload_count, bullets, value):
        our = [4,0.6,0.1]
        enemy = [4,4.4,0.5]
        if self.team == 'red':
            our[1], enemy[1] = enemy[1], our[1]
        else:
            pass           
        # 적 재장전 존 패널티 : 2번 이상 들어가면 실격
        self.pm.square_assign(enemy[0], enemy[1], enemy[2], -50, mode='abs')
        
        if stance == 'passive' or stance == 'aggressive_low_ammo':
            value = value * 2

        if reload_count > 0 and bullets < 10:
            self.pm.square_assign(our[0], our[1], our[2], value)              
        
    def move_cost(self, stance, my_pos, value):
        x = my_pos[0]
        y = my_pos[1]
        self.pm.circle_assign_gradient(x, y, 10, -value, 10)
        
        
    def wall_cover(self, stance, enemy_pos, my_pos, value):
        gamma = math.pi/2
        
        if stance == 'passive' or stance == 'guarded':
            gamma = math.pi/6
            
        minimum = self.inner_wall_tuple[0]
        target = [[0,0],[0,0],[0,0],[0,0]]
        for item in self.inner_wall_tuple:           
            target[0] = [item[0], item[2]]
            target[1] = [item[0], item[3]]
            target[2] = [item[1], item[2]]
            target[3] = [item[1], item[3]]
            for item_sub in target:          
                a1 = self.pm.p2pRelation(item_sub, enemy_pos)[0]
                a2 = self.pm.p2pRelation(item_sub, my_pos)[0]
                b1 = self.pm.p2pRelation(minimum, enemy_pos)[0]
                b2 = self.pm.p2pRelation(minimum, my_pos)[0]
                temp = 4*a1*a1 + a2*a2
                dist = 4*b1*b1 + b2*b2
                if temp < dist:
                    minimum = item_sub
        r1 = self.pm.p2pRelation(minimum, enemy_pos)     
        r2 = r1[0] + 1
        constant = max(self.pm.p2pRelation(my_pos, enemy_pos)[0]/2,1)            
        self.pm.sector_assign(minimum[0], minimum[1], r1[0], r2, r1[2], gamma, value/constant)
        
    def first_occupy(self, my_pos):
        self.pm.circle_assign(my_pos[0], my_pos[1], self.robot_radius*3, 0, mode='abs')
    
    def robot_diff(self, my_pos):
        self.pm.circle_assign(my_pos[0], my_pos[1], .2, -20, mode = 'abs')
    
    def pos_view(self, my_pos):
        self.pm.square_assign(my_pos[0], my_pos[1], self.robot_radius, -10, mode='abs')
    
    def enemy_occupy(self, pos):
        self.pm.square_assign(pos[0], pos[1], self.robot_radius/2, -10)
        
    def enemy_random(self, value):
        self.pm.random_assign(value)
        
    def support_fire(self, stance, team_position, enemy_pos, value):
        if stance == 'aggresive' or stance == 'aggresive_low_health':
            self.pm.circle_assign(team_position[0], team_position[1], 1.5, 2*value, 3)            
            self.pm.circle_assign_gradient(team_position[0], team_position[1], 1.5, -value, 3)
            self.pm.cirle_assign(enemy_pos[0],enemy_pos[1], 1.5 , -value)
        elif stance == 'guarded' or stance == 'passive':
             if stance == 'guarded':
                value = value/2
             self.pm.circle_assign_gradient(enemy_pos[0], enemy_pos[1], 5, -value, 4)        
        
    def enemy_zone_diff(self, stance, enemy_pos, percentage, distance, value):
        # 확실하게 적을 포착할 수록 작은 구역에 더 높은 가치, 적의 위치를 잘 모를 경우 작아짐 
        #percent90일때 const2, percent 50일때 const4를 기준으로 선형 할당 
        constant = -0.05*percentage + 6.5 
        
        if self.team == 'blue':
            e_bonus = [6.300,1.750,0.500]
            e_reload = [4.000,4.400,0.500]
            if enemy_pos[0]-e_bonus[0] < 1.5 and enemy_pos[1]-e_bonus[1] < 1.5 : 
                value = value * 1.2
            if enemy_pos[0]-e_reload[0] < 1.5 and enemy_pos[1]-e_reload[1] < 1.5 : 
                value = value * 1.2
        else:
            e_bonus = [1.700,3.250,0.500]
            e_reload = [4.000,0.600,0.500]
            if enemy_pos[0]-e_bonus[0] < 1.5 and enemy_pos[1]-e_bonus[1] < 1.5 : 
                value = value * 1.2
            if enemy_pos[0]-e_reload[0] < 1.5 and enemy_pos[1]-e_reload[1] < 1.5 : 
                value = value * 1.2
        # aggressive stance일 경우 최적 거리 distance에서 가장 높은 값을 가지고, 거기서 멀어지면 값이 작아짐.
        if stance == 'aggressive':
            self.pm.circle_assign_gradient(enemy_pos[0], enemy_pos[1], distance*constant, value/constant, constant*2)
            self.pm.circle_assign_gradient(enemy_pos[0], enemy_pos[1], distance, -1*value/constant, constant)
            if percentage > 70:
                self.pm.circle_assign(enemy_pos[0], enemy_pos[1], self.robot_radius*2, 0, mode='abs')
                
        # passive stance일 경우 그냥 적에서 멀어질수록 높은 값을 가짐
        elif stance == 'passive':
           #circle_assign(enemy_pos[0], enemy_pos[1], int(distance*constant*4), value/constant)
           self.pm.circle_assign_gradient(enemy_pos[0], enemy_pos[1], distance*constant*2, -value/constant, constant)

    def current_zone(self, pos, n, value):
        last = min(n, 16)
        try:
            target = list(itertools.islice(self.pos_set, 0, last))
            value_scaled = value * (1-np.sum(np.var(target, axis=0)))
            self.pm.circle_assign(pos[0], pos[1], self.robot_radius, -value_scaled)
            return value_scaled
        except:
            pass