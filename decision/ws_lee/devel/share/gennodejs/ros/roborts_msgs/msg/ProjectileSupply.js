// Auto-generated. Do not edit!

// (in-package roborts_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ProjectileSupply {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.supply = null;
    }
    else {
      if (initObj.hasOwnProperty('supply')) {
        this.supply = initObj.supply
      }
      else {
        this.supply = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ProjectileSupply
    // Serialize message field [supply]
    bufferOffset = _serializer.bool(obj.supply, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ProjectileSupply
    let len;
    let data = new ProjectileSupply(null);
    // Deserialize message field [supply]
    data.supply = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'roborts_msgs/ProjectileSupply';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3f61c0f8bda2af4961ed47ff103d5653';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #projectile supply
    bool supply
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ProjectileSupply(null);
    if (msg.supply !== undefined) {
      resolved.supply = msg.supply;
    }
    else {
      resolved.supply = false
    }

    return resolved;
    }
};

module.exports = ProjectileSupply;
