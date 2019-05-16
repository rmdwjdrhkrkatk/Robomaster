;; Auto-generated. Do not edit!


(when (boundp 'icra_roboin_msgs::PitchGain)
  (if (not (find-package "ICRA_ROBOIN_MSGS"))
    (make-package "ICRA_ROBOIN_MSGS"))
  (shadow 'PitchGain (find-package "ICRA_ROBOIN_MSGS")))
(unless (find-package "ICRA_ROBOIN_MSGS::PITCHGAIN")
  (make-package "ICRA_ROBOIN_MSGS::PITCHGAIN"))
(unless (find-package "ICRA_ROBOIN_MSGS::PITCHGAINREQUEST")
  (make-package "ICRA_ROBOIN_MSGS::PITCHGAINREQUEST"))
(unless (find-package "ICRA_ROBOIN_MSGS::PITCHGAINRESPONSE")
  (make-package "ICRA_ROBOIN_MSGS::PITCHGAINRESPONSE"))

(in-package "ROS")





(defclass icra_roboin_msgs::PitchGainRequest
  :super ros::object
  :slots (_p _i _d ))

(defmethod icra_roboin_msgs::PitchGainRequest
  (:init
   (&key
    ((:p __p) 0.0)
    ((:i __i) 0.0)
    ((:d __d) 0.0)
    )
   (send-super :init)
   (setq _p (float __p))
   (setq _i (float __i))
   (setq _d (float __d))
   self)
  (:p
   (&optional __p)
   (if __p (setq _p __p)) _p)
  (:i
   (&optional __i)
   (if __i (setq _i __i)) _i)
  (:d
   (&optional __d)
   (if __d (setq _d __d)) _d)
  (:serialization-length
   ()
   (+
    ;; float64 _p
    8
    ;; float64 _i
    8
    ;; float64 _d
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _p
       (sys::poke _p (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _i
       (sys::poke _i (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _d
       (sys::poke _d (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _p
     (setq _p (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _i
     (setq _i (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _d
     (setq _d (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass icra_roboin_msgs::PitchGainResponse
  :super ros::object
  :slots (_received ))

(defmethod icra_roboin_msgs::PitchGainResponse
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

(defclass icra_roboin_msgs::PitchGain
  :super ros::object
  :slots ())

(setf (get icra_roboin_msgs::PitchGain :md5sum-) "223542de9427e9df0f0b5bfbdc1715cb")
(setf (get icra_roboin_msgs::PitchGain :datatype-) "icra_roboin_msgs/PitchGain")
(setf (get icra_roboin_msgs::PitchGain :request) icra_roboin_msgs::PitchGainRequest)
(setf (get icra_roboin_msgs::PitchGain :response) icra_roboin_msgs::PitchGainResponse)

(defmethod icra_roboin_msgs::PitchGainRequest
  (:response () (instance icra_roboin_msgs::PitchGainResponse :init)))

(setf (get icra_roboin_msgs::PitchGainRequest :md5sum-) "223542de9427e9df0f0b5bfbdc1715cb")
(setf (get icra_roboin_msgs::PitchGainRequest :datatype-) "icra_roboin_msgs/PitchGainRequest")
(setf (get icra_roboin_msgs::PitchGainRequest :definition-)
      "float64 p
float64 i
float64 d
---
bool received
")

(setf (get icra_roboin_msgs::PitchGainResponse :md5sum-) "223542de9427e9df0f0b5bfbdc1715cb")
(setf (get icra_roboin_msgs::PitchGainResponse :datatype-) "icra_roboin_msgs/PitchGainResponse")
(setf (get icra_roboin_msgs::PitchGainResponse :definition-)
      "float64 p
float64 i
float64 d
---
bool received
")



(provide :icra_roboin_msgs/PitchGain "223542de9427e9df0f0b5bfbdc1715cb")


