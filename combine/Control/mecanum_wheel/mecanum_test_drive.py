import pigpio
import time
import pygame
"https://www.pygame.org/wiki/GettingStarted << 설치 가이드"
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

strength1 = 64
strength2 = 128

pi = pigpio.pi()



while True:
    pi.write(FL1, 1)
    pi.write(FL2, 0)
    pi.write(FR1, 1)
    pi.write(FR2, 0)
    pi.write(BL1, 1)
    pi.write(BL2, 0)
    pi.write(BR1, 1)
    pi.write(BR2, 0)                                    
    pi.set_PWM_dutycycle(PFL,strength1)
    pi.set_PWM_dutycycle(PFR,strength1)
    pi.set_PWM_dutycycle(PBL,strength1)
    pi.set_PWM_dutycycle(PBR,strength1)
    time.sleep(5)

    pi.write(FL1, 1)
    pi.write(FL2, 0)
    pi.write(FR1, 0)
    pi.write(FR2, 1)
    pi.write(BL1, 0)
    pi.write(BL2, 1)
    pi.write(BR1, 1)
    pi.write(BR2, 0)                                    
    pi.set_PWM_dutycycle(PFL,strength2)
    pi.set_PWM_dutycycle(PFR,strength2)
    pi.set_PWM_dutycycle(PBL,strength2)
    pi.set_PWM_dutycycle(PBR,strength2)
    time.sleep(5)

    pi.write(FL1, 0)
    pi.write(FL2, 1)
    pi.write(FR1, 1)
    pi.write(FR2, 0)
    pi.write(BL1, 1)
    pi.write(BL2, 0)
    pi.write(BR1, 0)
    pi.write(BR2, 1)                                    
    pi.set_PWM_dutycycle(PFL,strength2)
    pi.set_PWM_dutycycle(PFR,strength2)
    pi.set_PWM_dutycycle(PBL,strength2)
    pi.set_PWM_dutycycle(PBR,strength2)
    time.sleep(5)

    pi.write(FL1, 0)
    pi.write(FL2, 1)
    pi.write(FR1, 0)
    pi.write(FR2, 1)
    pi.write(BL1, 0)
    pi.write(BL2, 1)
    pi.write(BR1, 0)
    pi.write(BR2, 1)                                    
    pi.set_PWM_dutycycle(PFL,strength2)
    pi.set_PWM_dutycycle(PFR,strength2)
    pi.set_PWM_dutycycle(PBL,strength2)
    pi.set_PWM_dutycycle(PBR,strength2)
    time.sleep(5)

    pi.write(FL1, 0)
    pi.write(FL2, 0)
    pi.write(FR1, 0)
    pi.write(FR2, 0)
    pi.write(BL1, 0)
    pi.write(BL2, 0)
    pi.write(BR1, 0)
    pi.write(BR2, 0)                                    
    pi.set_PWM_dutycycle(PFL,0)
    pi.set_PWM_dutycycle(PFR,0)
    pi.set_PWM_dutycycle(PBL,0)
    pi.set_PWM_dutycycle(PBR,0)    
    break


