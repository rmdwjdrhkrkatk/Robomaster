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
    def __init__(self):
        
        self.fov_x = 80
        self.fov_y = 60
        
        self.lower_red = np.array([0,204,120])
        self.upper_red = np.array([12,255,255])
        self.lower_yellow = np.array([28,204,120])
        self.upper_yellow = np.array([46,255,255])
        self.lower_cyan = np.array([112,204,120])
        self.upper_cyan = np.array([140,255,255])
        self.lower_blue = np.array([140,204,120])
        self.upper_blue = np.array([175,255,255])
        
        self.bridge_obj = CvBridge()
        self.image_sub_ = rospy.Subscriber("/image",Image,self.image_CB)
        self.depth_sub_ = rospy.Subscriber("/depth",Image,self.depth_CB)
        self.pub_ = rospy.Publisher("enemy_info", YoloDetectionInfo, queue_size = 4)
        
        self.depth_image = 0
        
        self.red_detected = 0
        self.yellow_detected = 0
        self.cyan_detected = 0
        self.blue_detected = 0
        
        self.red_x =1
        self.red_y =1
        self.red_d =1
        
        
    def image_CB(self,data):
        try:
            cv_image = self.bridge_obj.imgmsg_to_cv2(data,desired_encoding="bgr8")
        except CvBridgeError as e:
            print(e)
        height,width,channels = cv_image.shape
        crop_image = cv_image[int(0.2*height):height][1:width]
        hsv_image = cv2.cvtColor(crop_image, cv2.COLOR_BGR2HSV).astype(np.float)
        mask_image = cv2.inRange(hsv_image, self.lower_red, self.upper_red)
        #blob_image = cv2.bitwise_and(crop_image,crop_image,mask=mask_image)
        m=cv2.moments(mask_image,False)
        
        try:
            self.red_x = m['m10']/m['m00']
            self.red_y = m['m01']/m['m00']
            self.red_detected = 1
            self.red_d = self.depth_image[int(self.red_y+int(0.2*height))][int(self.red_x)]
            detection_info = YoloDetectionInfo()
            detection_info.stamp = rospy.Time.now()
            detection_info.number_of_detection = self.red_detected + self.yellow_detected + self.cyan_detected
            detection_info.enemy_detected[1] = 1
            detection_info.angle_hori[1] = 100 * 180 / 3.141592 * atan2(self.red_x-(0.5*width),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_x)) 
            detection_info.angle_verti[1] = -100 * 180 / 3.141592 * atan2(self.red_y + (0.2*height) - (0.5*height),(0.5*width)/tan(3.141592/180 *0.5 * self.fov_y))
            detection_info.Pixel_X[1] =  self.red_x
            detection_info.Pixel_Y[1] = self.red_y + int(0.2*height)
            detection_info.Pixel_width[1] = width  ###TODO
            detection_info.Pixel_height[1] = height
            detection_info.real_width[1] = 0.45 ###TODO
            detection_info.real_height[1] = 0.45
            detection_info.distance[1] = self.red_d * 1000
            self.pub_.publish(detection_info)
        except ZeroDivisionError:
            self.red_detected = 0
            self.red_x = 1
            self.red_y = 1
            detection_info = YoloDetectionInfo()
            detection_info.stamp = rospy.Time.now()
            detection_info.number_of_detection = self.red_detected + self.yellow_detected + self.cyan_detected
            detection_info.enemy_detected[1] = 0
            detection_info.angle_hori[1] = 0
            detection_info.angle_verti[1] = 0
            detection_info.Pixel_X[1] =  0
            detection_info.Pixel_Y[1] = 0
            detection_info.Pixel_width[1] = width  ###TODO
            detection_info.Pixel_height[1] = height
            detection_info.real_width[1] = 0.45 ###TODO
            detection_info.real_height[1] = 0.45
            detection_info.distance[1] = 0
            self.pub_.publish(detection_info)
            
        #cv2.circle(blob_image,(int(self.red_x),int(self.red_y)),1,(255,255,0),-1)
        
        
        
        #cv2.imshow("image",blob_image)
        #cv2.waitKey(1)
        
        
    def depth_CB(self,data):
        try:
            cv_image = self.bridge_obj.imgmsg_to_cv2(data,desired_encoding="passthrough")
            self.depth_image = cv_image
        except CvBridgeError as e:
            print(e)
