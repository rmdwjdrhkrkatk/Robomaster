;; Auto-generated. Do not edit!


(when (boundp 'roborts_msgs::ProjectileSupply)
  (if (not (find-package "ROBORTS_MSGS"))
    (make-package "ROBORTS_MSGS"))
  (shadow 'ProjectileSupply (find-package "ROBORTS_MSGS")))
(unless (find-package "ROBORTS_MSGS::PROJECTILESUPPLY")
  (make-package "ROBORTS_MSGS::PROJECTILESUPPLY"))

(in-package "ROS")
;;//! \htmlinclude ProjectileSupply.msg.html


(defclass roborts_msgs::ProjectileSupply
  :super ros::object
  :slots (_supply ))

(defmethod roborts_msgs::ProjectileSupply
  (:init
   (&key
    ((:supply __supply) nil)
    )
   (send-super :init)
   (setq _supply __supply)
   self)
  (:supply
   (&optional __supply)
   (if __supply (setq _supply __supply)) _supply)
  (:serialization-length
   ()
   (+
    ;; bool _supply
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _supply
       (if _supply (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _supply
     (setq _supply (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get roborts_msgs::ProjectileSupply :md5sum-) "3f61c0f8bda2af4961ed47ff103d5653")
(setf (get roborts_msgs::ProjectileSupply :datatype-) "roborts_msgs/ProjectileSupply")
(setf (get roborts_msgs::ProjectileSupply :definition-)
      "#projectile supply
bool supply

")



(provide :roborts_msgs/ProjectileSupply "3f61c0f8bda2af4961ed47ff103d5653")


