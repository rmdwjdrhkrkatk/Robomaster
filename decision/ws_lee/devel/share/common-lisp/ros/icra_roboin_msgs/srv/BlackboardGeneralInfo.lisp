; Auto-generated. Do not edit!


(cl:in-package icra_roboin_msgs-srv)


;//! \htmlinclude BlackboardGeneralInfo-request.msg.html

(cl:defclass <BlackboardGeneralInfo-request> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (request_sender
    :reader request_sender
    :initarg :request_sender
    :type cl:string
    :initform "")
   (confirm
    :reader confirm
    :initarg :confirm
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass BlackboardGeneralInfo-request (<BlackboardGeneralInfo-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BlackboardGeneralInfo-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BlackboardGeneralInfo-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-srv:<BlackboardGeneralInfo-request> is deprecated: use icra_roboin_msgs-srv:BlackboardGeneralInfo-request instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <BlackboardGeneralInfo-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:stamp-val is deprecated.  Use icra_roboin_msgs-srv:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'request_sender-val :lambda-list '(m))
(cl:defmethod request_sender-val ((m <BlackboardGeneralInfo-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:request_sender-val is deprecated.  Use icra_roboin_msgs-srv:request_sender instead.")
  (request_sender m))

(cl:ensure-generic-function 'confirm-val :lambda-list '(m))
(cl:defmethod confirm-val ((m <BlackboardGeneralInfo-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:confirm-val is deprecated.  Use icra_roboin_msgs-srv:confirm instead.")
  (confirm m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BlackboardGeneralInfo-request>) ostream)
  "Serializes a message object of type '<BlackboardGeneralInfo-request>"
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
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'request_sender))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'request_sender))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'confirm) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BlackboardGeneralInfo-request>) istream)
  "Deserializes a message object of type '<BlackboardGeneralInfo-request>"
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
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'request_sender) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'request_sender) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'confirm) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BlackboardGeneralInfo-request>)))
  "Returns string type for a service object of type '<BlackboardGeneralInfo-request>"
  "icra_roboin_msgs/BlackboardGeneralInfoRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BlackboardGeneralInfo-request)))
  "Returns string type for a service object of type 'BlackboardGeneralInfo-request"
  "icra_roboin_msgs/BlackboardGeneralInfoRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BlackboardGeneralInfo-request>)))
  "Returns md5sum for a message object of type '<BlackboardGeneralInfo-request>"
  "b163c0ce1011a983e5ca043d25ff9b1c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BlackboardGeneralInfo-request)))
  "Returns md5sum for a message object of type 'BlackboardGeneralInfo-request"
  "b163c0ce1011a983e5ca043d25ff9b1c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BlackboardGeneralInfo-request>)))
  "Returns full string definition for message of type '<BlackboardGeneralInfo-request>"
  (cl:format cl:nil "time stamp~%string request_sender~%bool confirm~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BlackboardGeneralInfo-request)))
  "Returns full string definition for message of type 'BlackboardGeneralInfo-request"
  (cl:format cl:nil "time stamp~%string request_sender~%bool confirm~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BlackboardGeneralInfo-request>))
  (cl:+ 0
     8
     4 (cl:length (cl:slot-value msg 'request_sender))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BlackboardGeneralInfo-request>))
  "Converts a ROS message object to a list"
  (cl:list 'BlackboardGeneralInfo-request
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':request_sender (request_sender msg))
    (cl:cons ':confirm (confirm msg))
))
;//! \htmlinclude BlackboardGeneralInfo-response.msg.html

(cl:defclass <BlackboardGeneralInfo-response> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (my_id
    :reader my_id
    :initarg :my_id
    :type cl:fixnum
    :initform 0)
   (my_life
    :reader my_life
    :initarg :my_life
    :type cl:fixnum
    :initform 0)
   (my_teamtype
    :reader my_teamtype
    :initarg :my_teamtype
    :type cl:fixnum
    :initform 0)
   (robot_damage_type
    :reader robot_damage_type
    :initarg :robot_damage_type
    :type cl:fixnum
    :initform 0)
   (robot_damage_armor
    :reader robot_damage_armor
    :initarg :robot_damage_armor
    :type cl:fixnum
    :initform 0)
   (my_bonus_zone
    :reader my_bonus_zone
    :initarg :my_bonus_zone
    :type cl:fixnum
    :initform 0)
   (my_hp
    :reader my_hp
    :initarg :my_hp
    :type cl:fixnum
    :initform 0)
   (ally_life
    :reader ally_life
    :initarg :ally_life
    :type cl:fixnum
    :initform 0)
   (enemy1_life
    :reader enemy1_life
    :initarg :enemy1_life
    :type cl:fixnum
    :initform 0)
   (enemy2_life
    :reader enemy2_life
    :initarg :enemy2_life
    :type cl:fixnum
    :initform 0)
   (enemy_bonus_zone
    :reader enemy_bonus_zone
    :initarg :enemy_bonus_zone
    :type cl:fixnum
    :initform 0)
   (time_passed_from_start
    :reader time_passed_from_start
    :initarg :time_passed_from_start
    :type cl:integer
    :initform 0)
   (last_buff_time
    :reader last_buff_time
    :initarg :last_buff_time
    :type cl:integer
    :initform 0)
   (last_supply_time
    :reader last_supply_time
    :initarg :last_supply_time
    :type cl:integer
    :initform 0)
   (enemy_last_buff_time
    :reader enemy_last_buff_time
    :initarg :enemy_last_buff_time
    :type cl:integer
    :initform 0)
   (ammo
    :reader ammo
    :initarg :ammo
    :type cl:fixnum
    :initform 0)
   (game_status
    :reader game_status
    :initarg :game_status
    :type cl:fixnum
    :initform 0)
   (robot_bonus
    :reader robot_bonus
    :initarg :robot_bonus
    :type cl:fixnum
    :initform 0)
   (supplier_status
    :reader supplier_status
    :initarg :supplier_status
    :type cl:fixnum
    :initform 0)
   (game_result
    :reader game_result
    :initarg :game_result
    :type cl:fixnum
    :initform 0)
   (my_pose
    :reader my_pose
    :initarg :my_pose
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped))
   (enemy_pose1
    :reader enemy_pose1
    :initarg :enemy_pose1
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped))
   (enemy_pose2
    :reader enemy_pose2
    :initarg :enemy_pose2
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped))
   (how_many_enemies_detected
    :reader how_many_enemies_detected
    :initarg :how_many_enemies_detected
    :type cl:fixnum
    :initform 0)
   (is_enemy_1_detected
    :reader is_enemy_1_detected
    :initarg :is_enemy_1_detected
    :type cl:boolean
    :initform cl:nil)
   (is_enemy_2_detected
    :reader is_enemy_2_detected
    :initarg :is_enemy_2_detected
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass BlackboardGeneralInfo-response (<BlackboardGeneralInfo-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BlackboardGeneralInfo-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BlackboardGeneralInfo-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name icra_roboin_msgs-srv:<BlackboardGeneralInfo-response> is deprecated: use icra_roboin_msgs-srv:BlackboardGeneralInfo-response instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:stamp-val is deprecated.  Use icra_roboin_msgs-srv:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'my_id-val :lambda-list '(m))
(cl:defmethod my_id-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:my_id-val is deprecated.  Use icra_roboin_msgs-srv:my_id instead.")
  (my_id m))

(cl:ensure-generic-function 'my_life-val :lambda-list '(m))
(cl:defmethod my_life-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:my_life-val is deprecated.  Use icra_roboin_msgs-srv:my_life instead.")
  (my_life m))

(cl:ensure-generic-function 'my_teamtype-val :lambda-list '(m))
(cl:defmethod my_teamtype-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:my_teamtype-val is deprecated.  Use icra_roboin_msgs-srv:my_teamtype instead.")
  (my_teamtype m))

(cl:ensure-generic-function 'robot_damage_type-val :lambda-list '(m))
(cl:defmethod robot_damage_type-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:robot_damage_type-val is deprecated.  Use icra_roboin_msgs-srv:robot_damage_type instead.")
  (robot_damage_type m))

(cl:ensure-generic-function 'robot_damage_armor-val :lambda-list '(m))
(cl:defmethod robot_damage_armor-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:robot_damage_armor-val is deprecated.  Use icra_roboin_msgs-srv:robot_damage_armor instead.")
  (robot_damage_armor m))

(cl:ensure-generic-function 'my_bonus_zone-val :lambda-list '(m))
(cl:defmethod my_bonus_zone-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:my_bonus_zone-val is deprecated.  Use icra_roboin_msgs-srv:my_bonus_zone instead.")
  (my_bonus_zone m))

(cl:ensure-generic-function 'my_hp-val :lambda-list '(m))
(cl:defmethod my_hp-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:my_hp-val is deprecated.  Use icra_roboin_msgs-srv:my_hp instead.")
  (my_hp m))

(cl:ensure-generic-function 'ally_life-val :lambda-list '(m))
(cl:defmethod ally_life-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:ally_life-val is deprecated.  Use icra_roboin_msgs-srv:ally_life instead.")
  (ally_life m))

(cl:ensure-generic-function 'enemy1_life-val :lambda-list '(m))
(cl:defmethod enemy1_life-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:enemy1_life-val is deprecated.  Use icra_roboin_msgs-srv:enemy1_life instead.")
  (enemy1_life m))

(cl:ensure-generic-function 'enemy2_life-val :lambda-list '(m))
(cl:defmethod enemy2_life-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:enemy2_life-val is deprecated.  Use icra_roboin_msgs-srv:enemy2_life instead.")
  (enemy2_life m))

(cl:ensure-generic-function 'enemy_bonus_zone-val :lambda-list '(m))
(cl:defmethod enemy_bonus_zone-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:enemy_bonus_zone-val is deprecated.  Use icra_roboin_msgs-srv:enemy_bonus_zone instead.")
  (enemy_bonus_zone m))

(cl:ensure-generic-function 'time_passed_from_start-val :lambda-list '(m))
(cl:defmethod time_passed_from_start-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:time_passed_from_start-val is deprecated.  Use icra_roboin_msgs-srv:time_passed_from_start instead.")
  (time_passed_from_start m))

(cl:ensure-generic-function 'last_buff_time-val :lambda-list '(m))
(cl:defmethod last_buff_time-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:last_buff_time-val is deprecated.  Use icra_roboin_msgs-srv:last_buff_time instead.")
  (last_buff_time m))

(cl:ensure-generic-function 'last_supply_time-val :lambda-list '(m))
(cl:defmethod last_supply_time-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:last_supply_time-val is deprecated.  Use icra_roboin_msgs-srv:last_supply_time instead.")
  (last_supply_time m))

(cl:ensure-generic-function 'enemy_last_buff_time-val :lambda-list '(m))
(cl:defmethod enemy_last_buff_time-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:enemy_last_buff_time-val is deprecated.  Use icra_roboin_msgs-srv:enemy_last_buff_time instead.")
  (enemy_last_buff_time m))

(cl:ensure-generic-function 'ammo-val :lambda-list '(m))
(cl:defmethod ammo-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:ammo-val is deprecated.  Use icra_roboin_msgs-srv:ammo instead.")
  (ammo m))

(cl:ensure-generic-function 'game_status-val :lambda-list '(m))
(cl:defmethod game_status-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:game_status-val is deprecated.  Use icra_roboin_msgs-srv:game_status instead.")
  (game_status m))

(cl:ensure-generic-function 'robot_bonus-val :lambda-list '(m))
(cl:defmethod robot_bonus-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:robot_bonus-val is deprecated.  Use icra_roboin_msgs-srv:robot_bonus instead.")
  (robot_bonus m))

(cl:ensure-generic-function 'supplier_status-val :lambda-list '(m))
(cl:defmethod supplier_status-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:supplier_status-val is deprecated.  Use icra_roboin_msgs-srv:supplier_status instead.")
  (supplier_status m))

(cl:ensure-generic-function 'game_result-val :lambda-list '(m))
(cl:defmethod game_result-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:game_result-val is deprecated.  Use icra_roboin_msgs-srv:game_result instead.")
  (game_result m))

(cl:ensure-generic-function 'my_pose-val :lambda-list '(m))
(cl:defmethod my_pose-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:my_pose-val is deprecated.  Use icra_roboin_msgs-srv:my_pose instead.")
  (my_pose m))

(cl:ensure-generic-function 'enemy_pose1-val :lambda-list '(m))
(cl:defmethod enemy_pose1-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:enemy_pose1-val is deprecated.  Use icra_roboin_msgs-srv:enemy_pose1 instead.")
  (enemy_pose1 m))

(cl:ensure-generic-function 'enemy_pose2-val :lambda-list '(m))
(cl:defmethod enemy_pose2-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:enemy_pose2-val is deprecated.  Use icra_roboin_msgs-srv:enemy_pose2 instead.")
  (enemy_pose2 m))

(cl:ensure-generic-function 'how_many_enemies_detected-val :lambda-list '(m))
(cl:defmethod how_many_enemies_detected-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:how_many_enemies_detected-val is deprecated.  Use icra_roboin_msgs-srv:how_many_enemies_detected instead.")
  (how_many_enemies_detected m))

(cl:ensure-generic-function 'is_enemy_1_detected-val :lambda-list '(m))
(cl:defmethod is_enemy_1_detected-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:is_enemy_1_detected-val is deprecated.  Use icra_roboin_msgs-srv:is_enemy_1_detected instead.")
  (is_enemy_1_detected m))

(cl:ensure-generic-function 'is_enemy_2_detected-val :lambda-list '(m))
(cl:defmethod is_enemy_2_detected-val ((m <BlackboardGeneralInfo-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader icra_roboin_msgs-srv:is_enemy_2_detected-val is deprecated.  Use icra_roboin_msgs-srv:is_enemy_2_detected instead.")
  (is_enemy_2_detected m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BlackboardGeneralInfo-response>) ostream)
  "Serializes a message object of type '<BlackboardGeneralInfo-response>"
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
  (cl:let* ((signed (cl:slot-value msg 'my_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'my_life)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'my_teamtype)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_damage_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_damage_armor)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'my_bonus_zone)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'my_hp)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ally_life)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'enemy1_life)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'enemy2_life)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'enemy_bonus_zone)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'time_passed_from_start)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'last_buff_time)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'last_supply_time)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'enemy_last_buff_time)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ammo)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'game_status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'robot_bonus)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'supplier_status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'game_result)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'my_pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'enemy_pose1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'enemy_pose2) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'how_many_enemies_detected)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_enemy_1_detected) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_enemy_2_detected) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BlackboardGeneralInfo-response>) istream)
  "Deserializes a message object of type '<BlackboardGeneralInfo-response>"
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
      (cl:setf (cl:slot-value msg 'my_id) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'my_life) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'my_teamtype) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_damage_type) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_damage_armor) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'my_bonus_zone) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'my_hp) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ally_life) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enemy1_life) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enemy2_life) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enemy_bonus_zone) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'time_passed_from_start) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'last_buff_time) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'last_supply_time) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'enemy_last_buff_time) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ammo) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'game_status) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'robot_bonus) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'supplier_status) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'game_result) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'my_pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'enemy_pose1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'enemy_pose2) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'how_many_enemies_detected)) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'is_enemy_1_detected) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_enemy_2_detected) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BlackboardGeneralInfo-response>)))
  "Returns string type for a service object of type '<BlackboardGeneralInfo-response>"
  "icra_roboin_msgs/BlackboardGeneralInfoResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BlackboardGeneralInfo-response)))
  "Returns string type for a service object of type 'BlackboardGeneralInfo-response"
  "icra_roboin_msgs/BlackboardGeneralInfoResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BlackboardGeneralInfo-response>)))
  "Returns md5sum for a message object of type '<BlackboardGeneralInfo-response>"
  "b163c0ce1011a983e5ca043d25ff9b1c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BlackboardGeneralInfo-response)))
  "Returns md5sum for a message object of type 'BlackboardGeneralInfo-response"
  "b163c0ce1011a983e5ca043d25ff9b1c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BlackboardGeneralInfo-response>)))
  "Returns full string definition for message of type '<BlackboardGeneralInfo-response>"
  (cl:format cl:nil "time stamp~%int8 my_id~%int8 my_life~%int8 my_teamtype~%int8 robot_damage_type~%int8 robot_damage_armor~%int8 my_bonus_zone~%int8 my_hp~%int8 ally_life~%int8 enemy1_life~%int8 enemy2_life~%int8 enemy_bonus_zone~%int32 time_passed_from_start~%int32 last_buff_time~%int32 last_supply_time~%int32 enemy_last_buff_time~%int8 ammo~%int8 game_status~%int8 robot_bonus~%int8 supplier_status~%int8 game_result~%geometry_msgs/PoseStamped my_pose~%geometry_msgs/PoseStamped enemy_pose1~%geometry_msgs/PoseStamped enemy_pose2~%uint8 how_many_enemies_detected~%bool is_enemy_1_detected~%bool is_enemy_2_detected~%~%~%~%~%~%~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BlackboardGeneralInfo-response)))
  "Returns full string definition for message of type 'BlackboardGeneralInfo-response"
  (cl:format cl:nil "time stamp~%int8 my_id~%int8 my_life~%int8 my_teamtype~%int8 robot_damage_type~%int8 robot_damage_armor~%int8 my_bonus_zone~%int8 my_hp~%int8 ally_life~%int8 enemy1_life~%int8 enemy2_life~%int8 enemy_bonus_zone~%int32 time_passed_from_start~%int32 last_buff_time~%int32 last_supply_time~%int32 enemy_last_buff_time~%int8 ammo~%int8 game_status~%int8 robot_bonus~%int8 supplier_status~%int8 game_result~%geometry_msgs/PoseStamped my_pose~%geometry_msgs/PoseStamped enemy_pose1~%geometry_msgs/PoseStamped enemy_pose2~%uint8 how_many_enemies_detected~%bool is_enemy_1_detected~%bool is_enemy_2_detected~%~%~%~%~%~%~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BlackboardGeneralInfo-response>))
  (cl:+ 0
     8
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     1
     4
     4
     4
     4
     1
     1
     1
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'my_pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'enemy_pose1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'enemy_pose2))
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BlackboardGeneralInfo-response>))
  "Converts a ROS message object to a list"
  (cl:list 'BlackboardGeneralInfo-response
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':my_id (my_id msg))
    (cl:cons ':my_life (my_life msg))
    (cl:cons ':my_teamtype (my_teamtype msg))
    (cl:cons ':robot_damage_type (robot_damage_type msg))
    (cl:cons ':robot_damage_armor (robot_damage_armor msg))
    (cl:cons ':my_bonus_zone (my_bonus_zone msg))
    (cl:cons ':my_hp (my_hp msg))
    (cl:cons ':ally_life (ally_life msg))
    (cl:cons ':enemy1_life (enemy1_life msg))
    (cl:cons ':enemy2_life (enemy2_life msg))
    (cl:cons ':enemy_bonus_zone (enemy_bonus_zone msg))
    (cl:cons ':time_passed_from_start (time_passed_from_start msg))
    (cl:cons ':last_buff_time (last_buff_time msg))
    (cl:cons ':last_supply_time (last_supply_time msg))
    (cl:cons ':enemy_last_buff_time (enemy_last_buff_time msg))
    (cl:cons ':ammo (ammo msg))
    (cl:cons ':game_status (game_status msg))
    (cl:cons ':robot_bonus (robot_bonus msg))
    (cl:cons ':supplier_status (supplier_status msg))
    (cl:cons ':game_result (game_result msg))
    (cl:cons ':my_pose (my_pose msg))
    (cl:cons ':enemy_pose1 (enemy_pose1 msg))
    (cl:cons ':enemy_pose2 (enemy_pose2 msg))
    (cl:cons ':how_many_enemies_detected (how_many_enemies_detected msg))
    (cl:cons ':is_enemy_1_detected (is_enemy_1_detected msg))
    (cl:cons ':is_enemy_2_detected (is_enemy_2_detected msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'BlackboardGeneralInfo)))
  'BlackboardGeneralInfo-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'BlackboardGeneralInfo)))
  'BlackboardGeneralInfo-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BlackboardGeneralInfo)))
  "Returns string type for a service object of type '<BlackboardGeneralInfo>"
  "icra_roboin_msgs/BlackboardGeneralInfo")