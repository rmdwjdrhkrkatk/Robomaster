; Auto-generated. Do not edit!


(cl:in-package icra_roboin_msgs-msg)


;//! \htmlinclude Obstacles.msg.html

(cl:defclass <Obstacles> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (segments
    :reader segments
    :initarg :segments
    :type (cl:vector icra_roboin_msgs-msg:SegmentObstacle)
   :initform (cl:make-array 0 :element-type 'icra_roboin_msgs-msg:SegmentObstacle :initial-element (cl:make-instance 'icra_roboin_msgs-msg:SegmentObstacle)))
   (circles
    :reader circles
    :initarg :circles
    :type (cl:vector icra_roboin_msgs-msg:CircleObstacle)
   :initform (cl:make-array 0 :element-type 'icra_roboin_msgs-msg:CircleObstacle :initial-element (cl:make-instance 'icra_roboin_msgs-msg:CircleObstacle))))
)

(cl:defclass Obstacles (<Obstacles>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Obstacles>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Obstacles)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-msg:<Obstacles> is deprecated: use icra_roboin_msgs-msg:Obstacles instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Obstacles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:header-val is deprecated.  Use icra_roboin_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'segments-val :lambda-list '(m))
(cl:defmethod segments-val ((m <Obstacles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:segments-val is deprecated.  Use icra_roboin_msgs-msg:segments instead.")
  (segments m))

(cl:ensure-generic-function 'circles-val :lambda-list '(m))
(cl:defmethod circles-val ((m <Obstacles>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:circles-val is deprecated.  Use icra_roboin_msgs-msg:circles instead.")
  (circles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Obstacles>) ostream)
  "Serializes a message object of type '<Obstacles>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'segments))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'segments))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'circles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'circles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Obstacles>) istream)
  "Deserializes a message object of type '<Obstacles>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'segments) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'segments)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'icra_roboin_msgs-msg:SegmentObstacle))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'circles) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'circles)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'icra_roboin_msgs-msg:CircleObstacle))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Obstacles>)))
  "Returns string type for a message object of type '<Obstacles>"
  "icra_roboin_msgs/Obstacles")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Obstacles)))
  "Returns string type for a message object of type 'Obstacles"
  "icra_roboin_msgs/Obstacles")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Obstacles>)))
  "Returns md5sum for a message object of type '<Obstacles>"
  "d1ad5dcfab44f5899cb5e192beb9c8f9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Obstacles)))
  "Returns md5sum for a message object of type 'Obstacles"
  "d1ad5dcfab44f5899cb5e192beb9c8f9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Obstacles>)))
  "Returns full string definition for message of type '<Obstacles>"
  (cl:format cl:nil "Header header~%~%icra_roboin_msgs/SegmentObstacle[] segments~%icra_roboin_msgs/CircleObstacle[] circles~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: icra_roboin_msgs/SegmentObstacle~%geometry_msgs/Point first_point~%geometry_msgs/Point last_point~%~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: icra_roboin_msgs/CircleObstacle~%geometry_msgs/Point center~%float64 radius~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Obstacles)))
  "Returns full string definition for message of type 'Obstacles"
  (cl:format cl:nil "Header header~%~%icra_roboin_msgs/SegmentObstacle[] segments~%icra_roboin_msgs/CircleObstacle[] circles~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: icra_roboin_msgs/SegmentObstacle~%geometry_msgs/Point first_point~%geometry_msgs/Point last_point~%~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: icra_roboin_msgs/CircleObstacle~%geometry_msgs/Point center~%float64 radius~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Obstacles>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'segments) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'circles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Obstacles>))
  "Converts a ROS message object to a list"
  (cl:list 'Obstacles
    (cl:cons ':header (header msg))
    (cl:cons ':segments (segments msg))
    (cl:cons ':circles (circles msg))
))
