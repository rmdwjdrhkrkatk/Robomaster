from Decision_selection import Decision_selection_class
# import Behavior_possibility

import time


def get_state():
    state1 =  {
        'ammo': 3,   #####
        'is_enemy_1_detected': False,
        'is_enemy_2_detected': False,
        'enemy_distance': 2., 
        'my_health': 100,   #####
        'has_buff': False   #####
    }                                     

    a = {
        # 'buff_left': {'nsecs': 0, 'secs': 0},
        # 'buff_zone_cooltime': {'nsecs': 0, 'secs': 0},
        # 'current_behavior_process': 2,
        # 'current_behavior_style': 1,
        # 'enemy_pose1': {'header': {'frame_id': '',
        # 'seq': 0,
        # 'stamp': {'nsecs': 0, 'secs': 0}},
        # 'pose': {'orientation': {'w': 0.0, 'x': 0.0, 'y': 0.0, 'z': 0.0},
        # 'position': {'x': 0.0, 'y': 0.0, 'z': 0.0}}},
        # 'enemy_pose2': {'header': {'frame_id': '',
        # 'seq': 0,
        # 'stamp': {'nsecs': 0, 'secs': 0}},
        # 'pose': {'orientation': {'w': 0.0, 'x': 0.0, 'y': 0.0, 'z': 0.0},
        # 'position': {'x': 0.0, 'y': 0.0, 'z': 0.0}}},
        # 'enemy_priority': 3,
        # 'game_start_time': {'nsecs': 400000000, 'secs': 4},
        # 'game_state': 2,
        # 'goal': {'etc': 0.0,
        # 'header': {'frame_id': 'robot_0/map',
        # 'seq': 0,
        # 'stamp': {'nsecs': 200000000, 'secs': 193}},
        # 'x': 2.061732172649977,
        # 'xa': 0.0,
        # 'y': 0.9734800516102516,
        # 'ya': 0.0,
        # 'yaw': 0.0,
        # 'yawa': 0.0},
        # 'has_buff': False,
        # 'how_many_enemies_detected': 0,
        
        # 'is_hit': False,
        # 'last_hit_time': {'nsecs': 0, 'secs': 0},
        # 'locked_on_enemy': 0,
        # 'my_pose': {'header': {'frame_id': 'robot_0/map',
        # 'seq': 0,
        # 'stamp': {'nsecs': 0, 'secs': 205}},
        # 'pose': {'orientation': {'w': 0.9905062946940394,
        #     'x': 0.0,
        #     'y': 0.0,
        #     'z': 0.1374673785720989},
        # 'position': {'x': 2.01508103546965, 'y': 0.9571719811718515, 'z': 0.0}}},
        # 'reload_zone_cooltime': {'nsecs': 0, 'secs': 0},
        # 'stamp': {'nsecs': 0, 'secs': 205},
        # 'time_passed_from_start': {'nsecs': 600000000, 'secs': 200},
        # 'which_armor_hit': 102
        }
    
    state2 =  {
        'ammo': 2,
        'is_enemy_1_detected': False,
        'is_enemy_2_detected': False,
        'enemy_distance': 15,
        'my_health': 100,    
        'has_buff': False
                                      

        # 'buff_left': {'nsecs': 0, 'secs': 0},
        # 'buff_zone_cooltime': {'nsecs': 0, 'secs': 0},
        # 'current_behavior_process': 2,
        # 'current_behavior_style': 1,
        # 'enemy_pose1': {'header': {'frame_id': '',
        # 'seq': 0,
        # 'stamp': {'nsecs': 0, 'secs': 0}},
        # 'pose': {'orientation': {'w': 0.0, 'x': 0.0, 'y': 0.0, 'z': 0.0},
        # 'position': {'x': 0.0, 'y': 0.0, 'z': 0.0}}},
        # 'enemy_pose2': {'header': {'frame_id': '',
        # 'seq': 0,
        # 'stamp': {'nsecs': 0, 'secs': 0}},
        # 'pose': {'orientation': {'w': 0.0, 'x': 0.0, 'y': 0.0, 'z': 0.0},
        # 'position': {'x': 0.0, 'y': 0.0, 'z': 0.0}}},
        # 'enemy_priority': 3,
        # 'game_start_time': {'nsecs': 400000000, 'secs': 4},
        # 'game_state': 2,
        # 'goal': {'etc': 0.0,
        # 'header': {'frame_id': 'robot_0/map',
        # 'seq': 0,
        # 'stamp': {'nsecs': 200000000, 'secs': 193}},
        # 'x': 2.061732172649977,
        # 'xa': 0.0,
        # 'y': 0.9734800516102516,
        # 'ya': 0.0,
        # 'yaw': 0.0,
        # 'yawa': 0.0},
        # 'how_many_enemies_detected': 0,
        
        # 'is_hit': False,
        # 'last_hit_time': {'nsecs': 0, 'secs': 0},
        # 'locked_on_enemy': 0,
        # 'my_pose': {'header': {'frame_id': 'robot_0/map',
        # 'seq': 0,
        # 'stamp': {'nsecs': 0, 'secs': 205}},
        # 'pose': {'orientation': {'w': 0.9905062946940394,
        #     'x': 0.0,
        #     'y': 0.0,
        #     'z': 0.1374673785720989},
        # 'position': {'x': 2.01508103546965, 'y': 0.9571719811718515, 'z': 0.0}}},
        # 'reload_zone_cooltime': {'nsecs': 0, 'secs': 0},
        # 'stamp': {'nsecs': 0, 'secs': 205},
        # 'time_passed_from_start': {'nsecs': 600000000, 'secs': 200},
        # 'which_armor_hit': 102
        }

    # return GetInfoClient("robot_0",1), GetInfoClient("robot_1",1)
    return state1, state2

def main():
    real_time = 50
    print('start')
    while True:
        D = Decision_selection_class()
        real_time += 1
        state1, state2 = get_state()

        # print(real_time)
        action_required = D.F_decision_selection(state1,state2,real_time)
        
        time.sleep(1)

        print(real_time, ' : ', action_required)

if __name__ == '__main__':
	main()

