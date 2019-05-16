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

pygame.init()

while True:
    key = pygame.key.get_pressed()
    if key[pygame.K_w]:
        print('front')
    if key[pygame.K_a]:
        print('left')
    if key[pygame.K_s]:
        print('back')
    if key[pygame.K_d]:
        print('right')
    if key[pygame.K_LEFT]:
        print('CCW turn')
    if key[pygame.K_RIGHT]:
        print('CW turn')




