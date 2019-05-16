;; Auto-generated. Do not edit!


(when (boundp 'icra_roboin_msgs::YoloDetectionInfo)
  (if (not (find-package "ICRA_ROBOIN_MSGS"))
    (make-package "ICRA_ROBOIN_MSGS"))
  (shadow 'YoloDetectionInfo (find-package "ICRA_ROBOIN_MSGS")))
(unless (find-package "ICRA_ROBOIN_MSGS::YOLODETECTIONINFO")
  (make-package "ICRA_ROBOIN_MSGS::YOLODETECTIONINFO"))

(in-package "ROS")
;;//! \htmlinclude YoloDetectionInfo.msg.html


(defclass icra_roboin_msgs::YoloDetectionInfo
  :super ros::object
  :slots (_stamp _number_of_detection _reserved _enemy_detected _angle_hori _angle_verti _Pixel_X _Pixel_Y _Pixel_width _Pixel_height _real_width _real_height _distance ))

(defmethod icra_roboin_msgs::YoloDetectionInfo
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:number_of_detection __number_of_detection) 0)
    ((:reserved __reserved) (make-array 3 :initial-element 0 :element-type :integer))
    ((:enemy_detected __enemy_detected) (make-array 3 :initial-element 0 :element-type :integer))
    ((:angle_hori __angle_hori) (make-array 3 :initial-element 0 :element-type :integer))
    ((:angle_verti __angle_verti) (make-array 3 :initial-element 0 :element-type :integer))
    ((:Pixel_X __Pixel_X) (make-array 3 :initial-element 0 :element-type :integer))
    ((:Pixel_Y __Pixel_Y) (make-array 3 :initial-element 0 :element-type :integer))
    ((:Pixel_width __Pixel_width) (make-array 3 :initial-element 0 :element-type :integer))
    ((:Pixel_height __Pixel_height) (make-array 3 :initial-element 0 :element-type :integer))
    ((:real_width __real_width) (make-array 3 :initial-element 0 :element-type :integer))
    ((:real_height __real_height) (make-array 3 :initial-element 0 :element-type :integer))
    ((:distance __distance) (make-array 3 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _number_of_detection (round __number_of_detection))
   (setq _reserved __reserved)
   (setq _enemy_detected __enemy_detected)
   (setq _angle_hori __angle_hori)
   (setq _angle_verti __angle_verti)
   (setq _Pixel_X __Pixel_X)
   (setq _Pixel_Y __Pixel_Y)
   (setq _Pixel_width __Pixel_width)
   (setq _Pixel_height __Pixel_height)
   (setq _real_width __real_width)
   (setq _real_height __real_height)
   (setq _distance __distance)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:number_of_detection
   (&optional __number_of_detection)
   (if __number_of_detection (setq _number_of_detection __number_of_detection)) _number_of_detection)
  (:reserved
   (&optional __reserved)
   (if __reserved (setq _reserved __reserved)) _reserved)
  (:enemy_detected
   (&optional __enemy_detected)
   (if __enemy_detected (setq _enemy_detected __enemy_detected)) _enemy_detected)
  (:angle_hori
   (&optional __angle_hori)
   (if __angle_hori (setq _angle_hori __angle_hori)) _angle_hori)
  (:angle_verti
   (&optional __angle_verti)
   (if __angle_verti (setq _angle_verti __angle_verti)) _angle_verti)
  (:Pixel_X
   (&optional __Pixel_X)
   (if __Pixel_X (setq _Pixel_X __Pixel_X)) _Pixel_X)
  (:Pixel_Y
   (&optional __Pixel_Y)
   (if __Pixel_Y (setq _Pixel_Y __Pixel_Y)) _Pixel_Y)
  (:Pixel_width
   (&optional __Pixel_width)
   (if __Pixel_width (setq _Pixel_width __Pixel_width)) _Pixel_width)
  (:Pixel_height
   (&optional __Pixel_height)
   (if __Pixel_height (setq _Pixel_height __Pixel_height)) _Pixel_height)
  (:real_width
   (&optional __real_width)
   (if __real_width (setq _real_width __real_width)) _real_width)
  (:real_height
   (&optional __real_height)
   (if __real_height (setq _real_height __real_height)) _real_height)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; int16 _number_of_detection
    2
    ;; int8[3] _reserved
    (* 1    3)
    ;; int8[3] _enemy_detected
    (* 1    3)
    ;; int16[3] _angle_hori
    (* 2    3)
    ;; int16[3] _angle_verti
    (* 2    3)
    ;; int16[3] _Pixel_X
    (* 2    3)
    ;; int16[3] _Pixel_Y
    (* 2    3)
    ;; int16[3] _Pixel_width
    (* 2    3)
    ;; int16[3] _Pixel_height
    (* 2    3)
    ;; int16[3] _real_width
    (* 2    3)
    ;; int16[3] _real_height
    (* 2    3)
    ;; int16[3] _distance
    (* 2    3)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; int16 _number_of_detection
       (write-word _number_of_detection s)
     ;; int8[3] _reserved
     (dotimes (i 3)
       (write-byte (elt _reserved i) s)
       )
     ;; int8[3] _enemy_detected
     (dotimes (i 3)
       (write-byte (elt _enemy_detected i) s)
       )
     ;; int16[3] _angle_hori
     (dotimes (i 3)
       (write-word (elt _angle_hori i) s)
       )
     ;; int16[3] _angle_verti
     (dotimes (i 3)
       (write-word (elt _angle_verti i) s)
       )
     ;; int16[3] _Pixel_X
     (dotimes (i 3)
       (write-word (elt _Pixel_X i) s)
       )
     ;; int16[3] _Pixel_Y
     (dotimes (i 3)
       (write-word (elt _Pixel_Y i) s)
       )
     ;; int16[3] _Pixel_width
     (dotimes (i 3)
       (write-word (elt _Pixel_width i) s)
       )
     ;; int16[3] _Pixel_height
     (dotimes (i 3)
       (write-word (elt _Pixel_height i) s)
       )
     ;; int16[3] _real_width
     (dotimes (i 3)
       (write-word (elt _real_width i) s)
       )
     ;; int16[3] _real_height
     (dotimes (i 3)
       (write-word (elt _real_height i) s)
       )
     ;; int16[3] _distance
     (dotimes (i 3)
       (write-word (elt _distance i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int16 _number_of_detection
     (setq _number_of_detection (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int8[3] _reserved
   (dotimes (i (length _reserved))
     (setf (elt _reserved i) (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> (elt _reserved i) 127) (setf (elt _reserved i) (- (elt _reserved i) 256)))
     )
   ;; int8[3] _enemy_detected
   (dotimes (i (length _enemy_detected))
     (setf (elt _enemy_detected i) (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> (elt _enemy_detected i) 127) (setf (elt _enemy_detected i) (- (elt _enemy_detected i) 256)))
     )
   ;; int16[3] _angle_hori
   (dotimes (i (length _angle_hori))
     (setf (elt _angle_hori i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _angle_verti
   (dotimes (i (length _angle_verti))
     (setf (elt _angle_verti i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _Pixel_X
   (dotimes (i (length _Pixel_X))
     (setf (elt _Pixel_X i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _Pixel_Y
   (dotimes (i (length _Pixel_Y))
     (setf (elt _Pixel_Y i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _Pixel_width
   (dotimes (i (length _Pixel_width))
     (setf (elt _Pixel_width i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _Pixel_height
   (dotimes (i (length _Pixel_height))
     (setf (elt _Pixel_height i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _real_width
   (dotimes (i (length _real_width))
     (setf (elt _real_width i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _real_height
   (dotimes (i (length _real_height))
     (setf (elt _real_height i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;; int16[3] _distance
   (dotimes (i (length _distance))
     (setf (elt _distance i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     )
   ;;
   self)
  )

(setf (get icra_roboin_msgs::YoloDetectionInfo :md5sum-) "8c9b3f0e444e2f6af4be1632d58bee33")
(setf (get icra_roboin_msgs::YoloDetectionInfo :datatype-) "icra_roboin_msgs/YoloDetectionInfo")
(setf (get icra_roboin_msgs::YoloDetectionInfo :definition-)
      "time stamp
int16 number_of_detection
int8[3] reserved
int8[3] enemy_detected
int16[3] angle_hori
int16[3] angle_verti
int16[3] Pixel_X
int16[3] Pixel_Y
int16[3] Pixel_width
int16[3] Pixel_height
int16[3] real_width
int16[3] real_height
int16[3] distance

")



(provide :icra_roboin_msgs/YoloDetectionInfo "8c9b3f0e444e2f6af4be1632d58bee33")


