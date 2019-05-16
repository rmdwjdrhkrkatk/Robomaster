; Auto-generated. Do not edit!


(cl:in-package icra_roboin_msgs-msg)


;//! \htmlinclude YoloDetectionInfo.msg.html

(cl:defclass <YoloDetectionInfo> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (number_of_detection
    :reader number_of_detection
    :initarg :number_of_detection
    :type cl:fixnum
    :initform 0)
   (reserved
    :reader reserved
    :initarg :reserved
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (enemy_detected
    :reader enemy_detected
    :initarg :enemy_detected
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (angle_hori
    :reader angle_hori
    :initarg :angle_hori
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (angle_verti
    :reader angle_verti
    :initarg :angle_verti
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (Pixel_X
    :reader Pixel_X
    :initarg :Pixel_X
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (Pixel_Y
    :reader Pixel_Y
    :initarg :Pixel_Y
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (Pixel_width
    :reader Pixel_width
    :initarg :Pixel_width
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (Pixel_height
    :reader Pixel_height
    :initarg :Pixel_height
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (real_width
    :reader real_width
    :initarg :real_width
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (real_height
    :reader real_height
    :initarg :real_height
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0))
   (distance
    :reader distance
    :initarg :distance
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 3 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass YoloDetectionInfo (<YoloDetectionInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <YoloDetectionInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'YoloDetectionInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-msg:<YoloDetectionInfo> is deprecated: use icra_roboin_msgs-msg:YoloDetectionInfo instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:stamp-val is deprecated.  Use icra_roboin_msgs-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'number_of_detection-val :lambda-list '(m))
(cl:defmethod number_of_detection-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:number_of_detection-val is deprecated.  Use icra_roboin_msgs-msg:number_of_detection instead.")
  (number_of_detection m))

(cl:ensure-generic-function 'reserved-val :lambda-list '(m))
(cl:defmethod reserved-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:reserved-val is deprecated.  Use icra_roboin_msgs-msg:reserved instead.")
  (reserved m))

(cl:ensure-generic-function 'enemy_detected-val :lambda-list '(m))
(cl:defmethod enemy_detected-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:enemy_detected-val is deprecated.  Use icra_roboin_msgs-msg:enemy_detected instead.")
  (enemy_detected m))

(cl:ensure-generic-function 'angle_hori-val :lambda-list '(m))
(cl:defmethod angle_hori-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:angle_hori-val is deprecated.  Use icra_roboin_msgs-msg:angle_hori instead.")
  (angle_hori m))

(cl:ensure-generic-function 'angle_verti-val :lambda-list '(m))
(cl:defmethod angle_verti-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:angle_verti-val is deprecated.  Use icra_roboin_msgs-msg:angle_verti instead.")
  (angle_verti m))

(cl:ensure-generic-function 'Pixel_X-val :lambda-list '(m))
(cl:defmethod Pixel_X-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_X-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_X instead.")
  (Pixel_X m))

(cl:ensure-generic-function 'Pixel_Y-val :lambda-list '(m))
(cl:defmethod Pixel_Y-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_Y-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_Y instead.")
  (Pixel_Y m))

(cl:ensure-generic-function 'Pixel_width-val :lambda-list '(m))
(cl:defmethod Pixel_width-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_width-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_width instead.")
  (Pixel_width m))

(cl:ensure-generic-function 'Pixel_height-val :lambda-list '(m))
(cl:defmethod Pixel_height-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_height-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_height instead.")
  (Pixel_height m))

(cl:ensure-generic-function 'real_width-val :lambda-list '(m))
(cl:defmethod real_width-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:real_width-val is deprecated.  Use icra_roboin_msgs-msg:real_width instead.")
  (real_width m))

(cl:ensure-generic-function 'real_height-val :lambda-list '(m))
(cl:defmethod real_height-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:real_height-val is deprecated.  Use icra_roboin_msgs-msg:real_height instead.")
  (real_height m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <YoloDetectionInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:distance-val is deprecated.  Use icra_roboin_msgs-msg:distance instead.")
  (distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <YoloDetectionInfo>) ostream)
  "Serializes a message object of type '<YoloDetectionInfo>"
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'stamp) (cl:floor (cl:slot-value msg 'stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let* ((signed (cl:slot-value msg 'number_of_detection)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    ))
   (cl:slot-value msg 'reserved))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    ))
   (cl:slot-value msg 'enemy_detected))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'angle_hori))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'angle_verti))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'Pixel_X))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'Pixel_Y))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'Pixel_width))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'Pixel_height))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'real_width))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'real_height))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'distance))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <YoloDetectionInfo>) istream)
  "Deserializes a message object of type '<YoloDetectionInfo>"
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'number_of_detection) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  (cl:setf (cl:slot-value msg 'reserved) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'reserved)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))))
  (cl:setf (cl:slot-value msg 'enemy_detected) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'enemy_detected)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))))
  (cl:setf (cl:slot-value msg 'angle_hori) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'angle_hori)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'angle_verti) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'angle_verti)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'Pixel_X) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'Pixel_X)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'Pixel_Y) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'Pixel_Y)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'Pixel_width) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'Pixel_width)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'Pixel_height) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'Pixel_height)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'real_width) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'real_width)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'real_height) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'real_height)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'distance) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'distance)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<YoloDetectionInfo>)))
  "Returns string type for a message object of type '<YoloDetectionInfo>"
  "icra_roboin_msgs/YoloDetectionInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'YoloDetectionInfo)))
  "Returns string type for a message object of type 'YoloDetectionInfo"
  "icra_roboin_msgs/YoloDetectionInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<YoloDetectionInfo>)))
  "Returns md5sum for a message object of type '<YoloDetectionInfo>"
  "8c9b3f0e444e2f6af4be1632d58bee33")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'YoloDetectionInfo)))
  "Returns md5sum for a message object of type 'YoloDetectionInfo"
  "8c9b3f0e444e2f6af4be1632d58bee33")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<YoloDetectionInfo>)))
  "Returns full string definition for message of type '<YoloDetectionInfo>"
  (cl:format cl:nil "time stamp~%int16 number_of_detection~%int8[3] reserved~%int8[3] enemy_detected~%int16[3] angle_hori~%int16[3] angle_verti~%int16[3] Pixel_X~%int16[3] Pixel_Y~%int16[3] Pixel_width~%int16[3] Pixel_height~%int16[3] real_width~%int16[3] real_height~%int16[3] distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'YoloDetectionInfo)))
  "Returns full string definition for message of type 'YoloDetectionInfo"
  (cl:format cl:nil "time stamp~%int16 number_of_detection~%int8[3] reserved~%int8[3] enemy_detected~%int16[3] angle_hori~%int16[3] angle_verti~%int16[3] Pixel_X~%int16[3] Pixel_Y~%int16[3] Pixel_width~%int16[3] Pixel_height~%int16[3] real_width~%int16[3] real_height~%int16[3] distance~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <YoloDetectionInfo>))
  (cl:+ 0
     8
     2
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'reserved) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'enemy_detected) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'angle_hori) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'angle_verti) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Pixel_X) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Pixel_Y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Pixel_width) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Pixel_height) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'real_width) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'real_height) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'distance) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <YoloDetectionInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'YoloDetectionInfo
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':number_of_detection (number_of_detection msg))
    (cl:cons ':reserved (reserved msg))
    (cl:cons ':enemy_detected (enemy_detected msg))
    (cl:cons ':angle_hori (angle_hori msg))
    (cl:cons ':angle_verti (angle_verti msg))
    (cl:cons ':Pixel_X (Pixel_X msg))
    (cl:cons ':Pixel_Y (Pixel_Y msg))
    (cl:cons ':Pixel_width (Pixel_width msg))
    (cl:cons ':Pixel_height (Pixel_height msg))
    (cl:cons ':real_width (real_width msg))
    (cl:cons ':real_height (real_height msg))
    (cl:cons ':distance (distance msg))
))
