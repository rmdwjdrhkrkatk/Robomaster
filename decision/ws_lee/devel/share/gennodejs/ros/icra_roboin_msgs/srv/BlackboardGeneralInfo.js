// Auto-generated. Do not edit!

// (in-package icra_roboin_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class BlackboardGeneralInfoRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.request_sender = null;
      this.confirm = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('request_sender')) {
        this.request_sender = initObj.request_sender
      }
      else {
        this.request_sender = '';
      }
      if (initObj.hasOwnProperty('confirm')) {
        this.confirm = initObj.confirm
      }
      else {
        this.confirm = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BlackboardGeneralInfoRequest
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [request_sender]
    bufferOffset = _serializer.string(obj.request_sender, buffer, bufferOffset);
    // Serialize message field [confirm]
    bufferOffset = _serializer.bool(obj.confirm, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BlackboardGeneralInfoRequest
    let len;
    let data = new BlackboardGeneralInfoRequest(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [request_sender]
    data.request_sender = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [confirm]
    data.confirm = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.request_sender.length;
    return length + 13;
  }

  static datatype() {
    // Returns string type for a service object
    return 'icra_roboin_msgs/BlackboardGeneralInfoRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '66a57ffbb7b0191a46e5cac0c5adf55b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    string request_sender
    bool confirm
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BlackboardGeneralInfoRequest(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.request_sender !== undefined) {
      resolved.request_sender = msg.request_sender;
    }
    else {
      resolved.request_sender = ''
    }

    if (msg.confirm !== undefined) {
      resolved.confirm = msg.confirm;
    }
    else {
      resolved.confirm = false
    }

    return resolved;
    }
};

class BlackboardGeneralInfoResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.my_id = null;
      this.my_life = null;
      this.my_teamtype = null;
      this.robot_damage_type = null;
      this.robot_damage_armor = null;
      this.my_bonus_zone = null;
      this.my_hp = null;
      this.ally_life = null;
      this.enemy1_life = null;
      this.enemy2_life = null;
      this.enemy_bonus_zone = null;
      this.time_passed_from_start = null;
      this.last_buff_time = null;
      this.last_supply_time = null;
      this.enemy_last_buff_time = null;
      this.ammo = null;
      this.game_status = null;
      this.robot_bonus = null;
      this.supplier_status = null;
      this.game_result = null;
      this.my_pose = null;
      this.enemy_pose1 = null;
      this.enemy_pose2 = null;
      this.how_many_enemies_detected = null;
      this.is_enemy_1_detected = null;
      this.is_enemy_2_detected = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('my_id')) {
        this.my_id = initObj.my_id
      }
      else {
        this.my_id = 0;
      }
      if (initObj.hasOwnProperty('my_life')) {
        this.my_life = initObj.my_life
      }
      else {
        this.my_life = 0;
      }
      if (initObj.hasOwnProperty('my_teamtype')) {
        this.my_teamtype = initObj.my_teamtype
      }
      else {
        this.my_teamtype = 0;
      }
      if (initObj.hasOwnProperty('robot_damage_type')) {
        this.robot_damage_type = initObj.robot_damage_type
      }
      else {
        this.robot_damage_type = 0;
      }
      if (initObj.hasOwnProperty('robot_damage_armor')) {
        this.robot_damage_armor = initObj.robot_damage_armor
      }
      else {
        this.robot_damage_armor = 0;
      }
      if (initObj.hasOwnProperty('my_bonus_zone')) {
        this.my_bonus_zone = initObj.my_bonus_zone
      }
      else {
        this.my_bonus_zone = 0;
      }
      if (initObj.hasOwnProperty('my_hp')) {
        this.my_hp = initObj.my_hp
      }
      else {
        this.my_hp = 0;
      }
      if (initObj.hasOwnProperty('ally_life')) {
        this.ally_life = initObj.ally_life
      }
      else {
        this.ally_life = 0;
      }
      if (initObj.hasOwnProperty('enemy1_life')) {
        this.enemy1_life = initObj.enemy1_life
      }
      else {
        this.enemy1_life = 0;
      }
      if (initObj.hasOwnProperty('enemy2_life')) {
        this.enemy2_life = initObj.enemy2_life
      }
      else {
        this.enemy2_life = 0;
      }
      if (initObj.hasOwnProperty('enemy_bonus_zone')) {
        this.enemy_bonus_zone = initObj.enemy_bonus_zone
      }
      else {
        this.enemy_bonus_zone = 0;
      }
      if (initObj.hasOwnProperty('time_passed_from_start')) {
        this.time_passed_from_start = initObj.time_passed_from_start
      }
      else {
        this.time_passed_from_start = 0;
      }
      if (initObj.hasOwnProperty('last_buff_time')) {
        this.last_buff_time = initObj.last_buff_time
      }
      else {
        this.last_buff_time = 0;
      }
      if (initObj.hasOwnProperty('last_supply_time')) {
        this.last_supply_time = initObj.last_supply_time
      }
      else {
        this.last_supply_time = 0;
      }
      if (initObj.hasOwnProperty('enemy_last_buff_time')) {
        this.enemy_last_buff_time = initObj.enemy_last_buff_time
      }
      else {
        this.enemy_last_buff_time = 0;
      }
      if (initObj.hasOwnProperty('ammo')) {
        this.ammo = initObj.ammo
      }
      else {
        this.ammo = 0;
      }
      if (initObj.hasOwnProperty('game_status')) {
        this.game_status = initObj.game_status
      }
      else {
        this.game_status = 0;
      }
      if (initObj.hasOwnProperty('robot_bonus')) {
        this.robot_bonus = initObj.robot_bonus
      }
      else {
        this.robot_bonus = 0;
      }
      if (initObj.hasOwnProperty('supplier_status')) {
        this.supplier_status = initObj.supplier_status
      }
      else {
        this.supplier_status = 0;
      }
      if (initObj.hasOwnProperty('game_result')) {
        this.game_result = initObj.game_result
      }
      else {
        this.game_result = 0;
      }
      if (initObj.hasOwnProperty('my_pose')) {
        this.my_pose = initObj.my_pose
      }
      else {
        this.my_pose = new geometry_msgs.msg.PoseStamped();
      }
      if (initObj.hasOwnProperty('enemy_pose1')) {
        this.enemy_pose1 = initObj.enemy_pose1
      }
      else {
        this.enemy_pose1 = new geometry_msgs.msg.PoseStamped();
      }
      if (initObj.hasOwnProperty('enemy_pose2')) {
        this.enemy_pose2 = initObj.enemy_pose2
      }
      else {
        this.enemy_pose2 = new geometry_msgs.msg.PoseStamped();
      }
      if (initObj.hasOwnProperty('how_many_enemies_detected')) {
        this.how_many_enemies_detected = initObj.how_many_enemies_detected
      }
      else {
        this.how_many_enemies_detected = 0;
      }
      if (initObj.hasOwnProperty('is_enemy_1_detected')) {
        this.is_enemy_1_detected = initObj.is_enemy_1_detected
      }
      else {
        this.is_enemy_1_detected = false;
      }
      if (initObj.hasOwnProperty('is_enemy_2_detected')) {
        this.is_enemy_2_detected = initObj.is_enemy_2_detected
      }
      else {
        this.is_enemy_2_detected = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BlackboardGeneralInfoResponse
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [my_id]
    bufferOffset = _serializer.int8(obj.my_id, buffer, bufferOffset);
    // Serialize message field [my_life]
    bufferOffset = _serializer.int8(obj.my_life, buffer, bufferOffset);
    // Serialize message field [my_teamtype]
    bufferOffset = _serializer.int8(obj.my_teamtype, buffer, bufferOffset);
    // Serialize message field [robot_damage_type]
    bufferOffset = _serializer.int8(obj.robot_damage_type, buffer, bufferOffset);
    // Serialize message field [robot_damage_armor]
    bufferOffset = _serializer.int8(obj.robot_damage_armor, buffer, bufferOffset);
    // Serialize message field [my_bonus_zone]
    bufferOffset = _serializer.int8(obj.my_bonus_zone, buffer, bufferOffset);
    // Serialize message field [my_hp]
    bufferOffset = _serializer.int8(obj.my_hp, buffer, bufferOffset);
    // Serialize message field [ally_life]
    bufferOffset = _serializer.int8(obj.ally_life, buffer, bufferOffset);
    // Serialize message field [enemy1_life]
    bufferOffset = _serializer.int8(obj.enemy1_life, buffer, bufferOffset);
    // Serialize message field [enemy2_life]
    bufferOffset = _serializer.int8(obj.enemy2_life, buffer, bufferOffset);
    // Serialize message field [enemy_bonus_zone]
    bufferOffset = _serializer.int8(obj.enemy_bonus_zone, buffer, bufferOffset);
    // Serialize message field [time_passed_from_start]
    bufferOffset = _serializer.int32(obj.time_passed_from_start, buffer, bufferOffset);
    // Serialize message field [last_buff_time]
    bufferOffset = _serializer.int32(obj.last_buff_time, buffer, bufferOffset);
    // Serialize message field [last_supply_time]
    bufferOffset = _serializer.int32(obj.last_supply_time, buffer, bufferOffset);
    // Serialize message field [enemy_last_buff_time]
    bufferOffset = _serializer.int32(obj.enemy_last_buff_time, buffer, bufferOffset);
    // Serialize message field [ammo]
    bufferOffset = _serializer.int8(obj.ammo, buffer, bufferOffset);
    // Serialize message field [game_status]
    bufferOffset = _serializer.int8(obj.game_status, buffer, bufferOffset);
    // Serialize message field [robot_bonus]
    bufferOffset = _serializer.int8(obj.robot_bonus, buffer, bufferOffset);
    // Serialize message field [supplier_status]
    bufferOffset = _serializer.int8(obj.supplier_status, buffer, bufferOffset);
    // Serialize message field [game_result]
    bufferOffset = _serializer.int8(obj.game_result, buffer, bufferOffset);
    // Serialize message field [my_pose]
    bufferOffset = geometry_msgs.msg.PoseStamped.serialize(obj.my_pose, buffer, bufferOffset);
    // Serialize message field [enemy_pose1]
    bufferOffset = geometry_msgs.msg.PoseStamped.serialize(obj.enemy_pose1, buffer, bufferOffset);
    // Serialize message field [enemy_pose2]
    bufferOffset = geometry_msgs.msg.PoseStamped.serialize(obj.enemy_pose2, buffer, bufferOffset);
    // Serialize message field [how_many_enemies_detected]
    bufferOffset = _serializer.uint8(obj.how_many_enemies_detected, buffer, bufferOffset);
    // Serialize message field [is_enemy_1_detected]
    bufferOffset = _serializer.bool(obj.is_enemy_1_detected, buffer, bufferOffset);
    // Serialize message field [is_enemy_2_detected]
    bufferOffset = _serializer.bool(obj.is_enemy_2_detected, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BlackboardGeneralInfoResponse
    let len;
    let data = new BlackboardGeneralInfoResponse(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [my_id]
    data.my_id = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [my_life]
    data.my_life = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [my_teamtype]
    data.my_teamtype = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [robot_damage_type]
    data.robot_damage_type = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [robot_damage_armor]
    data.robot_damage_armor = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [my_bonus_zone]
    data.my_bonus_zone = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [my_hp]
    data.my_hp = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [ally_life]
    data.ally_life = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [enemy1_life]
    data.enemy1_life = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [enemy2_life]
    data.enemy2_life = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [enemy_bonus_zone]
    data.enemy_bonus_zone = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [time_passed_from_start]
    data.time_passed_from_start = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [last_buff_time]
    data.last_buff_time = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [last_supply_time]
    data.last_supply_time = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [enemy_last_buff_time]
    data.enemy_last_buff_time = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [ammo]
    data.ammo = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [game_status]
    data.game_status = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [robot_bonus]
    data.robot_bonus = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [supplier_status]
    data.supplier_status = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [game_result]
    data.game_result = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [my_pose]
    data.my_pose = geometry_msgs.msg.PoseStamped.deserialize(buffer, bufferOffset);
    // Deserialize message field [enemy_pose1]
    data.enemy_pose1 = geometry_msgs.msg.PoseStamped.deserialize(buffer, bufferOffset);
    // Deserialize message field [enemy_pose2]
    data.enemy_pose2 = geometry_msgs.msg.PoseStamped.deserialize(buffer, bufferOffset);
    // Deserialize message field [how_many_enemies_detected]
    data.how_many_enemies_detected = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [is_enemy_1_detected]
    data.is_enemy_1_detected = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [is_enemy_2_detected]
    data.is_enemy_2_detected = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.PoseStamped.getMessageSize(object.my_pose);
    length += geometry_msgs.msg.PoseStamped.getMessageSize(object.enemy_pose1);
    length += geometry_msgs.msg.PoseStamped.getMessageSize(object.enemy_pose2);
    return length + 43;
  }

  static datatype() {
    // Returns string type for a service object
    return 'icra_roboin_msgs/BlackboardGeneralInfoResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '97e8175f34809a4bf1b2a64adca6693a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BlackboardGeneralInfoResponse(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.my_id !== undefined) {
      resolved.my_id = msg.my_id;
    }
    else {
      resolved.my_id = 0
    }

    if (msg.my_life !== undefined) {
      resolved.my_life = msg.my_life;
    }
    else {
      resolved.my_life = 0
    }

    if (msg.my_teamtype !== undefined) {
      resolved.my_teamtype = msg.my_teamtype;
    }
    else {
      resolved.my_teamtype = 0
    }

    if (msg.robot_damage_type !== undefined) {
      resolved.robot_damage_type = msg.robot_damage_type;
    }
    else {
      resolved.robot_damage_type = 0
    }

    if (msg.robot_damage_armor !== undefined) {
      resolved.robot_damage_armor = msg.robot_damage_armor;
    }
    else {
      resolved.robot_damage_armor = 0
    }

    if (msg.my_bonus_zone !== undefined) {
      resolved.my_bonus_zone = msg.my_bonus_zone;
    }
    else {
      resolved.my_bonus_zone = 0
    }

    if (msg.my_hp !== undefined) {
      resolved.my_hp = msg.my_hp;
    }
    else {
      resolved.my_hp = 0
    }

    if (msg.ally_life !== undefined) {
      resolved.ally_life = msg.ally_life;
    }
    else {
      resolved.ally_life = 0
    }

    if (msg.enemy1_life !== undefined) {
      resolved.enemy1_life = msg.enemy1_life;
    }
    else {
      resolved.enemy1_life = 0
    }

    if (msg.enemy2_life !== undefined) {
      resolved.enemy2_life = msg.enemy2_life;
    }
    else {
      resolved.enemy2_life = 0
    }

    if (msg.enemy_bonus_zone !== undefined) {
      resolved.enemy_bonus_zone = msg.enemy_bonus_zone;
    }
    else {
      resolved.enemy_bonus_zone = 0
    }

    if (msg.time_passed_from_start !== undefined) {
      resolved.time_passed_from_start = msg.time_passed_from_start;
    }
    else {
      resolved.time_passed_from_start = 0
    }

    if (msg.last_buff_time !== undefined) {
      resolved.last_buff_time = msg.last_buff_time;
    }
    else {
      resolved.last_buff_time = 0
    }

    if (msg.last_supply_time !== undefined) {
      resolved.last_supply_time = msg.last_supply_time;
    }
    else {
      resolved.last_supply_time = 0
    }

    if (msg.enemy_last_buff_time !== undefined) {
      resolved.enemy_last_buff_time = msg.enemy_last_buff_time;
    }
    else {
      resolved.enemy_last_buff_time = 0
    }

    if (msg.ammo !== undefined) {
      resolved.ammo = msg.ammo;
    }
    else {
      resolved.ammo = 0
    }

    if (msg.game_status !== undefined) {
      resolved.game_status = msg.game_status;
    }
    else {
      resolved.game_status = 0
    }

    if (msg.robot_bonus !== undefined) {
      resolved.robot_bonus = msg.robot_bonus;
    }
    else {
      resolved.robot_bonus = 0
    }

    if (msg.supplier_status !== undefined) {
      resolved.supplier_status = msg.supplier_status;
    }
    else {
      resolved.supplier_status = 0
    }

    if (msg.game_result !== undefined) {
      resolved.game_result = msg.game_result;
    }
    else {
      resolved.game_result = 0
    }

    if (msg.my_pose !== undefined) {
      resolved.my_pose = geometry_msgs.msg.PoseStamped.Resolve(msg.my_pose)
    }
    else {
      resolved.my_pose = new geometry_msgs.msg.PoseStamped()
    }

    if (msg.enemy_pose1 !== undefined) {
      resolved.enemy_pose1 = geometry_msgs.msg.PoseStamped.Resolve(msg.enemy_pose1)
    }
    else {
      resolved.enemy_pose1 = new geometry_msgs.msg.PoseStamped()
    }

    if (msg.enemy_pose2 !== undefined) {
      resolved.enemy_pose2 = geometry_msgs.msg.PoseStamped.Resolve(msg.enemy_pose2)
    }
    else {
      resolved.enemy_pose2 = new geometry_msgs.msg.PoseStamped()
    }

    if (msg.how_many_enemies_detected !== undefined) {
      resolved.how_many_enemies_detected = msg.how_many_enemies_detected;
    }
    else {
      resolved.how_many_enemies_detected = 0
    }

    if (msg.is_enemy_1_detected !== undefined) {
      resolved.is_enemy_1_detected = msg.is_enemy_1_detected;
    }
    else {
      resolved.is_enemy_1_detected = false
    }

    if (msg.is_enemy_2_detected !== undefined) {
      resolved.is_enemy_2_detected = msg.is_enemy_2_detected;
    }
    else {
      resolved.is_enemy_2_detected = false
    }

    return resolved;
    }
};

module.exports = {
  Request: BlackboardGeneralInfoRequest,
  Response: BlackboardGeneralInfoResponse,
  md5sum() { return 'b163c0ce1011a983e5ca043d25ff9b1c'; },
  datatype() { return 'icra_roboin_msgs/BlackboardGeneralInfo'; }
};
