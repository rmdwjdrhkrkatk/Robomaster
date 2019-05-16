;; Auto-generated. Do not edit!


(when (boundp 'icra_roboin_msgs::YoloDetectionFeedback)
  (if (not (find-package "ICRA_ROBOIN_MSGS"))
    (make-package "ICRA_ROBOIN_MSGS"))
  (shadow 'YoloDetectionFeedback (find-package "ICRA_ROBOIN_MSGS")))
(unless (find-package "ICRA_ROBOIN_MSGS::YOLODETECTIONFEEDBACK")
  (make-package "ICRA_ROBOIN_MSGS::YOLODETECTIONFEEDBACK"))

(in-package "ROS")
;;//! \htmlinclude YoloDetectionFeedback.msg.html


(defclass icra_roboin_msgs::YoloDetectionFeedback
  :super ros::object
  :slots (_stamp _infochecker _enemy _angle_hori _angle_verti _Pixel_X _Pixel_Y _Pixel_width _Pixel_height _real_width _real_height _distance ))

(defmethod icra_roboin_msgs::YoloDetectionFeedback
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:infochecker __infochecker) 0)
    ((:enemy __enemy) 0)
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
   (setq _infochecker (round __infochecker))
   (setq _enemy (round __enemy))
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
  (:infochecker
   (&optional __infochecker)
   (if __infochecker (setq _infochecker __infochecker)) _infochecker)
  (:enemy
   (&optional __enemy)
   (if __enemy (setq _enemy __enemy)) _enemy)
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
    ;; uint8 _infochecker
    1
    ;; uint8 _enemy
    1
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
     ;; uint8 _infochecker
       (write-byte _infochecker s)
     ;; uint8 _enemy
       (write-byte _enemy s)
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
   ;; uint8 _infochecker
     (setq _infochecker (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _enemy
     (setq _enemy (sys::peek buf ptr- :char)) (incf ptr- 1)
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

(setf (get icra_roboin_msgs::YoloDetectionFeedback :md5sum-) "264543f7a1172d61963435fe8085999c")
(setf (get icra_roboin_msgs::YoloDetectionFeedback :datatype-) "icra_roboin_msgs/YoloDetectionFeedback")
(setf (get icra_roboin_msgs::YoloDetectionFeedback :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#feedback
time stamp
uint8 infochecker
uint8 enemy
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



(provide :icra_roboin_msgs/YoloDetectionFeedback "264543f7a1172d61963435fe8085999c")


