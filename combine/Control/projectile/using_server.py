import time
import pigpio
from PID import PID
import socket

# initialize the camera and grab a reference to the raw camera capture
width = 640
height = 480
shootx = 331
shooty = 361

SHOOT_CONTROL = 5
LR_PIN     = 15 # left right
UD_PIN    = 13 # up down
mid = 1330
midR = 1240
upper_limit = 1500
lower_limit = 1100
upper_limitR = 1840
lower_limitR = 640
rollM = midR
pitchM = mid
xp =0.5
xi =0.1
xd =1.0
firing = 0
resting = 0
fire = False

pi = pigpio.pi()
pi.set_servo_pulsewidth(LR_PIN, rollM)
pi.set_servo_pulsewidth(UD_PIN, pitchM)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('192.168.168.101', 12345))
server_socket.listen(0)

time.sleep(0.1)
step = 1
def shoot():
    pi.write(SHOOT_CONTROL, 1)
    time.sleep(0.15)
    pi.write(SHOOT_CONTROL, 0)

while True:
    client_socket, addr = server_socket.accept()
    data = client_socket.recv(65535)
    received_string = data.decode("utf-8")
    ll = received_string.split()
    print('step',step)
    step+=1
    try:
        aimx = ll[0]
        aimy = ll[1]
        d = ll[2]
        aimx = int(aimx)
        aimy = int(aimy)
        pid_x = PID(dt=0.2, Kp=xp, Ki=xi, Kd=xd) # roll
        pid_y = PID(dt=0.2, Kp=xp, Ki=xi, Kd=xd) # pitch
        ux = pid_x.feedback(shootx - aimx)
        uy = pid_y.feedback(shooty - aimy)
        
        rollM = rollM + ux
        pitchM = pitchM - uy
        
        if rollM > upper_limitR:
            rollM = upper_limitR
        elif rollM < lower_limitR:
            rollM = lower_limitR
        pi.set_servo_pulsewidth(LR_PIN, rollM)
            
        if pitchM > upper_limit:
            pitchM = upper_limit
        elif pitchM < lower_limit:
            pitchM = lower_limit
        pi.set_servo_pulsewidth(UD_PIN, pitchM)
        

        if abs(shootx-aimx) < 8 and abs(shooty-aimy) < 8:
            fire = True
        else:
            fire = False
            
        if fire:
            if resting > 0:
                print('resting')
            elif resting == 0 and firing < 6:
                print('shooting')
                shoot()
                firing += 1
                resting = 1
            elif resting == 0 and firing >= 6:
                print('rest start')
                resting = 1
                firing = 0
    except:
        print('not working')

    resting -= 1
    if resting <= 0:
        resting = 0
        

