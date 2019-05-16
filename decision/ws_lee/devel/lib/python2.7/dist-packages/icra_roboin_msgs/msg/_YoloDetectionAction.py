# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from icra_roboin_msgs/YoloDetectionAction.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import std_msgs.msg
import genpy
import actionlib_msgs.msg
import icra_roboin_msgs.msg

class YoloDetectionAction(genpy.Message):
  _md5sum = "ec702e9e8365cb7b66808ec14f81dde4"
  _type = "icra_roboin_msgs/YoloDetectionAction"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

YoloDetectionActionGoal action_goal
YoloDetectionActionResult action_result
YoloDetectionActionFeedback action_feedback

================================================================================
MSG: icra_roboin_msgs/YoloDetectionActionGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalID goal_id
YoloDetectionGoal goal

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
MSG: actionlib_msgs/GoalID
# The stamp should store the time at which this goal was requested.
# It is used by an action server when it tries to preempt all
# goals that were requested before a certain time
time stamp

# The id provides a way to associate feedback and
# result message with specific goal requests. The id
# specified must be unique.
string id


================================================================================
MSG: icra_roboin_msgs/YoloDetectionGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#Send a flag to server to control the thread start, pause, restart and stop
#command == 1 start
#command == 2 pause
#command == 3 stop
uint8 command

================================================================================
MSG: icra_roboin_msgs/YoloDetectionActionResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
YoloDetectionResult result

================================================================================
MSG: actionlib_msgs/GoalStatus
GoalID goal_id
uint8 status
uint8 PENDING         = 0   # The goal has yet to be processed by the action server
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing
                            #   and has since completed its execution (Terminal State)
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due
                            #    to some failure (Terminal State)
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,
                            #    because the goal was unattainable or invalid (Terminal State)
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing
                            #    and has not yet completed execution
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,
                            #    but the action server has not yet confirmed that the goal is canceled
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing
                            #    and was successfully cancelled (Terminal State)
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be
                            #    sent over the wire by an action server

#Allow for the user to associate a string with GoalStatus for debugging
string text


================================================================================
MSG: icra_roboin_msgs/YoloDetectionResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
float32 result

================================================================================
MSG: icra_roboin_msgs/YoloDetectionActionFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
YoloDetectionFeedback feedback

================================================================================
MSG: icra_roboin_msgs/YoloDetectionFeedback
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

"""
  __slots__ = ['action_goal','action_result','action_feedback']
  _slot_types = ['icra_roboin_msgs/YoloDetectionActionGoal','icra_roboin_msgs/YoloDetectionActionResult','icra_roboin_msgs/YoloDetectionActionFeedback']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       action_goal,action_result,action_feedback

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(YoloDetectionAction, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.action_goal is None:
        self.action_goal = icra_roboin_msgs.msg.YoloDetectionActionGoal()
      if self.action_result is None:
        self.action_result = icra_roboin_msgs.msg.YoloDetectionActionResult()
      if self.action_feedback is None:
        self.action_feedback = icra_roboin_msgs.msg.YoloDetectionActionFeedback()
    else:
      self.action_goal = icra_roboin_msgs.msg.YoloDetectionActionGoal()
      self.action_result = icra_roboin_msgs.msg.YoloDetectionActionResult()
      self.action_feedback = icra_roboin_msgs.msg.YoloDetectionActionFeedback()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs))
      _x = self.action_goal.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs))
      _x = self.action_goal.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_B3I().pack(_x.action_goal.goal.command, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs))
      _x = self.action_result.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs))
      _x = self.action_result.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_result.status.status))
      _x = self.action_result.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_f3I().pack(_x.action_result.result.result, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs))
      _x = self.action_feedback.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs))
      _x = self.action_feedback.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_feedback.status.status))
      _x = self.action_feedback.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I2B().pack(_x.action_feedback.feedback.stamp.secs, _x.action_feedback.feedback.stamp.nsecs, _x.action_feedback.feedback.infochecker, _x.action_feedback.feedback.enemy))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.angle_hori))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.angle_verti))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.Pixel_X))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.Pixel_Y))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.Pixel_width))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.Pixel_height))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.real_width))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.real_height))
      buff.write(_get_struct_3h().pack(*self.action_feedback.feedback.distance))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.action_goal is None:
        self.action_goal = icra_roboin_msgs.msg.YoloDetectionActionGoal()
      if self.action_result is None:
        self.action_result = icra_roboin_msgs.msg.YoloDetectionActionResult()
      if self.action_feedback is None:
        self.action_feedback = icra_roboin_msgs.msg.YoloDetectionActionFeedback()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_goal.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_goal.goal_id.id = str[start:end]
      _x = self
      start = end
      end += 13
      (_x.action_goal.goal.command, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs,) = _get_struct_B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_result.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_result.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.text = str[start:end].decode('utf-8')
      else:
        self.action_result.status.text = str[start:end]
      _x = self
      start = end
      end += 16
      (_x.action_result.result.result, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs,) = _get_struct_f3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_feedback.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.text = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.text = str[start:end]
      _x = self
      start = end
      end += 10
      (_x.action_feedback.feedback.stamp.secs, _x.action_feedback.feedback.stamp.nsecs, _x.action_feedback.feedback.infochecker, _x.action_feedback.feedback.enemy,) = _get_struct_2I2B().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.angle_hori = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.angle_verti = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_X = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_Y = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_width = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_height = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.real_width = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.real_height = _get_struct_3h().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.distance = _get_struct_3h().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs))
      _x = self.action_goal.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs))
      _x = self.action_goal.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_B3I().pack(_x.action_goal.goal.command, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs))
      _x = self.action_result.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs))
      _x = self.action_result.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_result.status.status))
      _x = self.action_result.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_f3I().pack(_x.action_result.result.result, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs))
      _x = self.action_feedback.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs))
      _x = self.action_feedback.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_feedback.status.status))
      _x = self.action_feedback.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I2B().pack(_x.action_feedback.feedback.stamp.secs, _x.action_feedback.feedback.stamp.nsecs, _x.action_feedback.feedback.infochecker, _x.action_feedback.feedback.enemy))
      buff.write(self.action_feedback.feedback.angle_hori.tostring())
      buff.write(self.action_feedback.feedback.angle_verti.tostring())
      buff.write(self.action_feedback.feedback.Pixel_X.tostring())
      buff.write(self.action_feedback.feedback.Pixel_Y.tostring())
      buff.write(self.action_feedback.feedback.Pixel_width.tostring())
      buff.write(self.action_feedback.feedback.Pixel_height.tostring())
      buff.write(self.action_feedback.feedback.real_width.tostring())
      buff.write(self.action_feedback.feedback.real_height.tostring())
      buff.write(self.action_feedback.feedback.distance.tostring())
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.action_goal is None:
        self.action_goal = icra_roboin_msgs.msg.YoloDetectionActionGoal()
      if self.action_result is None:
        self.action_result = icra_roboin_msgs.msg.YoloDetectionActionResult()
      if self.action_feedback is None:
        self.action_feedback = icra_roboin_msgs.msg.YoloDetectionActionFeedback()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_goal.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_goal.goal_id.id = str[start:end]
      _x = self
      start = end
      end += 13
      (_x.action_goal.goal.command, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs,) = _get_struct_B3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_result.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_result.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.text = str[start:end].decode('utf-8')
      else:
        self.action_result.status.text = str[start:end]
      _x = self
      start = end
      end += 16
      (_x.action_result.result.result, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs,) = _get_struct_f3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_feedback.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.text = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.text = str[start:end]
      _x = self
      start = end
      end += 10
      (_x.action_feedback.feedback.stamp.secs, _x.action_feedback.feedback.stamp.nsecs, _x.action_feedback.feedback.infochecker, _x.action_feedback.feedback.enemy,) = _get_struct_2I2B().unpack(str[start:end])
      start = end
      end += 6
      self.action_feedback.feedback.angle_hori = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.angle_verti = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_X = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_Y = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_width = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.Pixel_height = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.real_width = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.real_height = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      start = end
      end += 6
      self.action_feedback.feedback.distance = numpy.frombuffer(str[start:end], dtype=numpy.int16, count=3)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_B = None
def _get_struct_B():
    global _struct_B
    if _struct_B is None:
        _struct_B = struct.Struct("<B")
    return _struct_B
_struct_f3I = None
def _get_struct_f3I():
    global _struct_f3I
    if _struct_f3I is None:
        _struct_f3I = struct.Struct("<f3I")
    return _struct_f3I
_struct_2I2B = None
def _get_struct_2I2B():
    global _struct_2I2B
    if _struct_2I2B is None:
        _struct_2I2B = struct.Struct("<2I2B")
    return _struct_2I2B
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_3h = None
def _get_struct_3h():
    global _struct_3h
    if _struct_3h is None:
        _struct_3h = struct.Struct("<3h")
    return _struct_3h
_struct_B3I = None
def _get_struct_B3I():
    global _struct_B3I
    if _struct_B3I is None:
        _struct_B3I = struct.Struct("<B3I")
    return _struct_B3I
_struct_2I = None
def _get_struct_2I():
    global _struct_2I
    if _struct_2I is None:
        _struct_2I = struct.Struct("<2I")
    return _struct_2I