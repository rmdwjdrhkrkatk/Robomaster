import pigpio
import time
import keyboard

'''
pigpio 설치법
    wget abyz.me.uk/rpi/pigpio/pigpio.zip
    unzip pigpio.zip
    cd PIGPIO
    make
    sudo make install

keyboard 설치법
    pip3 install keyboard

실행법
    sudo pigpiod     #pigpio를 킨다
    코드가 있는 폴더로 이동.
    sudo python3 mecanum_keyboard.py

w - 직진, s - 후진, a - 좌측 횡이동, d - 우측 횡이동
좌측 방향키 - 반시계방향 회전, 우측 방향키 - 시계방향 회전

키들의 조합으로 대각선 움직임 등을 만들고자 했는데 잘 됐는지는 모르겠음...
'''

FL2 = 14 #Front Left
FL1 = 15
FR2 = 23
FR1 = 24
BL2 = 7
BL1 = 8
BR2 = 16 #Back Right
BR1 = 20
PFL = 5 #PWM Front Left
PFR = 6
PBL = 13
PBR = 19
pi = pigpio.pi()
speed = [64]

def calc(a):
    if a > 0.0:
        a1 = 'front'
    elif a < 0.0:
        a1 = 'back'
    else:
        a1 = 'stop'
    return a1

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
    front_left = 0.0
    front_right = 0.0
    back_left = 0.0
    back_right = 0.0

    if keyboard.is_pressed('w'):
        front_left += 0.5
        front_right += 0.5
        back_left += 0.5
        back_right += 0.5
        print('front')
    if keyboard.is_pressed('d'):
        front_left += -0.5
        front_right += 0.5
        back_left += 0.5
        back_right += -0.5
        print('right')
    if keyboard.is_pressed('s'):
        front_left += -0.5
        front_right += -0.5
        back_left += -0.5
        back_right += -0.5
        print('back')
    if keyboard.is_pressed('a'):
        front_left += 0.5
        front_right += -0.5
        back_left += -0.5
        back_right += 0.5
        print('left')
    if keyboard.is_pressed('LEFT'):
        front_left += -0.5
        front_right += 0.5
        back_left += -0.5
        back_right += 0.5
        print('CCW turn')
    if keyboard.is_pressed('RIGHT'):
        front_left += 0.5
        front_right += -0.5
        back_left += 0.5
        back_right += -0.5
        print('CW turn')
    if keyboard.is_pressed('1'):
        speed[0] = 64
        print('speed 64')
    if keyboard.is_pressed('2'):
        speed[0] = 128
        print('speed 128')
    if keyboard.is_pressed('3'):
        speed[0] = 255
        print('speed 255')
    
    motor_control(front_left,front_right,back_left,back_right)

    pi.set_PWM_dutycycle(PFL,speed)
    pi.set_PWM_dutycycle(PFR,speed)
    pi.set_PWM_dutycycle(PBL,speed)
    pi.set_PWM_dutycycle(PBR,speed)




