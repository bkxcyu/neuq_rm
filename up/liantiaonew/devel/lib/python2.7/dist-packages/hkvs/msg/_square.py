# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from hkvs/square.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class square(genpy.Message):
  _md5sum = "163b03e92fe2e6978d7ca6fcb8133a7c"
  _type = "hkvs/square"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float32 zs_x
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
"""
  __slots__ = ['zs_x','zx_x','ys_x','yx_x','o_x','o_y','zs_y','zx_y','ys_y','yx_y','square_num']
  _slot_types = ['float32','float32','float32','float32','float32','float32','float32','float32','float32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       zs_x,zx_x,ys_x,yx_x,o_x,o_y,zs_y,zx_y,ys_y,yx_y,square_num

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(square, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.zs_x is None:
        self.zs_x = 0.
      if self.zx_x is None:
        self.zx_x = 0.
      if self.ys_x is None:
        self.ys_x = 0.
      if self.yx_x is None:
        self.yx_x = 0.
      if self.o_x is None:
        self.o_x = 0.
      if self.o_y is None:
        self.o_y = 0.
      if self.zs_y is None:
        self.zs_y = 0.
      if self.zx_y is None:
        self.zx_y = 0.
      if self.ys_y is None:
        self.ys_y = 0.
      if self.yx_y is None:
        self.yx_y = 0.
      if self.square_num is None:
        self.square_num = 0.
    else:
      self.zs_x = 0.
      self.zx_x = 0.
      self.ys_x = 0.
      self.yx_x = 0.
      self.o_x = 0.
      self.o_y = 0.
      self.zs_y = 0.
      self.zx_y = 0.
      self.ys_y = 0.
      self.yx_y = 0.
      self.square_num = 0.

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
      buff.write(_get_struct_11f().pack(_x.zs_x, _x.zx_x, _x.ys_x, _x.yx_x, _x.o_x, _x.o_y, _x.zs_y, _x.zx_y, _x.ys_y, _x.yx_y, _x.square_num))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 44
      (_x.zs_x, _x.zx_x, _x.ys_x, _x.yx_x, _x.o_x, _x.o_y, _x.zs_y, _x.zx_y, _x.ys_y, _x.yx_y, _x.square_num,) = _get_struct_11f().unpack(str[start:end])
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
      buff.write(_get_struct_11f().pack(_x.zs_x, _x.zx_x, _x.ys_x, _x.yx_x, _x.o_x, _x.o_y, _x.zs_y, _x.zx_y, _x.ys_y, _x.yx_y, _x.square_num))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 44
      (_x.zs_x, _x.zx_x, _x.ys_x, _x.yx_x, _x.o_x, _x.o_y, _x.zs_y, _x.zx_y, _x.ys_y, _x.yx_y, _x.square_num,) = _get_struct_11f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_11f = None
def _get_struct_11f():
    global _struct_11f
    if _struct_11f is None:
        _struct_11f = struct.Struct("<11f")
    return _struct_11f
