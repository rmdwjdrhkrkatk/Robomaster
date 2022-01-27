def compute_possibility(self,action):
    is_it_possible = [True, True]
    return is_it_possible

def selection(a_r='fight',a_r_1='fight',a_r_2='fight'):
    if action[0] == 'defense': # Does not have to collaborate
        is_it_possible = compute_possibility(['defense','defense'])
        if is_it_possible[0] == True:
            if is_it_possible[1] == True:
                if self.hp_1 > self.hp_2: action = ['defense_cover', 'defense']
                else: action = ['defense', 'defense_cover']
            else:
                action = ['defense', None]
        else:
            if is_it_possible[1] == True: action = [None, 'defense']
            else: action = [None,None]

        return action

    elif action[0] == 'reload': # Must collaborate
        if action[1][0] == 'reload':
            is_it_possible = compute_possibility(['reload','reload_cover'])
            if is_it_possible[0] == True:
                if is_it_possible[1] == True: action = ['reload','reload_cover']
                else: action = ['reload', None]
            else:
                if is_it_possible[1] == True: action = [None, 'reload_cover']
                else: action = [None, None] 
        elif action[1][1] == 'reload':
            is_it_possible = compute_possibility(['reload_cover','reload'])
            if is_it_possible[1] == True:
                if is_it_possible[0] == True: action = ['reload_cover','reload']
                else: action = [None,'reload_cover']
            else:
                if is_it_possible[0] == True: action = ['reload_cover',None]
                else: action = [None, None] 
        
        return action

    elif action[0] == 'fight':
        is_it_possible = compute_possibility(['fight','fight'])
        if is_it_possible[0] == True:
            if is_it_possible[1] == True: action = ['fight', 'fight']
            else: action = ['fight', 'close_patrol']
        else:
            if is_it_possible[1] == True: action = ['close_patrol','fight']
            else: action = ['close_patrol','close_patrol'] 
        
        return action


    elif action[0] == 'patrol':
        if self.action_required == 'close_patrol'
            is_it_possible = compute_possibility(['close_patrol','close_patrol'])
            if is_it_possible[0] == True:
                if is_it_possible[1] == True: action = ['close_patrol', 'close_patrol']
                else: action = ['close_patrol', None]
            else:
                if is_it_possible[1] == True: action = [None, 'close_patrol']
                else: action = [None,None]

            return action

        if self.action_required == 'normal_patrol'
            is_it_possible = compute_possibility('normal_patrol')
            if is_it_possible[0] == True:
                if is_it_possible[1] == True: action = ['normal_patrol', 'normal_patrol']
                else: action = ['normal_patrol', None]
            else:
                if is_it_possible[1] == True: action = [None, 'normal_patrol']
                else: action = [None,None]

            return action

    elif action[0] == 'escape':
        if self.action_required == 'slow_escape_behavior'
            is_it_possible = compute_possibility('slow_escape_behavior')
            if is_it_possible[0] == True:
                if is_it_possible[1] == True: action = ['slow_escape_behavior', 'slow_escape_behavior']
                else: action = ['slow_escape_behavior', None]
            else:
                if is_it_possible[1] == True: action = [None, 'slow_escape_behavior']
                else: action = [None,None]

            return action

        if self.action_required == 'fast_escape_behavior'
            is_it_possible = compute_possibility('fast_escape_behavior')
            if is_it_possible[0] == True:
                if is_it_possible[1] == True: action = ['fast_escape_behavior', 'fast_escape_behavior']
                else: action = ['fast_escape_behavior', None]
            else:
                if is_it_possible[1] == True: action = [None, 'fast_escape_behavior']
                else: action = [None,None]

            return action
    
    elif action[0] == 'sentinental':
        is_it_possible = [True,True]
        action = [None, None]
        if self.action_required_1 == 'sentinental': action[0] = 'sentinental'
        if self.action_required_2 == 'sentinental': action[1] = 'sentinental'
        return action

    elif action[0] == 'hide':
        is_it_possible = [True, True]
        if self.action_required_1 == 'hide': action[0] = 'hide'
        if self.action_required_2 == 'hide': action[1] = 'hide'
        return action






