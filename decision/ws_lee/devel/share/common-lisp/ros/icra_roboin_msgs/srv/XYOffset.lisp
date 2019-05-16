; Auto-generated. Do not edit!


(cl:in-package icra_roboin_msgs-srv)


;//! \htmlinclude XYOffset-request.msg.html

(cl:defclass <XYOffset-request> (roslisp-msg-protocol:ros-message)
  ((x_offset
    :reader x_offset
    :initarg :x_offset
    :type cl:fixnum
    :initform 0)
   (y_offset
    :reader y_offset
    :initarg :y_offset
    :type cl:fixnum
    :initform 0))
)

(cl:defclass XYOffset-request (<XYOffset-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <XYOffset-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'XYOffset-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-srv:<XYOffset-request> is deprecated: use icra_roboin_msgs-srv:XYOffset-request instead.")))

(cl:ensure-generic-function 'x_offset-val :lambda-list '(m))
(cl:defmethod x_offset-val ((m <XYOffset-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:x_offset-val is deprecated.  Use icra_roboin_msgs-srv:x_offset instead.")
  (x_offset m))

(cl:ensure-generic-function 'y_offset-val :lambda-list '(m))
(cl:defmethod y_offset-val ((m <XYOffset-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:y_offset-val is deprecated.  Use icra_roboin_msgs-srv:y_offset instead.")
  (y_offset m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <XYOffset-request>) ostream)
  "Serializes a message object of type '<XYOffset-request>"
  (cl:let* ((signed (cl:slot-value msg 'x_offset)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y_offset)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <XYOffset-request>) istream)
  "Deserializes a message object of type '<XYOffset-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x_offset) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y_offset) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<XYOffset-request>)))
  "Returns string type for a service object of type '<XYOffset-request>"
  "icra_roboin_msgs/XYOffsetRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'XYOffset-request)))
  "Returns string type for a service object of type 'XYOffset-request"
  "icra_roboin_msgs/XYOffsetRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<XYOffset-request>)))
  "Returns md5sum for a message object of type '<XYOffset-request>"
  "d8dc129d6dde9852a52847783f565dfc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'XYOffset-request)))
  "Returns md5sum for a message object of type 'XYOffset-request"
  "d8dc129d6dde9852a52847783f565dfc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<XYOffset-request>)))
  "Returns full string definition for message of type '<XYOffset-request>"
  (cl:format cl:nil "int8 x_offset~%int8 y_offset~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'XYOffset-request)))
  "Returns full string definition for message of type 'XYOffset-request"
  (cl:format cl:nil "int8 x_offset~%int8 y_offset~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <XYOffset-request>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <XYOffset-request>))
  "Converts a ROS message object to a list"
  (cl:list 'XYOffset-request
    (cl:cons ':x_offset (x_offset msg))
    (cl:cons ':y_offset (y_offset msg))
))
;//! \htmlinclude XYOffset-response.msg.html

(cl:defclass <XYOffset-response> (roslisp-msg-protocol:ros-message)
  ((received
    :reader received
    :initarg :received
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass XYOffset-response (<XYOffset-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <XYOffset-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'XYOffset-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-srv:<XYOffset-response> is deprecated: use icra_roboin_msgs-srv:XYOffset-response instead.")))

(cl:ensure-generic-function 'received-val :lambda-list '(m))
(cl:defmethod received-val ((m <XYOffset-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:received-val is deprecated.  Use icra_roboin_msgs-srv:received instead.")
  (received m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <XYOffset-response>) ostream)
  "Serializes a message object of type '<XYOffset-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'received) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <XYOffset-response>) istream)
  "Deserializes a message object of type '<XYOffset-response>"
    (cl:setf (cl:slot-value msg 'received) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<XYOffset-response>)))
  "Returns string type for a service object of type '<XYOffset-response>"
  "icra_roboin_msgs/XYOffsetResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'XYOffset-response)))
  "Returns string type for a service object of type 'XYOffset-response"
  "icra_roboin_msgs/XYOffsetResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<XYOffset-response>)))
  "Returns md5sum for a message object of type '<XYOffset-response>"
  "d8dc129d6dde9852a52847783f565dfc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'XYOffset-response)))
  "Returns md5sum for a message object of type 'XYOffset-response"
  "d8dc129d6dde9852a52847783f565dfc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<XYOffset-response>)))
  "Returns full string definition for message of type '<XYOffset-response>"
  (cl:format cl:nil "bool received~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'XYOffset-response)))
  "Returns full string definition for message of type 'XYOffset-response"
  (cl:format cl:nil "bool received~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <XYOffset-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <XYOffset-response>))
  "Converts a ROS message object to a list"
  (cl:list 'XYOffset-response
    (cl:cons ':received (received msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'XYOffset)))
  'XYOffset-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'XYOffset)))
  'XYOffset-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'XYOffset)))
  "Returns string type for a service object of type '<XYOffset>"
  "icra_roboin_msgs/XYOffset")