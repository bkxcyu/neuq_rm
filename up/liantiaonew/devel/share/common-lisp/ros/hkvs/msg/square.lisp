; Auto-generated. Do not edit!


(cl:in-package hkvs-msg)


;//! \htmlinclude square.msg.html

(cl:defclass <square> (roslisp-msg-protocol:ros-message)
  ((zs_x
    :reader zs_x
    :initarg :zs_x
    :type cl:float
    :initform 0.0)
   (zx_x
    :reader zx_x
    :initarg :zx_x
    :type cl:float
    :initform 0.0)
   (ys_x
    :reader ys_x
    :initarg :ys_x
    :type cl:float
    :initform 0.0)
   (yx_x
    :reader yx_x
    :initarg :yx_x
    :type cl:float
    :initform 0.0)
   (o_x
    :reader o_x
    :initarg :o_x
    :type cl:float
    :initform 0.0)
   (o_y
    :reader o_y
    :initarg :o_y
    :type cl:float
    :initform 0.0)
   (zs_y
    :reader zs_y
    :initarg :zs_y
    :type cl:float
    :initform 0.0)
   (zx_y
    :reader zx_y
    :initarg :zx_y
    :type cl:float
    :initform 0.0)
   (ys_y
    :reader ys_y
    :initarg :ys_y
    :type cl:float
    :initform 0.0)
   (yx_y
    :reader yx_y
    :initarg :yx_y
    :type cl:float
    :initform 0.0)
   (square_num
    :reader square_num
    :initarg :square_num
    :type cl:float
    :initform 0.0))
)

(cl:defclass square (<square>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <square>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'square)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hkvs-msg:<square> is deprecated: use hkvs-msg:square instead.")))

(cl:ensure-generic-function 'zs_x-val :lambda-list '(m))
(cl:defmethod zs_x-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:zs_x-val is deprecated.  Use hkvs-msg:zs_x instead.")
  (zs_x m))

(cl:ensure-generic-function 'zx_x-val :lambda-list '(m))
(cl:defmethod zx_x-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:zx_x-val is deprecated.  Use hkvs-msg:zx_x instead.")
  (zx_x m))

(cl:ensure-generic-function 'ys_x-val :lambda-list '(m))
(cl:defmethod ys_x-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:ys_x-val is deprecated.  Use hkvs-msg:ys_x instead.")
  (ys_x m))

(cl:ensure-generic-function 'yx_x-val :lambda-list '(m))
(cl:defmethod yx_x-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:yx_x-val is deprecated.  Use hkvs-msg:yx_x instead.")
  (yx_x m))

(cl:ensure-generic-function 'o_x-val :lambda-list '(m))
(cl:defmethod o_x-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:o_x-val is deprecated.  Use hkvs-msg:o_x instead.")
  (o_x m))

(cl:ensure-generic-function 'o_y-val :lambda-list '(m))
(cl:defmethod o_y-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:o_y-val is deprecated.  Use hkvs-msg:o_y instead.")
  (o_y m))

(cl:ensure-generic-function 'zs_y-val :lambda-list '(m))
(cl:defmethod zs_y-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:zs_y-val is deprecated.  Use hkvs-msg:zs_y instead.")
  (zs_y m))

(cl:ensure-generic-function 'zx_y-val :lambda-list '(m))
(cl:defmethod zx_y-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:zx_y-val is deprecated.  Use hkvs-msg:zx_y instead.")
  (zx_y m))

(cl:ensure-generic-function 'ys_y-val :lambda-list '(m))
(cl:defmethod ys_y-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:ys_y-val is deprecated.  Use hkvs-msg:ys_y instead.")
  (ys_y m))

(cl:ensure-generic-function 'yx_y-val :lambda-list '(m))
(cl:defmethod yx_y-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:yx_y-val is deprecated.  Use hkvs-msg:yx_y instead.")
  (yx_y m))

(cl:ensure-generic-function 'square_num-val :lambda-list '(m))
(cl:defmethod square_num-val ((m <square>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:square_num-val is deprecated.  Use hkvs-msg:square_num instead.")
  (square_num m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <square>) ostream)
  "Serializes a message object of type '<square>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'zs_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'zx_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ys_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yx_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'o_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'o_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'zs_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'zx_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ys_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yx_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'square_num))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <square>) istream)
  "Deserializes a message object of type '<square>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zs_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zx_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ys_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yx_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'o_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'o_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zs_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zx_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ys_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yx_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'square_num) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<square>)))
  "Returns string type for a message object of type '<square>"
  "hkvs/square")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'square)))
  "Returns string type for a message object of type 'square"
  "hkvs/square")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<square>)))
  "Returns md5sum for a message object of type '<square>"
  "163b03e92fe2e6978d7ca6fcb8133a7c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'square)))
  "Returns md5sum for a message object of type 'square"
  "163b03e92fe2e6978d7ca6fcb8133a7c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<square>)))
  "Returns full string definition for message of type '<square>"
  (cl:format cl:nil "float32 zs_x~%float32 zx_x~%float32 ys_x~%float32 yx_x~%float32 o_x~%float32 o_y~%float32 zs_y~%float32 zx_y~%float32 ys_y~%float32 yx_y~%float32 square_num~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'square)))
  "Returns full string definition for message of type 'square"
  (cl:format cl:nil "float32 zs_x~%float32 zx_x~%float32 ys_x~%float32 yx_x~%float32 o_x~%float32 o_y~%float32 zs_y~%float32 zx_y~%float32 ys_y~%float32 yx_y~%float32 square_num~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <square>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <square>))
  "Converts a ROS message object to a list"
  (cl:list 'square
    (cl:cons ':zs_x (zs_x msg))
    (cl:cons ':zx_x (zx_x msg))
    (cl:cons ':ys_x (ys_x msg))
    (cl:cons ':yx_x (yx_x msg))
    (cl:cons ':o_x (o_x msg))
    (cl:cons ':o_y (o_y msg))
    (cl:cons ':zs_y (zs_y msg))
    (cl:cons ':zx_y (zx_y msg))
    (cl:cons ':ys_y (ys_y msg))
    (cl:cons ':yx_y (yx_y msg))
    (cl:cons ':square_num (square_num msg))
))
