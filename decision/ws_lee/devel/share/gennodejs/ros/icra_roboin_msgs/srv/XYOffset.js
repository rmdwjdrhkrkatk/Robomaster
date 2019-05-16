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


//-----------------------------------------------------------

class XYOffsetRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x_offset = null;
      this.y_offset = null;
    }
    else {
      if (initObj.hasOwnProperty('x_offset')) {
        this.x_offset = initObj.x_offset
      }
      else {
        this.x_offset = 0;
      }
      if (initObj.hasOwnProperty('y_offset')) {
        this.y_offset = initObj.y_offset
      }
      else {
        this.y_offset = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type XYOffsetRequest
    // Serialize message field [x_offset]
    bufferOffset = _serializer.int8(obj.x_offset, buffer, bufferOffset);
    // Serialize message field [y_offset]
    bufferOffset = _serializer.int8(obj.y_offset, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type XYOffsetRequest
    let len;
    let data = new XYOffsetRequest(null);
    // Deserialize message field [x_offset]
    data.x_offset = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [y_offset]
    data.y_offset = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'icra_roboin_msgs/XYOffsetRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '52d0410d68abc4c057c9602bab186b90';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 x_offset
    int8 y_offset
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new XYOffsetRequest(null);
    if (msg.x_offset !== undefined) {
      resolved.x_offset = msg.x_offset;
    }
    else {
      resolved.x_offset = 0
    }

    if (msg.y_offset !== undefined) {
      resolved.y_offset = msg.y_offset;
    }
    else {
      resolved.y_offset = 0
    }

    return resolved;
    }
};

class XYOffsetResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.received = null;
    }
    else {
      if (initObj.hasOwnProperty('received')) {
        this.received = initObj.received
      }
      else {
        this.received = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type XYOffsetResponse
    // Serialize message field [received]
    bufferOffset = _serializer.bool(obj.received, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type XYOffsetResponse
    let len;
    let data = new XYOffsetResponse(null);
    // Deserialize message field [received]
    data.received = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'icra_roboin_msgs/XYOffsetResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'dd4152e077925db952c78baadb1e48b7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool received
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new XYOffsetResponse(null);
    if (msg.received !== undefined) {
      resolved.received = msg.received;
    }
    else {
      resolved.received = false
    }

    return resolved;
    }
};

module.exports = {
  Request: XYOffsetRequest,
  Response: XYOffsetResponse,
  md5sum() { return 'd8dc129d6dde9852a52847783f565dfc'; },
  datatype() { return 'icra_roboin_msgs/XYOffset'; }
};
