import numpy as np
import cv2 as cv
import cv2
import pyrealsense2 as rs
import argparse
import socket
from time import sleep

confThreshold = 0.5  # accuracy 50% = 0.5
nmsThreshold = 0.4
nmsThreshold = 0.4
'''
sock  = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   ### chang
sock.connect(('192.168.168.101', 12345))
'''

#definition sets

def getOutputsNames(net):
    # Get the names of all the layers in the network
    layersNames = net.getLayerNames()
    # Get the names of the output layers, i.e. the layers with unconnected outputs
    return [layersNames[i[0] - 1] for i in net.getUnconnectedOutLayers()]

def postprocess(frame, outs):
    frameHeight = frame.shape[0]
    frameWidth = frame.shape[1]

    classIds = []
    confidences = []
    boxes = []
    # Scan through all the bounding boxes output from the network and keep only the
    # ones with high confidence scores. Assign the box's class label as the class with the highest score.
    classIds = []
    confidences = []
    boxes = []
    for out in outs:
        for detection in out:
            scores = detection[5:]
            classId = np.argmax(scores)
            confidence = scores[classId]
            if confidence > confThreshold:
                center_x = int(detection[0] * frameWidth)
                center_y = int(detection[1] * frameHeight)
                width = int(detection[2] * frameWidth)
                height = int(detection[3] * frameHeight)
                left = int(center_x - width / 2)
                top = int(center_y - height / 2)
                classIds.append(classId)
                confidences.append(float(confidence))
                boxes.append([left, top, width, height])
                global X
                global Y
                X= center_x
                Y= center_y

    # Perform non maximum suppression to eliminate redundant overlapping boxes with
    # lower confidences.
    indices = cv.dnn.NMSBoxes(boxes, confidences, confThreshold, nmsThreshold)
    for i in indices:
        i = i[0]
        box = boxes[i]
        left = box[0]
        top = box[1]
        width = box[2]
        height = box[3]
        drawPred(classIds[i], confidences[i], left, top, left + width, top + height)

def drawPred(classId, conf, left, top, right, bottom):
    # Draw a bounding box.
    cv.rectangle(detctframe, (left, top), (right, bottom), (0, 0, 255))

    label = '%.2f' % conf

    # Get the label for the class name and its confidence
    if classes:
        assert(classId < len(classes))
        label = '%s:%s' % (classes[classId], label)

    #Display the label at the top of the bounding box
    labelSize, baseLine = cv.getTextSize(label, cv.FONT_HERSHEY_SIMPLEX, 0.5, 1)
    top = max(top, labelSize[1])
    cv.putText(detctframe, label, (left, top), cv.FONT_HERSHEY_SIMPLEX, 0.5, (255,255,255))



# Configure depth and color streams
pipeline = rs.pipeline()
config = rs.config()
config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)

# Start streaming
pipeline.start(config)

#dectacting setting
Width = 640
Height = 480
scale = 0.00392 # 1/255 (1/chennel)
classes = ['robot']  #if you want to add new obj
COLORS = np.random.uniform(0, 255, size=(len(classes), 3)) # generate different colors for different classes
net = cv2.dnn.readNetFromDarknet('/home/kdh/robomaster/python/dectacting/venv/final.cfg','/home/kdh/robomaster/python/dectacting/venv/yolov3-tiny_30000.weights')

#cfg first than weight
net.setPreferableBackend(cv.dnn.DNN_BACKEND_OPENCV)
net.setPreferableTarget(cv.dnn.DNN_TARGET_CPU)
Numberofframe = 0

try:
    while True:
        X=0
        Y=0

        # Wait for a coherent pair of frames: depth and color
        frames = pipeline.wait_for_frames()
        depth_frame = frames.get_depth_frame()
        color_frame = frames.get_color_frame()
        if not depth_frame or not color_frame:
            continue

        # Convert images to numpy arrays
        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())

        detctframe = color_image
        Numberofframe = Numberofframe +1
        blob = cv.dnn.blobFromImage(detctframe , 1/255, (416, 416), [0,0,0], 1, crop=False) # Create a 4D blob from a frame.
        net.setInput(blob) # Sets the input to the network
        outs = net.forward(getOutputsNames(net)) # Runs the forward pass to get output of the output layers
        postprocess(detctframe, outs) # Remove the bounNumberofframeding boxes with low confidence
        # Put efficiency information. The function getPerfProfile returns the
        # overall time for inference(t) and the timings for each of the layers(in layersTimes)
        t, _ = net.getPerfProfile()
        label = 'Inference time: %.2f ms' % (t * 1000.0 / cv.getTickFrequency())
        cv.putText(detctframe , label, (0, 15), cv.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255))
        if X !=0 and Y !=0:

            distance = 0
            distance = depth_frame.get_distance(X,Y)
            print('distance info (mm) : ' + str(distance) )
            print(X,Y,distance)
            '''
            if Numberofframe % 20 == 0 :
                send_x = X
                send_y = Y
                send_dis = int(distance * 1000)
                print('send data:' ,'X:' ,send_x ,'Y:', send_y , 'distance:',send_dis)

                sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                sock.connect(('192.168.168.101', 12345))
                data_str = "{} {} {}".format(send_x, send_y, send_dis)
                byte_data = str.encode(data_str)
                sock.send(byte_data)
                '''





        # Apply colormap on depth image (image must be converted to 8-bit per pixel first)
        #depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, alpha=0.03), cv2.COLORMAP_JET)

        # Stack both images horizontally
        #images = np.hstack((color_image, depth_colormap))

        # Show images
        cv2.namedWindow('RealSense', cv2.WINDOW_AUTOSIZE)
        cv2.imshow('RealSense', detctframe)
        cv2.waitKey(1)

finally:

    # Stop streaming
    pipeline.stop()
