;; Auto-generated. Do not edit!


(when (boundp 'icra_roboin_msgs::XYOffset)
  (if (not (find-package "ICRA_ROBOIN_MSGS"))
    (make-package "ICRA_ROBOIN_MSGS"))
  (shadow 'XYOffset (find-package "ICRA_ROBOIN_MSGS")))
(unless (find-package "ICRA_ROBOIN_MSGS::XYOFFSET")
  (make-package "ICRA_ROBOIN_MSGS::XYOFFSET"))
(unless (find-package "ICRA_ROBOIN_MSGS::XYOFFSETREQUEST")
  (make-package "ICRA_ROBOIN_MSGS::XYOFFSETREQUEST"))
(unless (find-package "ICRA_ROBOIN_MSGS::XYOFFSETRESPONSE")
  (make-package "ICRA_ROBOIN_MSGS::XYOFFSETRESPONSE"))

(in-package "ROS")





(defclass icra_roboin_msgs::XYOffsetRequest
  :super ros::object
  :slots (_x_offset _y_offset ))

(defmethod icra_roboin_msgs::XYOffsetRequest
  (:init
   (&key
    ((:x_offset __x_offset) 0)
    ((:y_offset __y_offset) 0)
    )
   (send-super :init)
   (setq _x_offset (round __x_offset))
   (setq _y_offset (round __y_offset))
   self)
  (:x_offset
   (&optional __x_offset)
   (if __x_offset (setq _x_offset __x_offset)) _x_offset)
  (:y_offset
   (&optional __y_offset)
   (if __y_offset (setq _y_offset __y_offset)) _y_offset)
  (:serialization-length
   ()
   (+
    ;; int8 _x_offset
    1
    ;; int8 _y_offset
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _x_offset
       (write-byte _x_offset s)
     ;; int8 _y_offset
       (write-byte _y_offset s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _x_offset
     (setq _x_offset (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _x_offset 127) (setq _x_offset (- _x_offset 256)))
   ;; int8 _y_offset
     (setq _y_offset (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _y_offset 127) (setq _y_offset (- _y_offset 256)))
   ;;
   self)
  )

(defclass icra_roboin_msgs::XYOffsetResponse
  :super ros::object
  :slots (_received ))

(defmethod icra_roboin_msgs::XYOffsetResponse
  (:init
   (&key
    ((:received __received) nil)
    )
   (send-super :init)
   (setq _received __received)
   self)
  (:received
   (&optional __received)
   (if __received (setq _received __received)) _received)
  (:serialization-length
   ()
   (+
    ;; bool _received
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _received
       (if _received (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _received
     (setq _received (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass icra_roboin_msgs::XYOffset
  :super ros::object
  :slots ())

(setf (get icra_roboin_msgs::XYOffset :md5sum-) "d8dc129d6dde9852a52847783f565dfc")
(setf (get icra_roboin_msgs::XYOffset :datatype-) "icra_roboin_msgs/XYOffset")
(setf (get icra_roboin_msgs::XYOffset :request) icra_roboin_msgs::XYOffsetRequest)
(setf (get icra_roboin_msgs::XYOffset :response) icra_roboin_msgs::XYOffsetResponse)

(defmethod icra_roboin_msgs::XYOffsetRequest
  (:response () (instance icra_roboin_msgs::XYOffsetResponse :init)))

(setf (get icra_roboin_msgs::XYOffsetRequest :md5sum-) "d8dc129d6dde9852a52847783f565dfc")
(setf (get icra_roboin_msgs::XYOffsetRequest :datatype-) "icra_roboin_msgs/XYOffsetRequest")
(setf (get icra_roboin_msgs::XYOffsetRequest :definition-)
      "int8 x_offset
int8 y_offset
---
bool received
")

(setf (get icra_roboin_msgs::XYOffsetResponse :md5sum-) "d8dc129d6dde9852a52847783f565dfc")
(setf (get icra_roboin_msgs::XYOffsetResponse :datatype-) "icra_roboin_msgs/XYOffsetResponse")
(setf (get icra_roboin_msgs::XYOffsetResponse :definition-)
      "int8 x_offset
int8 y_offset
---
bool received
")



(provide :icra_roboin_msgs/XYOffset "d8dc129d6dde9852a52847783f565dfc")


