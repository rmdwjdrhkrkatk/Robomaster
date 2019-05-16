; Auto-generated. Do not edit!


(cl:in-package icra_roboin_msgs-srv)


;//! \htmlinclude PitchGain-request.msg.html

(cl:defclass <PitchGain-request> (roslisp-msg-protocol:ros-message)
  ((p
    :reader p
    :initarg :p
    :type cl:float
    :initform 0.0)
   (i
    :reader i
    :initarg :i
    :type cl:float
    :initform 0.0)
   (d
    :reader d
    :initarg :d
    :type cl:float
    :initform 0.0))
)

(cl:defclass PitchGain-request (<PitchGain-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PitchGain-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PitchGain-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-srv:<PitchGain-request> is deprecated: use icra_roboin_msgs-srv:PitchGain-request instead.")))

(cl:ensure-generic-function 'p-val :lambda-list '(m))
(cl:defmethod p-val ((m <PitchGain-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:p-val is deprecated.  Use icra_roboin_msgs-srv:p instead.")
  (p m))

(cl:ensure-generic-function 'i-val :lambda-list '(m))
(cl:defmethod i-val ((m <PitchGain-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:i-val is deprecated.  Use icra_roboin_msgs-srv:i instead.")
  (i m))

(cl:ensure-generic-function 'd-val :lambda-list '(m))
(cl:defmethod d-val ((m <PitchGain-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:d-val is deprecated.  Use icra_roboin_msgs-srv:d instead.")
  (d m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PitchGain-request>) ostream)
  "Serializes a message object of type '<PitchGain-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'p))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'i))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PitchGain-request>) istream)
  "Deserializes a message object of type '<PitchGain-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'p) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'i) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'd) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PitchGain-request>)))
  "Returns string type for a service object of type '<PitchGain-request>"
  "icra_roboin_msgs/PitchGainRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PitchGain-request)))
  "Returns string type for a service object of type 'PitchGain-request"
  "icra_roboin_msgs/PitchGainRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PitchGain-request>)))
  "Returns md5sum for a message object of type '<PitchGain-request>"
  "223542de9427e9df0f0b5bfbdc1715cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PitchGain-request)))
  "Returns md5sum for a message object of type 'PitchGain-request"
  "223542de9427e9df0f0b5bfbdc1715cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PitchGain-request>)))
  "Returns full string definition for message of type '<PitchGain-request>"
  (cl:format cl:nil "float64 p~%float64 i~%float64 d~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PitchGain-request)))
  "Returns full string definition for message of type 'PitchGain-request"
  (cl:format cl:nil "float64 p~%float64 i~%float64 d~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PitchGain-request>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PitchGain-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PitchGain-request
    (cl:cons ':p (p msg))
    (cl:cons ':i (i msg))
    (cl:cons ':d (d msg))
))
;//! \htmlinclude PitchGain-response.msg.html

(cl:defclass <PitchGain-response> (roslisp-msg-protocol:ros-message)
  ((received
    :reader received
    :initarg :received
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass PitchGain-response (<PitchGain-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PitchGain-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PitchGain-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-srv:<PitchGain-response> is deprecated: use icra_roboin_msgs-srv:PitchGain-response instead.")))

(cl:ensure-generic-function 'received-val :lambda-list '(m))
(cl:defmethod received-val ((m <PitchGain-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:received-val is deprecated.  Use icra_roboin_msgs-srv:received instead.")
  (received m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PitchGain-response>) ostream)
  "Serializes a message object of type '<PitchGain-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'received) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PitchGain-response>) istream)
  "Deserializes a message object of type '<PitchGain-response>"
    (cl:setf (cl:slot-value msg 'received) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PitchGain-response>)))
  "Returns string type for a service object of type '<PitchGain-response>"
  "icra_roboin_msgs/PitchGainResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PitchGain-response)))
  "Returns string type for a service object of type 'PitchGain-response"
  "icra_roboin_msgs/PitchGainResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PitchGain-response>)))
  "Returns md5sum for a message object of type '<PitchGain-response>"
  "223542de9427e9df0f0b5bfbdc1715cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PitchGain-response)))
  "Returns md5sum for a message object of type 'PitchGain-response"
  "223542de9427e9df0f0b5bfbdc1715cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PitchGain-response>)))
  "Returns full string definition for message of type '<PitchGain-response>"
  (cl:format cl:nil "bool received~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PitchGain-response)))
  "Returns full string definition for message of type 'PitchGain-response"
  (cl:format cl:nil "bool received~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PitchGain-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PitchGain-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PitchGain-response
    (cl:cons ':received (received msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PitchGain)))
  'PitchGain-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PitchGain)))
  'PitchGain-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PitchGain)))
  "Returns string type for a service object of type '<PitchGain>"
  "icra_roboin_msgs/PitchGain")