// Auto-generated. Do not edit!

// (in-package hkvs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class square {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.zs_x = null;
      this.zx_x = null;
      this.ys_x = null;
      this.yx_x = null;
      this.o_x = null;
      this.o_y = null;
      this.zs_y = null;
      this.zx_y = null;
      this.ys_y = null;
      this.yx_y = null;
      this.square_num = null;
    }
    else {
      if (initObj.hasOwnProperty('zs_x')) {
        this.zs_x = initObj.zs_x
      }
      else {
        this.zs_x = 0.0;
      }
      if (initObj.hasOwnProperty('zx_x')) {
        this.zx_x = initObj.zx_x
      }
      else {
        this.zx_x = 0.0;
      }
      if (initObj.hasOwnProperty('ys_x')) {
        this.ys_x = initObj.ys_x
      }
      else {
        this.ys_x = 0.0;
      }
      if (initObj.hasOwnProperty('yx_x')) {
        this.yx_x = initObj.yx_x
      }
      else {
        this.yx_x = 0.0;
      }
      if (initObj.hasOwnProperty('o_x')) {
        this.o_x = initObj.o_x
      }
      else {
        this.o_x = 0.0;
      }
      if (initObj.hasOwnProperty('o_y')) {
        this.o_y = initObj.o_y
      }
      else {
        this.o_y = 0.0;
      }
      if (initObj.hasOwnProperty('zs_y')) {
        this.zs_y = initObj.zs_y
      }
      else {
        this.zs_y = 0.0;
      }
      if (initObj.hasOwnProperty('zx_y')) {
        this.zx_y = initObj.zx_y
      }
      else {
        this.zx_y = 0.0;
      }
      if (initObj.hasOwnProperty('ys_y')) {
        this.ys_y = initObj.ys_y
      }
      else {
        this.ys_y = 0.0;
      }
      if (initObj.hasOwnProperty('yx_y')) {
        this.yx_y = initObj.yx_y
      }
      else {
        this.yx_y = 0.0;
      }
      if (initObj.hasOwnProperty('square_num')) {
        this.square_num = initObj.square_num
      }
      else {
        this.square_num = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type square
    // Serialize message field [zs_x]
    bufferOffset = _serializer.float32(obj.zs_x, buffer, bufferOffset);
    // Serialize message field [zx_x]
    bufferOffset = _serializer.float32(obj.zx_x, buffer, bufferOffset);
    // Serialize message field [ys_x]
    bufferOffset = _serializer.float32(obj.ys_x, buffer, bufferOffset);
    // Serialize message field [yx_x]
    bufferOffset = _serializer.float32(obj.yx_x, buffer, bufferOffset);
    // Serialize message field [o_x]
    bufferOffset = _serializer.float32(obj.o_x, buffer, bufferOffset);
    // Serialize message field [o_y]
    bufferOffset = _serializer.float32(obj.o_y, buffer, bufferOffset);
    // Serialize message field [zs_y]
    bufferOffset = _serializer.float32(obj.zs_y, buffer, bufferOffset);
    // Serialize message field [zx_y]
    bufferOffset = _serializer.float32(obj.zx_y, buffer, bufferOffset);
    // Serialize message field [ys_y]
    bufferOffset = _serializer.float32(obj.ys_y, buffer, bufferOffset);
    // Serialize message field [yx_y]
    bufferOffset = _serializer.float32(obj.yx_y, buffer, bufferOffset);
    // Serialize message field [square_num]
    bufferOffset = _serializer.float32(obj.square_num, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type square
    let len;
    let data = new square(null);
    // Deserialize message field [zs_x]
    data.zs_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [zx_x]
    data.zx_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ys_x]
    data.ys_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yx_x]
    data.yx_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [o_x]
    data.o_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [o_y]
    data.o_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [zs_y]
    data.zs_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [zx_y]
    data.zx_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ys_y]
    data.ys_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yx_y]
    data.yx_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [square_num]
    data.square_num = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 44;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hkvs/square';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '163b03e92fe2e6978d7ca6fcb8133a7c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 zs_x
    float32 zx_x
    float32 ys_x
    float32 yx_x
    float32 o_x
    float32 o_y
    float32 zs_y
    float32 zx_y
    float32 ys_y
    float32 yx_y
    float32 square_num
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new square(null);
    if (msg.zs_x !== undefined) {
      resolved.zs_x = msg.zs_x;
    }
    else {
      resolved.zs_x = 0.0
    }

    if (msg.zx_x !== undefined) {
      resolved.zx_x = msg.zx_x;
    }
    else {
      resolved.zx_x = 0.0
    }

    if (msg.ys_x !== undefined) {
      resolved.ys_x = msg.ys_x;
    }
    else {
      resolved.ys_x = 0.0
    }

    if (msg.yx_x !== undefined) {
      resolved.yx_x = msg.yx_x;
    }
    else {
      resolved.yx_x = 0.0
    }

    if (msg.o_x !== undefined) {
      resolved.o_x = msg.o_x;
    }
    else {
      resolved.o_x = 0.0
    }

    if (msg.o_y !== undefined) {
      resolved.o_y = msg.o_y;
    }
    else {
      resolved.o_y = 0.0
    }

    if (msg.zs_y !== undefined) {
      resolved.zs_y = msg.zs_y;
    }
    else {
      resolved.zs_y = 0.0
    }

    if (msg.zx_y !== undefined) {
      resolved.zx_y = msg.zx_y;
    }
    else {
      resolved.zx_y = 0.0
    }

    if (msg.ys_y !== undefined) {
      resolved.ys_y = msg.ys_y;
    }
    else {
      resolved.ys_y = 0.0
    }

    if (msg.yx_y !== undefined) {
      resolved.yx_y = msg.yx_y;
    }
    else {
      resolved.yx_y = 0.0
    }

    if (msg.square_num !== undefined) {
      resolved.square_num = msg.square_num;
    }
    else {
      resolved.square_num = 0.0
    }

    return resolved;
    }
};

module.exports = square;
