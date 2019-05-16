# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import pigpio
from PID import PID

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
width = 640
height = 480
shootx = 330
shooty = 340
camera.resolution = (width, height)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(width, height))

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
xp =0.6
xi =0.1
xd =1.0
firing = 0
resting = 0

prevx = 0
prevy = 0
fire = False

pi = pigpio.pi()
pi.set_servo_pulsewidth(LR_PIN, rollM)
pi.set_servo_pulsewidth(UD_PIN, pitchM)

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# allow the camera to warmup
time.sleep(0.1)

def shoot():
    pi.write(SHOOT_CONTROL, 1)
    time.sleep(0.1)
    pi.write(SHOOT_CONTROL, 0)

# capture frames from the camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text

    image = frame.array
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.7, 5)
    cv2.rectangle(image,(shootx-4,shooty-4),(shootx+4,shooty+4),(0,0,255),2)
    # print(faces)
    for (x,y,w,h) in faces:
        cv2.rectangle(image,(x,y),(x+w,y+h),(255,0,0),2)
        aimx = x + w/2
        aimy = y + h/2
        # aimx = aimx + (aimx-prevx)/10
        # aimy = aimy + (aimy-prevy)/10
        pid_x = PID(dt=0.05, Kp=xp, Ki=xi, Kd=xd) # roll
        pid_y = PID(dt=0.05, Kp=xp, Ki=xi, Kd=xd) # pitch
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
        
        
        
        if abs(shootx-aimx) < 10 and abs(shooty-aimy) < 10:
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
                resting = 2
            elif resting == 0 and firing >= 6:
                print('rest start')
                resting = 10
                firing = 0
        
        
    resting -= 1
    if resting <= 0:
        resting = 0
    
    # show the frame
    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF
    # clear the stream in preparation for the next frame
    rawCapture.truncate(0)
    # if the `q` key was pressed, break from the loop
    if key == ord("q"):
        cv2.destroyAllWindows()
        break
