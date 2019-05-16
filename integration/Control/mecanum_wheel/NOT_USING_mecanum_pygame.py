import pigpio
import time
import pygame
"https://www.pygame.org/wiki/GettingStarted << 설치 가이드"
FL1 = 14 #Front Left
FL2 = 15
FR1 = 23
FR2 = 24
BL1 = 25
BL2 = 8
BR1 = 16 #Back Right
BR2 = 20
PFL = 5 #PWM Front Left
PFR = 6
PBL = 13
PBR = 19
front_left = 0.0
front_right = 0.0
back_left = 0.0
back_right = 0.0
pi = pigpio.pi()
pygame.init()
'''
pi.set_mode(FL1, pigpio.OUTPUT)
pi.set_mode(FL2, pigpio.OUTPUT)
pi.set_mode(FR1, pigpio.OUTPUT)
pi.set_mode(FR2, pigpio.OUTPUT)
pi.set_mode(BL1, pigpio.OUTPUT)
pi.set_mode(BL2, pigpio.OUTPUT)
pi.set_mode(BR2, pigpio.OUTPUT)
pi.set_mode(BR2, pigpio.OUTPUT)
pi.set_mode(PFL, pigpio.OUTPUT)
pi.set_mode(PFR, pigpio.OUTPUT)
pi.set_mode(PBL, pigpio.OUTPUT)
pi.set_mode(PBR, pigpio.OUTPUT)
'''

# Working on...
def reset():
    front_left = 0.0
    front_right = 0.0
    back_left = 0.0
    back_right = 0.0
def add(fl,fr,bl,br):
    front_left += fl
    front_right += fr
    back_left += bl
    back_right += br
def calc(a):
    if a < 0.0:
        a1 = 'back'
    elif a > 0.0:
        a1 = 'front'
    else:
        a1 = 'stop'
    return a1
def read_key(reading):
    if reading[pygame.K_w]:
        add(0.5,0.5,0.5,0.5)
        print('front')
    if reading[pygame.K_a]:
        add(-0.5,0.5,0.5,-0.5)
        print('left')
    if reading[pygame.K_s]:
        add(-0.5,-0.5,-0.5,-0.5)
        print('back')
    if reading[pygame.K_d]:
        add(0.5,-0.5,-0.5,0.5)
        print('right')
    if reading[pygame.K_LEFT]:
        add(-0.5,0.5,0.5,-0.5)
        print('CCW turn')
    if reading[pygame.K_RIGHT]:
        add(0.5,-0.5,-0.5,0.5)
        print('CW turn')

def motor_control(a,b,c,d):
    a1 = calc(a)
    b1 = calc(b)
    c1 = calc(c)
    d1 = calc(d)
    
    if a1 == 'front':
        pi.write(FL1, 1)
        pi.write(FL2, 0)
    elif a1 == 'back':
        pi.write(FL1, 0)
        pi.write(FL2, 1)
    elif a1 == 'stop':
        pi.write(FL1, 0)
        pi.write(FL2, 0)

    if b1 == 'front':
        pi.write(FR1, 1)
        pi.write(FR2, 0)
    elif b1 == 'back':
        pi.write(FR1, 0)
        pi.write(FR2, 1)
    elif b1 == 'stop':
        pi.write(FR1, 0)
        pi.write(FR2, 0)

    if c1 == 'front':
        pi.write(BL1, 1)
        pi.write(BL2, 0)
    elif c1 == 'back':
        pi.write(BL1, 0)
        pi.write(BL2, 1)
    elif c1 == 'stop':
        pi.write(BL1, 0)
        pi.write(BL2, 0)

    if d1 == 'front':
        pi.write(BR1, 1)
        pi.write(BR2, 0)
    elif d1 == 'back':
        pi.write(BR1, 0)
        pi.write(BR2, 1)
    elif d1 == 'stop':
        pi.write(BR1, 0)
        pi.write(BR2, 0)


while True:
    reset()
    try:
        key = pygame.key.get_pressed()

        read_key(key)

        motor_control(front_left,front_right,back_left,back_right)

        pi.set_PWM_dutycycle(PFL,128*(abs(front_left)/3))
        pi.set_PWM_dutycycle(PFR,128*(abs(front_right)/3))
        pi.set_PWM_dutycycle(PBL,128*(abs(back_left)/3))
        pi.set_PWM_dutycycle(PBR,128*(abs(back_right)/3))
    except:
        pass



