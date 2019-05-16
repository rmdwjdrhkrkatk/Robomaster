;; Auto-generated. Do not edit!


(when (boundp 'icra_roboin_msgs::CircleObstacle)
  (if (not (find-package "ICRA_ROBOIN_MSGS"))
    (make-package "ICRA_ROBOIN_MSGS"))
  (shadow 'CircleObstacle (find-package "ICRA_ROBOIN_MSGS")))
(unless (find-package "ICRA_ROBOIN_MSGS::CIRCLEOBSTACLE")
  (make-package "ICRA_ROBOIN_MSGS::CIRCLEOBSTACLE"))

(in-package "ROS")
;;//! \htmlinclude CircleObstacle.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass icra_roboin_msgs::CircleObstacle
  :super ros::object
  :slots (_center _radius ))

(defmethod icra_roboin_msgs::CircleObstacle
  (:init
   (&key
    ((:center __center) (instance geometry_msgs::Point :init))
    ((:radius __radius) 0.0)
    )
   (send-super :init)
   (setq _center __center)
   (setq _radius (float __radius))
   self)
  (:center
   (&rest __center)
   (if (keywordp (car __center))
       (send* _center __center)
     (progn
       (if __center (setq _center (car __center)))
       _center)))
  (:radius
   (&optional __radius)
   (if __radius (setq _radius __radius)) _radius)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _center
    (send _center :serialization-length)
    ;; float64 _radius
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _center
       (send _center :serialize s)
     ;; float64 _radius
       (sys::poke _radius (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _center
     (send _center :deserialize buf ptr-) (incf ptr- (send _center :serialization-length))
   ;; float64 _radius
     (setq _radius (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get icra_roboin_msgs::CircleObstacle :md5sum-) "ab296cd39c1a1fa7dd67209d6a4767e1")
(setf (get icra_roboin_msgs::CircleObstacle :datatype-) "icra_roboin_msgs/CircleObstacle")
(setf (get icra_roboin_msgs::CircleObstacle :definition-)
      "geometry_msgs/Point center
float64 radius


================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :icra_roboin_msgs/CircleObstacle "ab296cd39c1a1fa7dd67209d6a4767e1")


