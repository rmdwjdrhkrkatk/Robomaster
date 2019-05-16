;; Auto-generated. Do not edit!


(when (boundp 'icra_roboin_msgs::BlackboardGeneralInfo)
  (if (not (find-package "ICRA_ROBOIN_MSGS"))
    (make-package "ICRA_ROBOIN_MSGS"))
  (shadow 'BlackboardGeneralInfo (find-package "ICRA_ROBOIN_MSGS")))
(unless (find-package "ICRA_ROBOIN_MSGS::BLACKBOARDGENERALINFO")
  (make-package "ICRA_ROBOIN_MSGS::BLACKBOARDGENERALINFO"))
(unless (find-package "ICRA_ROBOIN_MSGS::BLACKBOARDGENERALINFOREQUEST")
  (make-package "ICRA_ROBOIN_MSGS::BLACKBOARDGENERALINFOREQUEST"))
(unless (find-package "ICRA_ROBOIN_MSGS::BLACKBOARDGENERALINFORESPONSE")
  (make-package "ICRA_ROBOIN_MSGS::BLACKBOARDGENERALINFORESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass icra_roboin_msgs::BlackboardGeneralInfoRequest
  :super ros::object
  :slots (_stamp _request_sender _confirm ))

(defmethod icra_roboin_msgs::BlackboardGeneralInfoRequest
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:request_sender __request_sender) "")
    ((:confirm __confirm) nil)
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _request_sender (string __request_sender))
   (setq _confirm __confirm)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:request_sender
   (&optional __request_sender)
   (if __request_sender (setq _request_sender __request_sender)) _request_sender)
  (:confirm
   (&optional __confirm)
   (if __confirm (setq _confirm __confirm)) _confirm)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; string _request_sender
    4 (length _request_sender)
    ;; bool _confirm
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; string _request_sender
       (write-long (length _request_sender) s) (princ _request_sender s)
     ;; bool _confirm
       (if _confirm (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _request_sender
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _request_sender (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; bool _confirm
     (setq _confirm (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass icra_roboin_msgs::BlackboardGeneralInfoResponse
  :super ros::object
  :slots (_stamp _my_id _my_life _my_teamtype _robot_damage_type _robot_damage_armor _my_bonus_zone _my_hp _ally_life _enemy1_life _enemy2_life _enemy_bonus_zone _time_passed_from_start _last_buff_time _last_supply_time _enemy_last_buff_time _ammo _game_status _robot_bonus _supplier_status _game_result _my_pose _enemy_pose1 _enemy_pose2 _how_many_enemies_detected _is_enemy_1_detected _is_enemy_2_detected ))

(defmethod icra_roboin_msgs::BlackboardGeneralInfoResponse
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:my_id __my_id) 0)
    ((:my_life __my_life) 0)
    ((:my_teamtype __my_teamtype) 0)
    ((:robot_damage_type __robot_damage_type) 0)
    ((:robot_damage_armor __robot_damage_armor) 0)
    ((:my_bonus_zone __my_bonus_zone) 0)
    ((:my_hp __my_hp) 0)
    ((:ally_life __ally_life) 0)
    ((:enemy1_life __enemy1_life) 0)
    ((:enemy2_life __enemy2_life) 0)
    ((:enemy_bonus_zone __enemy_bonus_zone) 0)
    ((:time_passed_from_start __time_passed_from_start) 0)
    ((:last_buff_time __last_buff_time) 0)
    ((:last_supply_time __last_supply_time) 0)
    ((:enemy_last_buff_time __enemy_last_buff_time) 0)
    ((:ammo __ammo) 0)
    ((:game_status __game_status) 0)
    ((:robot_bonus __robot_bonus) 0)
    ((:supplier_status __supplier_status) 0)
    ((:game_result __game_result) 0)
    ((:my_pose __my_pose) (instance geometry_msgs::PoseStamped :init))
    ((:enemy_pose1 __enemy_pose1) (instance geometry_msgs::PoseStamped :init))
    ((:enemy_pose2 __enemy_pose2) (instance geometry_msgs::PoseStamped :init))
    ((:how_many_enemies_detected __how_many_enemies_detected) 0)
    ((:is_enemy_1_detected __is_enemy_1_detected) nil)
    ((:is_enemy_2_detected __is_enemy_2_detected) nil)
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _my_id (round __my_id))
   (setq _my_life (round __my_life))
   (setq _my_teamtype (round __my_teamtype))
   (setq _robot_damage_type (round __robot_damage_type))
   (setq _robot_damage_armor (round __robot_damage_armor))
   (setq _my_bonus_zone (round __my_bonus_zone))
   (setq _my_hp (round __my_hp))
   (setq _ally_life (round __ally_life))
   (setq _enemy1_life (round __enemy1_life))
   (setq _enemy2_life (round __enemy2_life))
   (setq _enemy_bonus_zone (round __enemy_bonus_zone))
   (setq _time_passed_from_start (round __time_passed_from_start))
   (setq _last_buff_time (round __last_buff_time))
   (setq _last_supply_time (round __last_supply_time))
   (setq _enemy_last_buff_time (round __enemy_last_buff_time))
   (setq _ammo (round __ammo))
   (setq _game_status (round __game_status))
   (setq _robot_bonus (round __robot_bonus))
   (setq _supplier_status (round __supplier_status))
   (setq _game_result (round __game_result))
   (setq _my_pose __my_pose)
   (setq _enemy_pose1 __enemy_pose1)
   (setq _enemy_pose2 __enemy_pose2)
   (setq _how_many_enemies_detected (round __how_many_enemies_detected))
   (setq _is_enemy_1_detected __is_enemy_1_detected)
   (setq _is_enemy_2_detected __is_enemy_2_detected)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:my_id
   (&optional __my_id)
   (if __my_id (setq _my_id __my_id)) _my_id)
  (:my_life
   (&optional __my_life)
   (if __my_life (setq _my_life __my_life)) _my_life)
  (:my_teamtype
   (&optional __my_teamtype)
   (if __my_teamtype (setq _my_teamtype __my_teamtype)) _my_teamtype)
  (:robot_damage_type
   (&optional __robot_damage_type)
   (if __robot_damage_type (setq _robot_damage_type __robot_damage_type)) _robot_damage_type)
  (:robot_damage_armor
   (&optional __robot_damage_armor)
   (if __robot_damage_armor (setq _robot_damage_armor __robot_damage_armor)) _robot_damage_armor)
  (:my_bonus_zone
   (&optional __my_bonus_zone)
   (if __my_bonus_zone (setq _my_bonus_zone __my_bonus_zone)) _my_bonus_zone)
  (:my_hp
   (&optional __my_hp)
   (if __my_hp (setq _my_hp __my_hp)) _my_hp)
  (:ally_life
   (&optional __ally_life)
   (if __ally_life (setq _ally_life __ally_life)) _ally_life)
  (:enemy1_life
   (&optional __enemy1_life)
   (if __enemy1_life (setq _enemy1_life __enemy1_life)) _enemy1_life)
  (:enemy2_life
   (&optional __enemy2_life)
   (if __enemy2_life (setq _enemy2_life __enemy2_life)) _enemy2_life)
  (:enemy_bonus_zone
   (&optional __enemy_bonus_zone)
   (if __enemy_bonus_zone (setq _enemy_bonus_zone __enemy_bonus_zone)) _enemy_bonus_zone)
  (:time_passed_from_start
   (&optional __time_passed_from_start)
   (if __time_passed_from_start (setq _time_passed_from_start __time_passed_from_start)) _time_passed_from_start)
  (:last_buff_time
   (&optional __last_buff_time)
   (if __last_buff_time (setq _last_buff_time __last_buff_time)) _last_buff_time)
  (:last_supply_time
   (&optional __last_supply_time)
   (if __last_supply_time (setq _last_supply_time __last_supply_time)) _last_supply_time)
  (:enemy_last_buff_time
   (&optional __enemy_last_buff_time)
   (if __enemy_last_buff_time (setq _enemy_last_buff_time __enemy_last_buff_time)) _enemy_last_buff_time)
  (:ammo
   (&optional __ammo)
   (if __ammo (setq _ammo __ammo)) _ammo)
  (:game_status
   (&optional __game_status)
   (if __game_status (setq _game_status __game_status)) _game_status)
  (:robot_bonus
   (&optional __robot_bonus)
   (if __robot_bonus (setq _robot_bonus __robot_bonus)) _robot_bonus)
  (:supplier_status
   (&optional __supplier_status)
   (if __supplier_status (setq _supplier_status __supplier_status)) _supplier_status)
  (:game_result
   (&optional __game_result)
   (if __game_result (setq _game_result __game_result)) _game_result)
  (:my_pose
   (&rest __my_pose)
   (if (keywordp (car __my_pose))
       (send* _my_pose __my_pose)
     (progn
       (if __my_pose (setq _my_pose (car __my_pose)))
       _my_pose)))
  (:enemy_pose1
   (&rest __enemy_pose1)
   (if (keywordp (car __enemy_pose1))
       (send* _enemy_pose1 __enemy_pose1)
     (progn
       (if __enemy_pose1 (setq _enemy_pose1 (car __enemy_pose1)))
       _enemy_pose1)))
  (:enemy_pose2
   (&rest __enemy_pose2)
   (if (keywordp (car __enemy_pose2))
       (send* _enemy_pose2 __enemy_pose2)
     (progn
       (if __enemy_pose2 (setq _enemy_pose2 (car __enemy_pose2)))
       _enemy_pose2)))
  (:how_many_enemies_detected
   (&optional __how_many_enemies_detected)
   (if __how_many_enemies_detected (setq _how_many_enemies_detected __how_many_enemies_detected)) _how_many_enemies_detected)
  (:is_enemy_1_detected
   (&optional __is_enemy_1_detected)
   (if __is_enemy_1_detected (setq _is_enemy_1_detected __is_enemy_1_detected)) _is_enemy_1_detected)
  (:is_enemy_2_detected
   (&optional __is_enemy_2_detected)
   (if __is_enemy_2_detected (setq _is_enemy_2_detected __is_enemy_2_detected)) _is_enemy_2_detected)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; int8 _my_id
    1
    ;; int8 _my_life
    1
    ;; int8 _my_teamtype
    1
    ;; int8 _robot_damage_type
    1
    ;; int8 _robot_damage_armor
    1
    ;; int8 _my_bonus_zone
    1
    ;; int8 _my_hp
    1
    ;; int8 _ally_life
    1
    ;; int8 _enemy1_life
    1
    ;; int8 _enemy2_life
    1
    ;; int8 _enemy_bonus_zone
    1
    ;; int32 _time_passed_from_start
    4
    ;; int32 _last_buff_time
    4
    ;; int32 _last_supply_time
    4
    ;; int32 _enemy_last_buff_time
    4
    ;; int8 _ammo
    1
    ;; int8 _game_status
    1
    ;; int8 _robot_bonus
    1
    ;; int8 _supplier_status
    1
    ;; int8 _game_result
    1
    ;; geometry_msgs/PoseStamped _my_pose
    (send _my_pose :serialization-length)
    ;; geometry_msgs/PoseStamped _enemy_pose1
    (send _enemy_pose1 :serialization-length)
    ;; geometry_msgs/PoseStamped _enemy_pose2
    (send _enemy_pose2 :serialization-length)
    ;; uint8 _how_many_enemies_detected
    1
    ;; bool _is_enemy_1_detected
    1
    ;; bool _is_enemy_2_detected
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; int8 _my_id
       (write-byte _my_id s)
     ;; int8 _my_life
       (write-byte _my_life s)
     ;; int8 _my_teamtype
       (write-byte _my_teamtype s)
     ;; int8 _robot_damage_type
       (write-byte _robot_damage_type s)
     ;; int8 _robot_damage_armor
       (write-byte _robot_damage_armor s)
     ;; int8 _my_bonus_zone
       (write-byte _my_bonus_zone s)
     ;; int8 _my_hp
       (write-byte _my_hp s)
     ;; int8 _ally_life
       (write-byte _ally_life s)
     ;; int8 _enemy1_life
       (write-byte _enemy1_life s)
     ;; int8 _enemy2_life
       (write-byte _enemy2_life s)
     ;; int8 _enemy_bonus_zone
       (write-byte _enemy_bonus_zone s)
     ;; int32 _time_passed_from_start
       (write-long _time_passed_from_start s)
     ;; int32 _last_buff_time
       (write-long _last_buff_time s)
     ;; int32 _last_supply_time
       (write-long _last_supply_time s)
     ;; int32 _enemy_last_buff_time
       (write-long _enemy_last_buff_time s)
     ;; int8 _ammo
       (write-byte _ammo s)
     ;; int8 _game_status
       (write-byte _game_status s)
     ;; int8 _robot_bonus
       (write-byte _robot_bonus s)
     ;; int8 _supplier_status
       (write-byte _supplier_status s)
     ;; int8 _game_result
       (write-byte _game_result s)
     ;; geometry_msgs/PoseStamped _my_pose
       (send _my_pose :serialize s)
     ;; geometry_msgs/PoseStamped _enemy_pose1
       (send _enemy_pose1 :serialize s)
     ;; geometry_msgs/PoseStamped _enemy_pose2
       (send _enemy_pose2 :serialize s)
     ;; uint8 _how_many_enemies_detected
       (write-byte _how_many_enemies_detected s)
     ;; bool _is_enemy_1_detected
       (if _is_enemy_1_detected (write-byte -1 s) (write-byte 0 s))
     ;; bool _is_enemy_2_detected
       (if _is_enemy_2_detected (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int8 _my_id
     (setq _my_id (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _my_id 127) (setq _my_id (- _my_id 256)))
   ;; int8 _my_life
     (setq _my_life (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _my_life 127) (setq _my_life (- _my_life 256)))
   ;; int8 _my_teamtype
     (setq _my_teamtype (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _my_teamtype 127) (setq _my_teamtype (- _my_teamtype 256)))
   ;; int8 _robot_damage_type
     (setq _robot_damage_type (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _robot_damage_type 127) (setq _robot_damage_type (- _robot_damage_type 256)))
   ;; int8 _robot_damage_armor
     (setq _robot_damage_armor (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _robot_damage_armor 127) (setq _robot_damage_armor (- _robot_damage_armor 256)))
   ;; int8 _my_bonus_zone
     (setq _my_bonus_zone (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _my_bonus_zone 127) (setq _my_bonus_zone (- _my_bonus_zone 256)))
   ;; int8 _my_hp
     (setq _my_hp (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _my_hp 127) (setq _my_hp (- _my_hp 256)))
   ;; int8 _ally_life
     (setq _ally_life (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _ally_life 127) (setq _ally_life (- _ally_life 256)))
   ;; int8 _enemy1_life
     (setq _enemy1_life (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enemy1_life 127) (setq _enemy1_life (- _enemy1_life 256)))
   ;; int8 _enemy2_life
     (setq _enemy2_life (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enemy2_life 127) (setq _enemy2_life (- _enemy2_life 256)))
   ;; int8 _enemy_bonus_zone
     (setq _enemy_bonus_zone (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _enemy_bonus_zone 127) (setq _enemy_bonus_zone (- _enemy_bonus_zone 256)))
   ;; int32 _time_passed_from_start
     (setq _time_passed_from_start (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _last_buff_time
     (setq _last_buff_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _last_supply_time
     (setq _last_supply_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _enemy_last_buff_time
     (setq _enemy_last_buff_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int8 _ammo
     (setq _ammo (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _ammo 127) (setq _ammo (- _ammo 256)))
   ;; int8 _game_status
     (setq _game_status (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _game_status 127) (setq _game_status (- _game_status 256)))
   ;; int8 _robot_bonus
     (setq _robot_bonus (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _robot_bonus 127) (setq _robot_bonus (- _robot_bonus 256)))
   ;; int8 _supplier_status
     (setq _supplier_status (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _supplier_status 127) (setq _supplier_status (- _supplier_status 256)))
   ;; int8 _game_result
     (setq _game_result (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _game_result 127) (setq _game_result (- _game_result 256)))
   ;; geometry_msgs/PoseStamped _my_pose
     (send _my_pose :deserialize buf ptr-) (incf ptr- (send _my_pose :serialization-length))
   ;; geometry_msgs/PoseStamped _enemy_pose1
     (send _enemy_pose1 :deserialize buf ptr-) (incf ptr- (send _enemy_pose1 :serialization-length))
   ;; geometry_msgs/PoseStamped _enemy_pose2
     (send _enemy_pose2 :deserialize buf ptr-) (incf ptr- (send _enemy_pose2 :serialization-length))
   ;; uint8 _how_many_enemies_detected
     (setq _how_many_enemies_detected (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; bool _is_enemy_1_detected
     (setq _is_enemy_1_detected (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _is_enemy_2_detected
     (setq _is_enemy_2_detected (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass icra_roboin_msgs::BlackboardGeneralInfo
  :super ros::object
  :slots ())

(setf (get icra_roboin_msgs::BlackboardGeneralInfo :md5sum-) "b163c0ce1011a983e5ca043d25ff9b1c")
(setf (get icra_roboin_msgs::BlackboardGeneralInfo :datatype-) "icra_roboin_msgs/BlackboardGeneralInfo")
(setf (get icra_roboin_msgs::BlackboardGeneralInfo :request) icra_roboin_msgs::BlackboardGeneralInfoRequest)
(setf (get icra_roboin_msgs::BlackboardGeneralInfo :response) icra_roboin_msgs::BlackboardGeneralInfoResponse)

(defmethod icra_roboin_msgs::BlackboardGeneralInfoRequest
  (:response () (instance icra_roboin_msgs::BlackboardGeneralInfoResponse :init)))

(setf (get icra_roboin_msgs::BlackboardGeneralInfoRequest :md5sum-) "b163c0ce1011a983e5ca043d25ff9b1c")
(setf (get icra_roboin_msgs::BlackboardGeneralInfoRequest :datatype-) "icra_roboin_msgs/BlackboardGeneralInfoRequest")
(setf (get icra_roboin_msgs::BlackboardGeneralInfoRequest :definition-)
      "time stamp
string request_sender
bool confirm
---
time stamp
int8 my_id
int8 my_life
int8 my_teamtype
int8 robot_damage_type
int8 robot_damage_armor
int8 my_bonus_zone
int8 my_hp
int8 ally_life
int8 enemy1_life
int8 enemy2_life
int8 enemy_bonus_zone
int32 time_passed_from_start
int32 last_buff_time
int32 last_supply_time
int32 enemy_last_buff_time
int8 ammo
int8 game_status
int8 robot_bonus
int8 supplier_status
int8 game_result
geometry_msgs/PoseStamped my_pose
geometry_msgs/PoseStamped enemy_pose1
geometry_msgs/PoseStamped enemy_pose2
uint8 how_many_enemies_detected
bool is_enemy_1_detected
bool is_enemy_2_detected







================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

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
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")

(setf (get icra_roboin_msgs::BlackboardGeneralInfoResponse :md5sum-) "b163c0ce1011a983e5ca043d25ff9b1c")
(setf (get icra_roboin_msgs::BlackboardGeneralInfoResponse :datatype-) "icra_roboin_msgs/BlackboardGeneralInfoResponse")
(setf (get icra_roboin_msgs::BlackboardGeneralInfoResponse :definition-)
      "time stamp
string request_sender
bool confirm
---
time stamp
int8 my_id
int8 my_life
int8 my_teamtype
int8 robot_damage_type
int8 robot_damage_armor
int8 my_bonus_zone
int8 my_hp
int8 ally_life
int8 enemy1_life
int8 enemy2_life
int8 enemy_bonus_zone
int32 time_passed_from_start
int32 last_buff_time
int32 last_supply_time
int32 enemy_last_buff_time
int8 ammo
int8 game_status
int8 robot_bonus
int8 supplier_status
int8 game_result
geometry_msgs/PoseStamped my_pose
geometry_msgs/PoseStamped enemy_pose1
geometry_msgs/PoseStamped enemy_pose2
uint8 how_many_enemies_detected
bool is_enemy_1_detected
bool is_enemy_2_detected







================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

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
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")



(provide :icra_roboin_msgs/BlackboardGeneralInfo "b163c0ce1011a983e5ca043d25ff9b1c")


