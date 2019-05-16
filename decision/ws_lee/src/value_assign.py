# -*- coding: utf-8 -*-
"""
@author: SHF_W
"""

#!/usr/bin/env python

import random
import math
import numpy as np
import matplotlib.pyplot as plt

class potentialField():
    def __init__(self, size):        
        self.value_matrix = np.zeros(size)
        self.height = self.value_matrix.shape[0]
        self.width = self.value_matrix.shape[1]    
        self.grid = 5.0/self.height    
         
    # 정사각형으로 값을 더해줌
    def square_assign(self, x, y, d, value, *args, **kargs):
        setting = kargs.get('mode', None)
        
        x = int(x*1.0/self.grid)
        y = int(y*1.0/self.grid)
        d = int(d*1.0/self.grid)       
        
        left = max(x-d,0)
        right = min(x+d+1, self.width)
        down = max(y-d,0)
        up= min(y+d+1, self.height)    
            
        if setting == 'abs':
            self.value_matrix[down:up, left:right] = value
        else:
            self.value_matrix[down:up, left:right] += value  
    
    # 직사각형으로 값 지정
    def rectangular_assign(self, x1, x2, y1, y2, value, *args, **kargs):
        setting = kargs.get('mode', None)
        
        if x1 < 0:
            x1 = 0
        if x2 > 8:
            x2 = 8
        if y1 < 0:
            y1 = 0
        if y2 > 5:
            y2 = 0      
        
        x1 = int(x1*1.0/self.grid*1.0)
        x2 = int(x2*1.0/self.grid*1.0)+1
        y1 = int(y1*1.0/self.grid*1.0)
        y2 = int(y2*1.0/self.grid*1.0)+1
        
        if setting == 'abs':
            self.value_matrix[y1:y2, x1:x2] = value             
        else:
            self.value_matrix[y1:y2, x1:x2] += value         

    # 정사각형으로 가운데로 갈수록 값이 커지는 형태로 값 더해줌
    def square_assign_gradient(self, x, y, d, value, gradient):
        x = int(x*1.0/self.grid)
        y = int(y*1.0/self.grid)
        d = int(d*1.0/self.grid)
        
        steps = int(d/gradient+1)
        value= value*1.0/steps
        for i in range(steps):        
            left_in = max(x-d+gradient*i,0)
            right_in = min(x+d+1-gradient*i, self.value_matrix.shape[1])
            down_in = max(y-d-1+gradient*i,0)
            up_in= min(y+d-gradient*i, self.value_matrix.shape[0])        
            self.value_matrix[down_in:up_in, left_in:right_in] += value

    # 원형으로 값 지정            
    def circle_assign(self, x, y, r, value, *args, **kargs):
        setting = kargs.get('mode', None)
        
        x = int(x*1.0/self.grid)
        y = int(y*1.0/self.grid)
        r = int(r*1.0/self.grid)        
        m, n = self.value_matrix.shape
        a, b = np.ogrid[-y:m-y, -x:n-x]
        mask = a*a+b*b <= r*r    
        
        if setting == 'abs':
            self.value_matrix[mask] = value
        else:
            self.value_matrix[mask] += value        
            
    def sector_assign(self, x, y, r1, r2, theta, gamma, value, *args, **kargs):
        setting = kargs.get('mode', None)
        
        x = int(x*1.0/self.grid)
        y = int(y*1.0/self.grid)
        r1 = int(r1*1.0/self.grid)      
        r2 = int(r2*1.0/self.grid)  
                
        if r1 > r2: r1, r2 = r2, r1
        
        m, n = self.value_matrix.shape
        a, b = np.ogrid[-y:m-y, -x:n-x]        
        
        lower = (theta-gamma/2) % (math.pi*2)
        upper = (theta+gamma/2) % (math.pi*2)

        slope1= math.tan(theta-gamma/2)
        slope2= math.tan(theta+gamma/2)        
        

        mask1 = a*a+b*b <= r2*r2
        mask2 = a*a+b*b >= r1*r1

        if lower < 1.5*math.pi and lower > 0.5*math.pi:
            mask3 = (slope1*a-x) > (slope1*b-y)
        else:
            mask3 = (slope1*a-x) < (b-y)
            
        if upper < 1.5*math.pi and upper > 0.5*math.pi:
            mask4 = (slope2*a-x) < (b-y)
        else:
            mask4 = (slope2*a-x) > (b-y)           
        
        
        mask = np.multiply(mask1, mask2)
        mask = np.multiply(mask, mask3)
        mask = np.multiply(mask, mask4)
        
        if setting == 'abs':
            self.value_matrix[mask] = value
        else:
            self.value_matrix[mask] += value   
            
    # 원형으로 가운데로 갈수록 값이 커지는 형태로 값 더해줌
    def circle_assign_gradient(self, x, y, r, value, gradient):
        x = int(x*1.0/self.grid)
        y = int(y*1.0/self.grid)
        r = int(r*1.0/self.grid)
        
        steps = int(r/gradient+1)
        value = value*1.0/steps
        
        for i in range(steps):
            m, n = self.value_matrix.shape
            a, b = np.ogrid[-y:m-y, -x:n-x]
            mask = a*a+b*b <= (gradient*i)*(gradient*i)    
            self.value_matrix[mask] += value
            
            
    def random_assign(self, value):
        mat = np.random.rand(self.height, self.width)        
        self.value_matrix += mat*value
    
    # 현재 위치의 값 보기
    def getValue(self, xy):
        x = int( xy[0] / self.grid)
        y = int( xy[1] / self.grid)
        
        return self.value_matrix[y,x]
       
    # 가장 높은 값과, 그 값의 위치'들'. output이 좀 특이한 형태라 가공 필요
    def getMax(self):
        value = np.max(self.value_matrix)
        return (value, np.where(self.value_matrix >= value))
    
    ## 임시 함수
    def getPoint(self):
        value = np.max(self.value_matrix)
        temp = np.where(self.value_matrix >= value)
        
        index = random.randint(0, len(temp[1])-1)
        
        point = [ temp[1][index]*self.grid, temp[0][index]*self.grid ]       
        return (value, point )
    
    def out(self):
        return self.value_matrix
    
    def plot(self):
        image = np.flip(self.value_matrix, axis=0)    
        plt.imshow(image)
        
        # return distnace and relative angles
    def p2pRelation(self, p1, p2):  
        xd = p2[0]-p1[0]
        yd = p2[1]-p1[1]       
        
        dist = math.sqrt(xd*xd+yd*yd)
        e1_angle = math.atan2(yd,xd)
        if e1_angle == math.pi:
            e2_angle = math.pi/2
        
        return dist, e1_angle, e2_angle
    

