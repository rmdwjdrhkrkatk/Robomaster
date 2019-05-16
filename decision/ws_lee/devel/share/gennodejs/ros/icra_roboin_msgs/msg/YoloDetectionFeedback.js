// Auto-generated. Do not edit!

// (in-package icra_roboin_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class YoloDetectionFeedback {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.infochecker = null;
      this.enemy = null;
      this.angle_hori = null;
      this.angle_verti = null;
      this.Pixel_X = null;
      this.Pixel_Y = null;
      this.Pixel_width = null;
      this.Pixel_height = null;
      this.real_width = null;
      this.real_height = null;
      this.distance = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('infochecker')) {
        this.infochecker = initObj.infochecker
      }
      else {
        this.infochecker = 0;
      }
      if (initObj.hasOwnProperty('enemy')) {
        this.enemy = initObj.enemy
      }
      else {
        this.enemy = 0;
      }
      if (initObj.hasOwnProperty('angle_hori')) {
        this.angle_hori = initObj.angle_hori
      }
      else {
        this.angle_hori = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('angle_verti')) {
        this.angle_verti = initObj.angle_verti
      }
      else {
        this.angle_verti = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('Pixel_X')) {
        this.Pixel_X = initObj.Pixel_X
      }
      else {
        this.Pixel_X = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('Pixel_Y')) {
        this.Pixel_Y = initObj.Pixel_Y
      }
      else {
        this.Pixel_Y = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('Pixel_width')) {
        this.Pixel_width = initObj.Pixel_width
      }
      else {
        this.Pixel_width = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('Pixel_height')) {
        this.Pixel_height = initObj.Pixel_height
      }
      else {
        this.Pixel_height = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('real_width')) {
        this.real_width = initObj.real_width
      }
      else {
        this.real_width = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('real_height')) {
        this.real_height = initObj.real_height
      }
      else {
        this.real_height = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = new Array(3).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type YoloDetectionFeedback
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [infochecker]
    bufferOffset = _serializer.uint8(obj.infochecker, buffer, bufferOffset);
    // Serialize message field [enemy]
    bufferOffset = _serializer.uint8(obj.enemy, buffer, bufferOffset);
    // Check that the constant length array field [angle_hori] has the right length
    if (obj.angle_hori.length !== 3) {
      throw new Error('Unable to serialize array field angle_hori - length must be 3')
    }
    // Serialize message field [angle_hori]
    bufferOffset = _arraySerializer.int16(obj.angle_hori, buffer, bufferOffset, 3);
    // Check that the constant length array field [angle_verti] has the right length
    if (obj.angle_verti.length !== 3) {
      throw new Error('Unable to serialize array field angle_verti - length must be 3')
    }
    // Serialize message field [angle_verti]
    bufferOffset = _arraySerializer.int16(obj.angle_verti, buffer, bufferOffset, 3);
    // Check that the constant length array field [Pixel_X] has the right length
    if (obj.Pixel_X.length !== 3) {
      throw new Error('Unable to serialize array field Pixel_X - length must be 3')
    }
    // Serialize message field [Pixel_X]
    bufferOffset = _arraySerializer.int16(obj.Pixel_X, buffer, bufferOffset, 3);
    // Check that the constant length array field [Pixel_Y] has the right length
    if (obj.Pixel_Y.length !== 3) {
      throw new Error('Unable to serialize array field Pixel_Y - length must be 3')
    }
    // Serialize message field [Pixel_Y]
    bufferOffset = _arraySerializer.int16(obj.Pixel_Y, buffer, bufferOffset, 3);
    // Check that the constant length array field [Pixel_width] has the right length
    if (obj.Pixel_width.length !== 3) {
      throw new Error('Unable to serialize array field Pixel_width - length must be 3')
    }
    // Serialize message field [Pixel_width]
    bufferOffset = _arraySerializer.int16(obj.Pixel_width, buffer, bufferOffset, 3);
    // Check that the constant length array field [Pixel_height] has the right length
    if (obj.Pixel_height.length !== 3) {
      throw new Error('Unable to serialize array field Pixel_height - length must be 3')
    }
    // Serialize message field [Pixel_height]
    bufferOffset = _arraySerializer.int16(obj.Pixel_height, buffer, bufferOffset, 3);
    // Check that the constant length array field [real_width] has the right length
    if (obj.real_width.length !== 3) {
      throw new Error('Unable to serialize array field real_width - length must be 3')
    }
    // Serialize message field [real_width]
    bufferOffset = _arraySerializer.int16(obj.real_width, buffer, bufferOffset, 3);
    // Check that the constant length array field [real_height] has the right length
    if (obj.real_height.length !== 3) {
      throw new Error('Unable to serialize array field real_height - length must be 3')
    }
    // Serialize message field [real_height]
    bufferOffset = _arraySerializer.int16(obj.real_height, buffer, bufferOffset, 3);
    // Check that the constant length array field [distance] has the right length
    if (obj.distance.length !== 3) {
      throw new Error('Unable to serialize array field distance - length must be 3')
    }
    // Serialize message field [distance]
    bufferOffset = _arraySerializer.int16(obj.distance, buffer, bufferOffset, 3);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type YoloDetectionFeedback
    let len;
    let data = new YoloDetectionFeedback(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [infochecker]
    data.infochecker = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [enemy]
    data.enemy = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [angle_hori]
    data.angle_hori = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [angle_verti]
    data.angle_verti = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [Pixel_X]
    data.Pixel_X = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [Pixel_Y]
    data.Pixel_Y = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [Pixel_width]
    data.Pixel_width = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [Pixel_height]
    data.Pixel_height = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [real_width]
    data.real_width = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [real_height]
    data.real_height = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    // Deserialize message field [distance]
    data.distance = _arrayDeserializer.int16(buffer, bufferOffset, 3)
    return data;
  }

  static getMessageSize(object) {
    return 64;
  }

  static datatype() {
    // Returns string type for a message object
    return 'icra_roboin_msgs/YoloDetectionFeedback';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '264543f7a1172d61963435fe8085999c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    #feedback
    time stamp
    uint8 infochecker
    uint8 enemy
    int16[3] angle_hori
    int16[3] angle_verti
    int16[3] Pixel_X
    int16[3] Pixel_Y
    int16[3] Pixel_width
    int16[3] Pixel_height
    int16[3] real_width
    int16[3] real_height
    int16[3] distance
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new YoloDetectionFeedback(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.infochecker !== undefined) {
      resolved.infochecker = msg.infochecker;
    }
    else {
      resolved.infochecker = 0
    }

    if (msg.enemy !== undefined) {
      resolved.enemy = msg.enemy;
    }
    else {
      resolved.enemy = 0
    }

    if (msg.angle_hori !== undefined) {
      resolved.angle_hori = msg.angle_hori;
    }
    else {
      resolved.angle_hori = new Array(3).fill(0)
    }

    if (msg.angle_verti !== undefined) {
      resolved.angle_verti = msg.angle_verti;
    }
    else {
      resolved.angle_verti = new Array(3).fill(0)
    }

    if (msg.Pixel_X !== undefined) {
      resolved.Pixel_X = msg.Pixel_X;
    }
    else {
      resolved.Pixel_X = new Array(3).fill(0)
    }

    if (msg.Pixel_Y !== undefined) {
      resolved.Pixel_Y = msg.Pixel_Y;
    }
    else {
      resolved.Pixel_Y = new Array(3).fill(0)
    }

    if (msg.Pixel_width !== undefined) {
      resolved.Pixel_width = msg.Pixel_width;
    }
    else {
      resolved.Pixel_width = new Array(3).fill(0)
    }

    if (msg.Pixel_height !== undefined) {
      resolved.Pixel_height = msg.Pixel_height;
    }
    else {
      resolved.Pixel_height = new Array(3).fill(0)
    }

    if (msg.real_width !== undefined) {
      resolved.real_width = msg.real_width;
    }
    else {
      resolved.real_width = new Array(3).fill(0)
    }

    if (msg.real_height !== undefined) {
      resolved.real_height = msg.real_height;
    }
    else {
      resolved.real_height = new Array(3).fill(0)
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = new Array(3).fill(0)
    }

    return resolved;
    }
};

module.exports = YoloDetectionFeedback;
