;; Auto-generated. Do not edit!


(when (boundp 'icra_roboin_msgs::Obstacles)
  (if (not (find-package "ICRA_ROBOIN_MSGS"))
    (make-package "ICRA_ROBOIN_MSGS"))
  (shadow 'Obstacles (find-package "ICRA_ROBOIN_MSGS")))
(unless (find-package "ICRA_ROBOIN_MSGS::OBSTACLES")
  (make-package "ICRA_ROBOIN_MSGS::OBSTACLES"))

(in-package "ROS")
;;//! \htmlinclude Obstacles.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass icra_roboin_msgs::Obstacles
  :super ros::object
  :slots (_header _segments _circles ))

(defmethod icra_roboin_msgs::Obstacles
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:segments __segments) (let (r) (dotimes (i 0) (push (instance icra_roboin_msgs::SegmentObstacle :init) r)) r))
    ((:circles __circles) (let (r) (dotimes (i 0) (push (instance icra_roboin_msgs::CircleObstacle :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _segments __segments)
   (setq _circles __circles)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:segments
   (&rest __segments)
   (if (keywordp (car __segments))
       (send* _segments __segments)
     (progn
       (if __segments (setq _segments (car __segments)))
       _segments)))
  (:circles
   (&rest __circles)
   (if (keywordp (car __circles))
       (send* _circles __circles)
     (progn
       (if __circles (setq _circles (car __circles)))
       _circles)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; icra_roboin_msgs/SegmentObstacle[] _segments
    (apply #'+ (send-all _segments :serialization-length)) 4
    ;; icra_roboin_msgs/CircleObstacle[] _circles
    (apply #'+ (send-all _circles :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; icra_roboin_msgs/SegmentObstacle[] _segments
     (write-long (length _segments) s)
     (dolist (elem _segments)
       (send elem :serialize s)
       )
     ;; icra_roboin_msgs/CircleObstacle[] _circles
     (write-long (length _circles) s)
     (dolist (elem _circles)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; icra_roboin_msgs/SegmentObstacle[] _segments
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _segments (let (r) (dotimes (i n) (push (instance icra_roboin_msgs::SegmentObstacle :init) r)) r))
     (dolist (elem- _segments)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; icra_roboin_msgs/CircleObstacle[] _circles
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _circles (let (r) (dotimes (i n) (push (instance icra_roboin_msgs::CircleObstacle :init) r)) r))
     (dolist (elem- _circles)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get icra_roboin_msgs::Obstacles :md5sum-) "d1ad5dcfab44f5899cb5e192beb9c8f9")
(setf (get icra_roboin_msgs::Obstacles :datatype-) "icra_roboin_msgs/Obstacles")
(setf (get icra_roboin_msgs::Obstacles :definition-)
      "Header header

icra_roboin_msgs/SegmentObstacle[] segments
icra_roboin_msgs/CircleObstacle[] circles

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: icra_roboin_msgs/SegmentObstacle
geometry_msgs/Point first_point
geometry_msgs/Point last_point


================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: icra_roboin_msgs/CircleObstacle
geometry_msgs/Point center
float64 radius


")



(provide :icra_roboin_msgs/Obstacles "d1ad5dcfab44f5899cb5e192beb9c8f9")


