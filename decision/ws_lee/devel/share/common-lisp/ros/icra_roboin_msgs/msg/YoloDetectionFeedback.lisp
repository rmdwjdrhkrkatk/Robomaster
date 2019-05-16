; Auto-generated. Do not edit!


(cl:in-package icra_roboin_msgs-msg)


;//! \htmlinclude YoloDetectionFeedback.msg.html

(cl:defclass <YoloDetectionFeedback> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (infochecker
    :reader infochecker
    :initarg :infochecker
    :type cl:fixnum
    :initform 0)
   (enemy
    :reader enemy
    :initarg :enemy
    :type cl:fixnum
    :initform 0)
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

(cl:defclass YoloDetectionFeedback (<YoloDetectionFeedback>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <YoloDetectionFeedback>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'YoloDetectionFeedback)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-msg:<YoloDetectionFeedback> is deprecated: use icra_roboin_msgs-msg:YoloDetectionFeedback instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:stamp-val is deprecated.  Use icra_roboin_msgs-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'infochecker-val :lambda-list '(m))
(cl:defmethod infochecker-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:infochecker-val is deprecated.  Use icra_roboin_msgs-msg:infochecker instead.")
  (infochecker m))

(cl:ensure-generic-function 'enemy-val :lambda-list '(m))
(cl:defmethod enemy-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:enemy-val is deprecated.  Use icra_roboin_msgs-msg:enemy instead.")
  (enemy m))

(cl:ensure-generic-function 'angle_hori-val :lambda-list '(m))
(cl:defmethod angle_hori-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:angle_hori-val is deprecated.  Use icra_roboin_msgs-msg:angle_hori instead.")
  (angle_hori m))

(cl:ensure-generic-function 'angle_verti-val :lambda-list '(m))
(cl:defmethod angle_verti-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:angle_verti-val is deprecated.  Use icra_roboin_msgs-msg:angle_verti instead.")
  (angle_verti m))

(cl:ensure-generic-function 'Pixel_X-val :lambda-list '(m))
(cl:defmethod Pixel_X-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_X-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_X instead.")
  (Pixel_X m))

(cl:ensure-generic-function 'Pixel_Y-val :lambda-list '(m))
(cl:defmethod Pixel_Y-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_Y-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_Y instead.")
  (Pixel_Y m))

(cl:ensure-generic-function 'Pixel_width-val :lambda-list '(m))
(cl:defmethod Pixel_width-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_width-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_width instead.")
  (Pixel_width m))

(cl:ensure-generic-function 'Pixel_height-val :lambda-list '(m))
(cl:defmethod Pixel_height-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:Pixel_height-val is deprecated.  Use icra_roboin_msgs-msg:Pixel_height instead.")
  (Pixel_height m))

(cl:ensure-generic-function 'real_width-val :lambda-list '(m))
(cl:defmethod real_width-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:real_width-val is deprecated.  Use icra_roboin_msgs-msg:real_width instead.")
  (real_width m))

(cl:ensure-generic-function 'real_height-val :lambda-list '(m))
(cl:defmethod real_height-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:real_height-val is deprecated.  Use icra_roboin_msgs-msg:real_height instead.")
  (real_height m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <YoloDetectionFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-msg:distance-val is deprecated.  Use icra_roboin_msgs-msg:distance instead.")
  (distance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <YoloDetectionFeedback>) ostream)
  "Serializes a message object of type '<YoloDetectionFeedback>"
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
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'infochecker)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'enemy)) ostream)
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <YoloDetectionFeedback>) istream)
  "Deserializes a message object of type '<YoloDetectionFeedback>"
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
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'infochecker)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'enemy)) (cl:read-byte istream))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<YoloDetectionFeedback>)))
  "Returns string type for a message object of type '<YoloDetectionFeedback>"
  "icra_roboin_msgs/YoloDetectionFeedback")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'YoloDetectionFeedback)))
  "Returns string type for a message object of type 'YoloDetectionFeedback"
  "icra_roboin_msgs/YoloDetectionFeedback")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<YoloDetectionFeedback>)))
  "Returns md5sum for a message object of type '<YoloDetectionFeedback>"
  "264543f7a1172d61963435fe8085999c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'YoloDetectionFeedback)))
  "Returns md5sum for a message object of type 'YoloDetectionFeedback"
  "264543f7a1172d61963435fe8085999c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<YoloDetectionFeedback>)))
  "Returns full string definition for message of type '<YoloDetectionFeedback>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#feedback~%time stamp~%uint8 infochecker~%uint8 enemy~%int16[3] angle_hori~%int16[3] angle_verti~%int16[3] Pixel_X~%int16[3] Pixel_Y~%int16[3] Pixel_width~%int16[3] Pixel_height~%int16[3] real_width~%int16[3] real_height~%int16[3] distance~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'YoloDetectionFeedback)))
  "Returns full string definition for message of type 'YoloDetectionFeedback"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#feedback~%time stamp~%uint8 infochecker~%uint8 enemy~%int16[3] angle_hori~%int16[3] angle_verti~%int16[3] Pixel_X~%int16[3] Pixel_Y~%int16[3] Pixel_width~%int16[3] Pixel_height~%int16[3] real_width~%int16[3] real_height~%int16[3] distance~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <YoloDetectionFeedback>))
  (cl:+ 0
     8
     1
     1
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
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <YoloDetectionFeedback>))
  "Converts a ROS message object to a list"
  (cl:list 'YoloDetectionFeedback
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':infochecker (infochecker msg))
    (cl:cons ':enemy (enemy msg))
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
