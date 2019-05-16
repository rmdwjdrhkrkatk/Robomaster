import roslib
import sys
import rospy
import cv2
import numpy as np
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
from icra_roboin_msgs.msg import YoloDetectionInfo
from math import atan2, tan

class StageImageGrabber(object):
    def __init__(self,my_color="blue",ally_color="blue",enemy1_color="red",enemy2_color="red"):
        
        self.fov_x = 80
        self.fov_y = 60
        
        self.lower_red = np.array([0,204,120])
        self.upper_red = np.array([10,255,255])
        self.lower_yellow = np.array([20,204,120])
        self.upper_yellow = np.array([35,255,255])
        self.lower_green = np.array([40,204,120])
        self.upper_green = np.array([80,255,255])
        self.lower_blue = np.array([100,204,120])
        self.upper_blue = np.array([130,255,255])
        
        self.bridge_obj = CvBridge()
        self.image_sub_ = rospy.Subscriber("image",Image,self.image_CB)
        self.depth_sub_ = rospy.Subscriber("depth",Image,self.depth_CB)
        self.pub_ = rospy.Publisher("enemy_info", YoloDetectionInfo, queue_size = 4)
        
        self.depth_image = 0

	self.my_color=my_color
        self.ally_color=ally_color
        self.enemy1_color=enemy1_color
        self.enemy2_color=enemy2_color

	self.use_ally = True
        self.use_enemy1 = True
        self.use_enemy2 = True

        self.lower_my_color = 0
        self.upper_my_color = 0
        self.lower_ally_color = 0
        self.upper_ally_color = 0
        self.lower_enemy1_color = 0
        self.upper_enemy1_color = 0
        self.lower_enemy2_color = 0
        self.upper_enemy2_color = 0

        if self.my_color == "blue":
            self.lower_my_color = self.lower_blue
            self.upper_my_color = self.upper_blue
        elif self.my_color == "green" :
            self.lower_my_color = self.lower_green
            self.upper_my_color = self.upper_green
        elif self.my_color == "red" :
            self.lower_my_color = self.lower_red
            self.upper_my_color = self.upper_red
        elif self.my_color == "yellow" :
            self.lower_my_color = self.lower_yellow
            self.upper_my_color = self.upper_yellow
        else:
            rospy.loginfo("stage blob detector error: unknown my color name")
            



        if self.ally_color == "blue" :
            self.lower_ally_color = self.lower_blue
            self.upper_ally_color = self.upper_blue
        elif self.ally_color == "green" :
            self.lower_ally_color = self.lower_green
            self.upper_ally_color = self.upper_green
        elif self.ally_color == "red" :
            self.lower_ally_color = self.lower_red
            self.upper_ally_color = self.upper_red
        elif self.ally_color == "yellow" :
            self.lower_ally_color = self.lower_yellow
            self.upper_ally_color = self.upper_yellow
        elif self.ally_color == "none" :
            self.use_ally = False
        else:
            rospy.loginfo("stage blob detector error: unknown ally color name")
            self.use_ally = False



        if self.enemy1_color == "blue" :
            self.lower_enemy1_color = self.lower_blue
            self.upper_enemy1_color = self.upper_blue
        elif self.enemy1_color == "green" :
            self.lower_enemy1_color = self.lower_green
            self.upper_enemy1_color = self.upper_green
        elif self.enemy1_color == "red" :
            self.lower_enemy1_color = self.lower_red
            self.upper_enemy1_color = self.upper_red
        elif self.enemy1_color == "yellow" :
            self.lower_enemy1_color = self.lower_yellow
            self.upper_enemy1_color = self.upper_yellow
        elif self.enemy1_color == "none" :
            self.use_enemy1 = False
        else:
            rospy.loginfo("stage blob detector error: unknown enemy1 color name")
            self.use_enemy1 = False


        if self.enemy2_color == "blue" :
            self.lower_enemy2_color = self.lower_blue
            self.upper_enemy2_color = self.upper_blue
        elif self.enemy2_color == "green" :
            self.lower_enemy2_color = self.lower_green
            self.upper_enemy2_color = self.upper_green
        elif self.enemy2_color == "red" :
            self.lower_enemy2_color = self.lower_red
            self.upper_enemy2_color = self.upper_red
        elif self.enemy2_color == "yellow" :
            self.lower_enemy2_color = self.lower_yellow
            self.upper_enemy2_color = self.upper_yellow
        elif self.enemy2_color == "none" :
            self.use_enemy2 = False
        else:
            rospy.loginfo("stage blob detector error: unknown enemy2 color name")
            self.use_enemy2 = False


               
        self.ally_detected = 0
        self.enemy1_detected = 0
        self.enemy2_detected = 0
      
        self.ally_x =1
        self.ally_y =1
        self.ally_d =1

        self.enemy1_x =1
        self.enemy1_y =1
        self.enemy1_d =1

        self.enemy2_x =1
        self.enemy2_y =1
        self.enemy2_d =1


        
    def image_CB(self,data):
        try:
            cv_image = self.bridge_obj.imgmsg_to_cv2(data,desired_encoding="bgr8")
        except CvBridgeError as e:
            print(e)
        height,width,channels = cv_image.shape
        crop_image = cv_image[int(0.2*height):height][1:width]
        hsv_image = cv2.cvtColor(crop_image, cv2.COLOR_BGR2HSV).astype(np.float)
        #cv2.imshow("image",hsv_image)
        detection_info = YoloDetectionInfo()
        detection_info.stamp = rospy.Time.now()
        detection_info.number_of_detection = self.ally_detected + self.enemy1_detected + self.enemy2_detected
	if self.use_ally :
            mask_image_ally = cv2.inRange(hsv_image, self.lower_ally_color, self.upper_ally_color)
            self.message_creator(mask_image_ally,detection_info,"ally",height,width,channels)
	if self.use_enemy1 :
            mask_image_enemy1 = cv2.inRange(hsv_image, self.lower_enemy1_color, self.upper_enemy1_color)
            #cv2.imshow("image",mask_image_enemy1)
            self.message_creator(mask_image_enemy1,detection_info,"enemy1",height,width,channels)
	if self.use_enemy2 :
            mask_image_enemy2 = cv2.inRange(hsv_image, self.lower_enemy2_color, self.upper_enemy2_color)
            self.message_creator(mask_image_enemy2,detection_info,"enemy2",height,width,channels)

	self.pub_.publish(detection_info)

        #blob_image = cv2.bitwise_and(crop_image,crop_image,mask=mask_image)
        #cv2.circle(blob_image,(int(self.red_x),int(self.red_y)),1,(255,255,0),-1)
        #cv2.imshow("image",blob_image)
        #cv2.waitKey(1)




    def message_creator(self,mask_image,message_obj,what,height,width,channels):
        m = cv2.moments(mask_image,False)
        if what =="ally":
            try:
                self.ally_x = m['m10']/m['m00']
                self.ally_y = m['m01']/m['m00']
                self.ally_detected = 1
                self.ally_d = self.depth_image[int(self.ally_y+int(0.2*height))][int(self.ally_x)]
                message_obj.enemy_detected[0]=1
                message_obj.angle_hori[0] = 100 * 180 / 3.141592 * atan2(self.ally_x - (0.5*width),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_x))
                message_obj.angle_verti[0] = -100 * 180 / 3.141592 * atan2(self.ally_y + (0.2*height) - (0.5*height),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_y))
                message_obj.Pixel_X[0] =  self.ally_x
                message_obj.Pixel_Y[0] = self.ally_y + int(0.2*height)
                message_obj.Pixel_width[0] = width  ###TODO
                message_obj.Pixel_height[0] = height
                message_obj.real_width[0] = 0.45 ###TODO
                message_obj.real_height[0] = 0.45
                message_obj.distance[0] = self.ally_d * 1000
            except ZeroDivisionError:
                self.ally_detected = 0
                self.ally_x = 1
                self.ally_y = 1
                message_obj.enemy_detected[0]=0
                message_obj.angle_hori[0] = 0
                message_obj.angle_verti[0] = 0
                message_obj.Pixel_X[0] =  0
                message_obj.Pixel_Y[0] = 0
                message_obj.Pixel_width[0] = 0
                message_obj.Pixel_height[0] = 0
                message_obj.real_width[0] = 0
                message_obj.real_height[0] = 0
                message_obj.distance[0] = 0

        if what =="enemy1":
            try:
                self.enemy1_x = m['m10']/m['m00']
                self.enemy1_y = m['m01']/m['m00']
                self.enemy1_detected = 1
                self.enemy1_d = self.depth_image[int(self.enemy1_y+int(0.2*height))][int(self.enemy1_x)]
                message_obj.enemy_detected[1]=1
                message_obj.angle_hori[1] = 100 * 180 / 3.141592 * atan2(self.enemy1_x - (0.5*width),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_x))
                message_obj.angle_verti[1] = -100 * 180 / 3.141592 * atan2(self.enemy1_y + (0.2*height) - (0.5*height),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_y))
                message_obj.Pixel_X[1] =  self.enemy1_x
                message_obj.Pixel_Y[1] = self.enemy1_y + int(0.2*height)
                message_obj.Pixel_width[1] = width  ###TODO
                message_obj.Pixel_height[1] = height
                message_obj.real_width[1] = 0.45 ###TODO
                message_obj.real_height[1] = 0.45
                message_obj.distance[1] = self.enemy1_d * 1000
            except ZeroDivisionError:
                self.enemy1_detected = 0
                self.enemy1_x = 1
                self.enemy1_y = 1
                message_obj.enemy_detected[1]=0
                message_obj.angle_hori[1] = 0
                message_obj.angle_verti[1] = 0
                message_obj.Pixel_X[1] =  0
                message_obj.Pixel_Y[1] = 0
                message_obj.Pixel_width[1] = 0
                message_obj.Pixel_height[1] = 0
                message_obj.real_width[1] = 0
                message_obj.real_height[1] = 0
                message_obj.distance[1] = 0

        if what =="enemy2":
            try:
                self.enemy2_x = m['m10']/m['m00']
                self.enemy2_y = m['m01']/m['m00']
                self.enemy2_detected = 1
                self.enemy2_d = self.depth_image[int(self.enemy2_y+int(0.2*height))][int(self.enemy2_x)]
                message_obj.enemy_detected[2]=1
                message_obj.angle_hori[2] = 100 * 180 / 3.141592 * atan2(self.enemy2_x - (0.5*width),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_x))
                message_obj.angle_verti[2] = -100 * 180 / 3.141592 * atan2(self.enemy2_y + (0.2*height) - (0.5*height),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_y))
                message_obj.Pixel_X[2] =  self.enemy2_x
                message_obj.Pixel_Y[2] = self.enemy2_y + int(0.2*height)
                message_obj.Pixel_width[2] = width  ###TODO
                message_obj.Pixel_height[2] = height
                message_obj.real_width[2] = 0.45 ###TODO
                message_obj.real_height[2] = 0.45
                message_obj.distance[2] = self.enemy2_d * 1000
            except ZeroDivisionError:
                self.enemy2_detected = 0
                self.enemy2_x = 1
                self.enemy2_y = 1
                message_obj.enemy_detected[2]=0
                message_obj.angle_hori[2] = 0
                message_obj.angle_verti[2] = 0
                message_obj.Pixel_X[2] =  0
                message_obj.Pixel_Y[2] = 0
                message_obj.Pixel_width[2] = 0
                message_obj.Pixel_height[2] = 0
                message_obj.real_width[2] = 0
                message_obj.real_height[2] = 0
                message_obj.distance[2] = 0





       
        
    def depth_CB(self,data):
        try:
            cv_image = self.bridge_obj.imgmsg_to_cv2(data,desired_encoding="passthrough")
            self.depth_image = cv_image
        except CvBridgeError as e:
            print(e)
