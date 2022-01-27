import numpy as np

class Decision_selection_class():
    def __init__(self):
        # Key parameters and values
        self.v = 5.
        self.robot_velocity = 2                                      # Empirical Threshold Velocity
        self.threshold_hp = [250, 1250, 2000]                        # Empirical Threshold HP
        # self.threshold_distance = [1, 2]                             # Empirical Threshold Distance
        self.threshold_bullet = [20,10]                                 # Empirical Threshold Number of bullets



        self.time = 0 # Get time
        self.distance_to_defense_zone_1 = 10.
        self.distance_to_defense_zone_2 = 12.

        self.distance_to_reload_zone_1 = 10.
        self.distance_to_reload_zone_2 = 10.

        self.robot_hp = [2000, 2000]                     # Robot 1, 2 HP
        self.robot_bullet = [40, 40]         # Robot 1, 2 Number of Bullets
        self.robot_buff = False
        self.enemy_detection = [True, True]
        self.detect_distance = 0.
        self.detect_distance_threshold = 1.5
        self.defense_activation = []
        self.defense_zone = False

        # self.is_possible_to_defense_zone = [True, True]              # Boolean for path planning to the defense zone
        self.robot_behavior = [
            'fight', #
            'defense', #
            ['close_patrol', 'normal_patrol'], #
            ['reload_cover', 'reload'], #
            # 'hide', 
            ['slow_escape', 'fast_escape'], #
            'sentry' #'sentry' , hold(rotate and sentry), buff
            ]
        
        self.defense_time_threshold = 5.
        self.time_to_defense_zone = [self.distance_to_defense_zone_1 / self.v, self.distance_to_defense_zone_2 / self.v]
        self.time_to_reload_zone = [self.distance_to_reload_zone_1 / self.v, self.distance_to_reload_zone_2 / self.v]

    def F_decision_selection(self,state1,state2,real_time):
        self.time = real_time
        self.distance_to_defense_zone = 10.
        self.distance_to_reload_zone = 10.
        self.robot_hp = [state1['my_health'], state2['my_health']]     # Robot 1, 2 HP
        self.robot_bullet = [state1['ammo'], state2['ammo']]         # Robot 1, 2 Number of Bullets
        self.robot_buff = [state1['has_buff'], state2['has_buff']]
        self.enemy_detection = np.array([[state1['is_enemy_1_detected'],state1['is_enemy_2_detected']], 
                                [state2['is_enemy_1_detected'],state2['is_enemy_2_detected']]])
        self.detect_distance = [state1['enemy_distance'],state2['enemy_distance']]
        self.defense_activation = [state1['has_buff'],state2['has_buff']]

        if (self.time % 60. < 5.):
            self.defense_zone = True

        if any(self.robot_buff) == True:
            self.defense_zone = False

        # 어차피 HP가 회복되는 경우는 존재하지 않으므로, HP에 따른 시간적인 흐름으로 분류함
        """----------------------------------------------------------------------------------------------------------------------"""
        """-----------------------------------------------1st HP region Start----------------------------------------------------"""
        """----------------------------------------------------------------------------------------------------------------------"""
        if min(self.robot_hp) > self.threshold_hp[2]:                                  # HP 4단계 중 가장 안전한 경우
            print(1)
            if min(self.robot_bullet) > self.threshold_bullet[0]:
                
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    print(3)
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[0]                # Fight
                        robot_2_behavior = self.robot_behavior[0]                # Fight
                        print(4)
                    else:
                        if (self.defense_zone == True):
                            print(5)
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[1]            # occupy defense zone
                                robot_2_behavior = self.robot_behavior[1]            # occupy defense zone
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                                robot_2_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                        else:
                            print(6)
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[-1]           # sentinental mode
                                robot_2_behavior = self.robot_behavior[-1]           # sentinental mode
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                                robot_2_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                                       
                else:
                    print(7)
                    if (self.defense_zone == True):
                        print(8)
                        if (any(self.robot_buff) == False):
                            robot_1_behavior = self.robot_behavior[1]            # occupy defense zone
                            robot_2_behavior = self.robot_behavior[1]            # occupy defense zone
                        elif any(self.robot_buff) == True:
                            robot_1_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 Patrol 하자- STEP 2
                            robot_2_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 Patrol 하자- STEP 2 # aggressive
                    else:
                        print(9)
                        if (any(self.robot_buff) == False):
                            print(10)
                            robot_1_behavior = self.robot_behavior[-1]           # sentinental mode
                            robot_2_behavior = self.robot_behavior[-1]           # sentinental mode
                        elif any(self.robot_buff) == True:
                            robot_1_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                            robot_2_behavior = self.robot_behavior[2][0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자

            elif (self.robot_bullet[0] > self.robot_bullet[1]) and (min(self.robot_bullet) > 0):
                robot_1_behavior = self.robot_behavior[3][0]
                robot_2_behavior = self.robot_behavior[3][1]
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[0]                # Fight
                        robot_2_behavior = self.robot_behavior[0]                # Fight
                    else:
                        robot_1_behavior = self.robot_behavior[3][0]             # Reload
                        robot_2_behavior = self.robot_behavior[3][1]             # Reload
                else:
                    robot_1_behavior = self.robot_behavior[3][0]                 # keep on going
                    robot_2_behavior = self.robot_behavior[3][1]                 # keep on going

            elif (self.robot_bullet[0] < self.robot_bullet[1]) and (min(self.robot_bullet) > 0):
                print(2)
                robot_1_behavior = self.robot_behavior[3][1]
                robot_2_behavior = self.robot_behavior[3][0]
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[0]                # Fight
                        robot_2_behavior = self.robot_behavior[0]                # Fight
                    else:
                        robot_1_behavior = self.robot_behavior[3][1]             # Reload
                        robot_2_behavior = self.robot_behavior[3][0]             # Reload
                else:
                    robot_1_behavior = self.robot_behavior[3][1]                 # keep on going
                    robot_2_behavior = self.robot_behavior[3][0]                 # keep on going
            
            elif (self.robot_bullet[0] == self.robot_bullet[1]) and (min(self.robot_bullet) > 0):
                if self.time_to_reload_zone[0] >= self.time_to_reload_zone[1]: 
                    robot_1_behavior = self.robot_behavior[3][1]
                    robot_2_behavior = self.robot_behavior[3][0]
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[0]            # Fight
                            robot_2_behavior = self.robot_behavior[0]            # Fight
                        else:
                            robot_1_behavior = self.robot_behavior[3][1]         # keep on going
                            robot_2_behavior = self.robot_behavior[3][0]         # keep on going
                else:
                    robot_1_behavior = self.robot_behavior[3][0]                     
                    robot_2_behavior = self.robot_behavior[3][1]                     
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[0]            # Fight
                            robot_2_behavior = self.robot_behavior[0]            # Fight
                        else:
                            robot_1_behavior = self.robot_behavior[3][0]         # keep on going
                            robot_2_behavior = self.robot_behavior[3][1]         # keep on going
            
            # 둘다 총알이 없을 때, 이건 정말 심각한 상황이다
            else:                                                               # 무조건 Reload가 급선무다 HP는 많으니 몸으로 버텨라
                if self.time_to_reload_zone[0] >= self.time_to_reload_zone[1]: 
                    robot_1_behavior = self.robot_behavior[3][1]
                    robot_2_behavior = self.robot_behavior[3][0]
                else:
                    robot_1_behavior = self.robot_behavior[3][0]
                    robot_2_behavior = self.robot_behavior[3][1]

            if robot_1_behavior == 'fight':
                return [['fight', ['fight','fight']],
                        ['fight', ['fight','fight']],
                        ['fight', ['fight','fight']]
                        ]
            elif robot_1_behavior == 'defense':
                return [['defense', ['defense','defense']],
                        ['fight', ['fight','fight']],
                        ['patrol', ['close_patrol','close_patrol']]
                        ]
            elif robot_1_behavior == 'close_patrol':
                return [['patrol', ['close_patrol','close_patrol']],
                        ['fight', ['fight','fight']],
                        ['patrol', ['close_patrol','close_patrol']]
                        ]
            elif robot_1_behavior == 'normal_patrol':
                return [['patrol', ['normal_patrol','normal_patrol']],
                        ['fight', ['fight','fight']],
                        ['patrol', ['normal_patrol','normal_patrol']]
                        ]
            elif robot_1_behavior == 'reload':
                return [['reload', ['reload','reload_cover']],
                        ['patrol', ['normal_patrol','normal_patrol']],
                        ['reload', ['reload','reload_cover']]
                        ]
            elif robot_1_behavior == 'reload_cover':
                return [['reload', ['reload_cover','reload']],
                        ['patrol', ['normal_patrol','normal_patrol']],
                        ['reload', ['reload_cover','reload']]
                        ]
            elif robot_1_behavior == 'slow_escape':
                return [['escape', ['slow_escape','slow_escape']],
                        ['escape', ['slow_escape','slow_escape']],
                        ['escape', ['slow_escape','slow_escape']]
                        ]
            elif robot_1_behavior == 'fast_escape':
                return [['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']]
                        ]
            elif robot_1_behavior == 'sentry':
                return [['sentry', ['sentry','sentry']],
                        ['sentry', ['sentry','fight']],
                        ['sentry', ['sentry','sentry']]
                        ]

        """---------------------------------------------------------------------------------------------------------------------"""
        """---------------------------------------------1st HP region Complete--------------------------------------------------"""
        """---------------------------------------------------------------------------------------------------------------------"""
        ############################################################################################################################
        """----------------------------------------------------------------------------------------------------------------------"""
        """----------------------------------------------2nd HP region Start-----------------------------------------------------"""
        """----------------------------------------------------------------------------------------------------------------------"""

        if (self.threshold_hp[1] < min(self.robot_hp)) and (min(self.robot_hp) <= self.threshold_hp[2]):                          # HP 4단계 중 2번째로 안전한 경우
            if min(self.robot_bullet) > self.threshold_bullet[0]:
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[count]                # Fight
                        robot_2_behavior = self.robot_behavior[count]                # Fight
                    else:
                        if (self.defense_zone == True):
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[1]            # occupy defense zone
                                robot_2_behavior = self.robot_behavior[1]            # occupy defense zone
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                                robot_2_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                        else:
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[-1]           # sentinental mode  # if hp is low, have to hide or slow escape(section 3 or 4)
                                robot_2_behavior = self.robot_behavior[-1]           # sentinental mode
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                                robot_2_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                                                                                 # HP Part 1과 다른 부분(2) -> 적극적 Patrol 삭제
                else:
                    if (self.defense_zone == True):
                        if (any(self.robot_buff) == False):
                            robot_1_behavior = self.robot_behavior[1]            # occupy defense zone
                            robot_2_behavior = self.robot_behavior[1]            # occupy defense zone
                        elif any(self.robot_buff) == True:
                            robot_1_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 Patrol 하자- STEP 2
                            robot_2_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 Patrol 하자- STEP 2
                    else:
                        if (any(self.robot_buff) == False):
                            robot_1_behavior = self.robot_behavior[-1]           # sentinental mode
                            robot_2_behavior = self.robot_behavior[-1]           # sentinental mode
                        elif any(self.robot_buff) == True:
                            robot_1_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                            robot_2_behavior = self.robot_behavior[2][1]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자

            elif (self.robot_bullet[0] > self.robot_bullet[1]) and (min(self.robot_bullet) > 0):
                robot_1_behavior = self.robot_behavior[3][0]
                robot_2_behavior = self.robot_behavior[3][1]
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[0]            # Fight
                        robot_2_behavior = self.robot_behavior[0]            # Fight
                    else:
                        robot_1_behavior = self.robot_behavior[3][0]         # Reload
                        robot_2_behavior = self.robot_behavior[3][1]         # Reload
                else:
                    robot_1_behavior = self.robot_behavior[3][0]             # keep on going
                    robot_2_behavior = self.robot_behavior[3][1]             # keep on going

            elif (self.robot_bullet[0] < self.robot_bullet[1]) and (min(self.robot_bullet) > 0):
                robot_1_behavior = self.robot_behavior[3][1]
                robot_2_behavior = self.robot_behavior[3][0]
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[0]                # Fight
                        robot_2_behavior = self.robot_behavior[0]                # Fight
                    else:
                        robot_1_behavior = self.robot_behavior[count][1]             # Reload
                        robot_2_behavior = self.robot_behavior[count][0]             # Reload
                else:
                    robot_1_behavior = self.robot_behavior[3][1]                 # keep on going
                    robot_2_behavior = self.robot_behavior[3][0]                 # keep on going
            
            elif (self.robot_bullet[0] == self.robot_bullet[1]) and (min(self.robot_bullet) > 0):
                if self.time_to_reload_zone[0] >= self.time_to_reload_zone[1]: 
                    robot_1_behavior = self.robot_behavior[3][1]
                    robot_2_behavior = self.robot_behavior[3][0]
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[0]            # Fight
                            robot_2_behavior = self.robot_behavior[0]            # Fight
                        else:
                            robot_1_behavior = self.robot_behavior[3][1]         # keep on going
                            robot_2_behavior = self.robot_behavior[3][0]         # keep on going
                else:
                    robot_1_behavior = self.robot_behavior[3][0]                     
                    robot_2_behavior = self.robot_behavior[3][1]                     
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[0]            # Fight
                            robot_2_behavior = self.robot_behavior[0]            # Fight
                        else:
                            robot_1_behavior = self.robot_behavior[3][1]         # keep on going
                            robot_2_behavior = self.robot_behavior[3][0]         # keep on going
            
            # 둘다 총알이 없을 때, 이건 정말 심각한 상황이다
            else:                                                           # Reload가 급선무다 아직까지는 몸으로 버텨라
                if self.time_to_reload_zone[0] >= self.time_to_reload_zone[1]: 
                    robot_1_behavior = self.robot_behavior[3][1]
                    robot_2_behavior = self.robot_behavior[3][0]
                else:
                    robot_1_behavior = self.robot_behavior[3][0]
                    robot_2_behavior = self.robot_behavior[3][1]  

            if robot_1_behavior == 'fight':
                return [['fight', ['fight','fight']],
                        ['fight', ['fight','fight']],
                        ['fight', ['fight','fight']]
                        ]
            elif robot_1_behavior == 'defense':
                return [['defense', ['defense','defense']],
                        ['fight', ['fight','fight']],
                        ['patrol', ['close_patrol','close_patrol']]
                        ]
            elif robot_1_behavior == 'close_patrol':
                return [['patrol', ['close_patrol','close_patrol']],
                        ['fight', ['fight','fight']],
                        ['patrol', ['close_patrol','close_patrol']]
                        ]
            elif robot_1_behavior == 'normal_patrol':
                return [['patrol', ['normal_patrol','normal_patrol']],
                        ['fight', ['fight','fight']],
                        ['patrol', ['normal_patrol','normal_patrol']]
                        ]
            elif robot_1_behavior == 'reload':
                return [['reload', ['reload','reload_cover']],
                        ['patrol', ['normal_patrol','normal_patrol']],
                        ['reload', ['reload','reload_cover']]
                        ]
            elif robot_1_behavior == 'reload_cover':
                return [['reload', ['reload_cover','reload']],
                        ['patrol', ['normal_patrol','normal_patrol']],
                        ['reload', ['reload_cover','reload']]
                        ]
            elif robot_1_behavior == 'slow_escape':
                return [['escape', ['slow_escape','slow_escape']],
                        ['escape', ['slow_escape','slow_escape']],
                        ['escape', ['slow_escape','slow_escape']]
                        ]
            elif robot_1_behavior == 'fast_escape':
                return [['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']]
                        ]
            elif robot_1_behavior == 'sentry':
                return [['sentry', ['sentry','sentry']],
                        ['sentry', ['sentry','fight']],
                        ['sentry', ['sentry','sentry']]
                        ]
        
        """---------------------------------------------------------------------------------------------------------------------"""
        """---------------------------------------------2nd HP region Complete--------------------------------------------------"""
        """---------------------------------------------------------------------------------------------------------------------"""
        ############################################################################################################################
        """----------------------------------------------------------------------------------------------------------------------"""
        """-----------------------------------------------3rd HP region Start----------------------------------------------------"""
        """----------------------------------------------------------------------------------------------------------------------"""   

        if self.threshold_hp[0] < min(self.robot_hp) <= self.threshold_hp[1]:               # HP 4단계 중 3번째로 안전한 단계
                                                                                            # 이 단계의 특징점(buff가 있을 때만 싸운다)
            print(1)
            if min(self.robot_bullet) > self.threshold_bullet[0]:
                print(2)
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    print(3)
                    if min(self.detect_distance) < self.detect_distance_threshold: # in sight
                        if (self.defense_zone == True):
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[1]            # occupy defense zone
                                robot_2_behavior = self.robot_behavior[1]            # occupy defense zone
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[0]     # Fight
                                robot_2_behavior = self.robot_behavior[0]     # Fight
                        else:
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[-2][1]           # fast escape mode vs sentinental
                                robot_2_behavior = self.robot_behavior[-2][1]           # fast excape mode vs sentinental
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                                robot_2_behavior = self.robot_behavior[0]     # 로봇이 버프를 받고 있다면 적 가까이 접근하자
                    else:        
                        if (self.defense_zone == True):
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[1]            # occupy defense zone
                                robot_2_behavior = self.robot_behavior[1]            # occupy defense zone
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol
                                robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol
                        else:
                            if (any(self.robot_buff) == False):
                                robot_1_behavior = self.robot_behavior[-2][0]         # hide
                                robot_2_behavior = self.robot_behavior[-2][0]         # hide
                            elif any(self.robot_buff) == True:
                                robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol
                                robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol
                else:
                    print(4)
                    if (self.defense_zone == True):
                        print(5)
                        if (any(self.robot_buff) == False):
                            print(6)
                            robot_1_behavior = self.robot_behavior[1]            # occupy defense zone
                            robot_2_behavior = self.robot_behavior[1]            # occupy defense zone
                        elif any(self.robot_buff) == True:
                            print(7)
                            robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                            robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                    else:
                        print(8)
                        if (any(self.robot_buff) == False):
                            print(9)
                            robot_1_behavior = self.robot_behavior[-2][0]           # slow escape
                            robot_2_behavior = self.robot_behavior[-2][0]           # slow escape 
                        elif any(self.robot_buff) == True:
                            robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                            robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                                                      
                
                
            elif ((self.robot_bullet[0] > self.robot_bullet[1])) and (min(self.robot_bullet) > self.threshold_bullet[1]):
                robot_1_behavior = self.robot_behavior[3][0]
                robot_2_behavior = self.robot_behavior[3][1]
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[-2][1]                # 빠르게 escape 
                        robot_2_behavior = self.robot_behavior[-2][1]                # 빠르게 escape 
                    else:
                        robot_1_behavior = self.robot_behavior[-2][0]                # 느리게 escape
                        robot_2_behavior = self.robot_behavior[-2][0]                # 느리게 escape
                else:
                    robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                    robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol



            elif ((self.robot_bullet[0] < self.robot_bullet[1])) and (min(self.robot_bullet) > self.threshold_bullet[1]):
                robot_1_behavior = self.robot_behavior[3][1]
                robot_2_behavior = self.robot_behavior[3][0]
                print(19)
                if any(np.ndarray.flatten(self.enemy_detection)) == True:
                    if min(self.detect_distance) < self.detect_distance_threshold:
                        robot_1_behavior = self.robot_behavior[-2][1]                # 빠르게 escape 
                        robot_2_behavior = self.robot_behavior[-2][1]                # 빠르게 escape 
                    else:
                        robot_1_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                        robot_2_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                else:
                    robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                    robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
            


            elif ((self.robot_bullet[0] == self.robot_bullet[1])) and (min(self.robot_bullet) > self.threshold_bullet[1]):
                if self.time_to_reload_zone[0] >= self.time_to_reload_zone[1]: 
                    robot_1_behavior = self.robot_behavior[3][1]
                    robot_2_behavior = self.robot_behavior[3][0]
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                            robot_2_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                        else:
                            robot_1_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                            robot_2_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                    else:
                        robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                        robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                else: 
                    robot_1_behavior = self.robot_behavior[3][0]
                    robot_2_behavior = self.robot_behavior[3][1]
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                            robot_2_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                        else:
                            robot_1_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                            robot_2_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                    else:
                        robot_1_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                        robot_2_behavior = self.robot_behavior[-1]     # sentinental patrol vs slow patrol
                    
            # 둘다 총알이 없을 때, 이건 정말 심각한 상황이다
            else:          
                                                                 # Reload가 급선무다 아직까지는 몸으로 버텨라
                print(44)
                if self.time_to_reload_zone[0] >= self.time_to_reload_zone[1]: 
                    print(414)
                    robot_1_behavior = self.robot_behavior[3][1]
                    robot_2_behavior = self.robot_behavior[3][0]
                    
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                            robot_2_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                        else:
                            robot_1_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                            robot_2_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                    else:
                        robot_1_behavior = self.robot_behavior[3][1]            # Reload
                        robot_2_behavior = self.robot_behavior[3][0]            # Reload
                
                else:
                    print(444)
                    robot_1_behavior = self.robot_behavior[3][0]
                    robot_2_behavior = self.robot_behavior[3][1] 
                    
                    if any(np.ndarray.flatten(self.enemy_detection)) == True:
                        if min(self.detect_distance) < self.detect_distance_threshold:
                            robot_1_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                            robot_2_behavior = self.robot_behavior[-2][1]            # 빠르게 escape 
                        else:
                            robot_1_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                            robot_2_behavior = self.robot_behavior[-2][0]            # 느리게 escape
                    else:
                        robot_1_behavior = self.robot_behavior[3][0]     # sentinental patrol vs slow patrol
                        robot_2_behavior = self.robot_behavior[3][1]     # sentinental patrol vs slow patrol
            if robot_1_behavior == 'fight':
                return [['fight', ['fight','fight']],
                        ['fight', ['fight','fight']],
                        ['fight', ['fight','fight']]
                        ]
            elif robot_1_behavior == 'defense':
                return [['defense', ['defense','defense']],
                        ['fight', ['fight','fight']],
                        ['patrol', ['close_patrol','close_patrol']]
                        ]
            elif robot_1_behavior == 'close_patrol':
                return [['patrol', ['close_patrol','close_patrol']],
                        ['escape', ['slow_escape','slow_escape']],
                        ['patrol', ['close_patrol','close_patrol']]
                        ]
            elif robot_1_behavior == 'normal_patrol':
                return [['patrol', ['normal_patrol','normal_patrol']],
                        ['patrol', ['normal_patrol','normal_patrol']],
                        ['patrol', ['normal_patrol','normal_patrol']]
                        ]
            elif robot_1_behavior == 'reload':
                return [['reload', ['reload','reload_cover']],
                        ['escape', ['slow_escape','slow_escape']],
                        ['reload', ['reload','reload_cover']]
                        ]
            elif robot_1_behavior == 'reload_cover':
                return [['reload', ['reload_cover','reload']],
                        ['escape', ['slow_escape','slow_escape']],
                        ['reload', ['reload_cover','reload']]
                        ]
            elif robot_1_behavior == 'slow_escape':
                return [['escape', ['slow_escape','slow_escape']],
                        ['escape', ['slow_escape','slow_escape']],
                        ['escape', ['slow_escape','slow_escape']]
                        ]
            elif robot_1_behavior == 'fast_escape':
                return [['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']]
                        ]
            elif robot_1_behavior == 'sentry':
                return [['sentry', ['sentry','sentry']],
                        ['sentry', ['sentry','fight']],
                        ['sentry', ['sentry','sentry']]
                        ]

        """---------------------------------------------------------------------------------------------------------------------"""
        """---------------------------------------------3rd HP region Complete--------------------------------------------------"""
        """---------------------------------------------------------------------------------------------------------------------"""
        ############################################################################################################################
        """----------------------------------------------------------------------------------------------------------------------"""
        """-----------------------------------------------Last HP region Start---------------------------------------------------"""
        """----------------------------------------------------------------------------------------------------------------------""" 

        if 0 <= min(self.robot_hp) <= self.threshold_hp[0]:                             # HP 4단계 중 가장 위험한 단계
            if any(np.ndarray.flatten(self.enemy_detection)) == True:
                print(1)
                if min(self.detect_distance) < self.detect_distance_threshold:
                    print(2)
                    robot_1_behavior = self.robot_behavior[-2][1]                     # 빠르게 escape 
                    robot_2_behavior = self.robot_behavior[-2][1]                     # 빠르게 escape 
                else:
                    robot_1_behavior = self.robot_behavior[-2][0]                     # 느리게 escape
                    robot_2_behavior = self.robot_behavior[-2][0]                     # 느리게 escape
            else:
                robot_1_behavior = self.robot_behavior[-1]
                robot_2_behavior = self.robot_behavior[-1]

            # Defense Zone의 Activate Time은 아니지만 체력이 낮기 때문에 hide_behavior를 취한다(마지막 적의 위치를 토대로 특정 위치로 이동)
            # robot_1_behavior = self.robot_behavior[-3]                                # hide behavior
            # robot_2_behavior = self.robot_behavior[-3]                                # hide behavior
            if robot_1_behavior == 'fight':
                return [['fight', ['fight','fight']],
                        ['fight', ['fight','fight']],
                        ['fight', ['fight','fight']]
                        ]
            elif robot_1_behavior == 'defense':
                return [['defense', ['defense','defense']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']]
                        ]
            elif robot_1_behavior == 'close_patrol':
                return [['patrol', ['close_patrol','close_patrol']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']]
                        ]
            elif robot_1_behavior == 'normal_patrol':
                return [['patrol', ['normal_patrol','normal_patrol']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['patrol', ['normal_patrol','normal_patrol']]
                        ]
            elif robot_1_behavior == 'reload':
                return [['reload', ['reload','reload_cover']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['reload', ['reload','reload_cover']]
                        ]
            elif robot_1_behavior == 'reload_cover':
                return [['reload', ['reload_cover','reload']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['reload', ['reload_cover','reload']]
                        ]
            elif robot_1_behavior == 'slow_escape':
                return [['escape', ['slow_escape','slow_escape']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['escape', ['slow_escape','slow_escape']]
                        ]
            elif robot_1_behavior == 'fast_escape':
                return [['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']],
                        ['escape', ['fast_escape','fast_escape']]
                        ]
            elif robot_1_behavior == 'sentry':
                return [['sentry', ['sentry','sentry']],
                        ['sentry', ['sentry','fight']],
                        ['sentry', ['sentry','sentry']]
                        ]




        

