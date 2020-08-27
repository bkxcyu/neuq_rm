; Auto-generated. Do not edit!


(cl:in-package hkvs-msg)


;//! \htmlinclude vel.msg.html

(cl:defclass <vel> (roslisp-msg-protocol:ros-message)
  ((vel
    :reader vel
    :initarg :vel
    :type cl:float
    :initform 0.0))
)

(cl:defclass vel (<vel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <vel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'vel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hkvs-msg:<vel> is deprecated: use hkvs-msg:vel instead.")))

(cl:ensure-generic-function 'vel-val :lambda-list '(m))
(cl:defmethod vel-val ((m <vel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hkvs-msg:vel-val is deprecated.  Use hkvs-msg:vel instead.")
  (vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <vel>) ostream)
  "Serializes a message object of type '<vel>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <vel>) istream)
  "Deserializes a message object of type '<vel>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<vel>)))
  "Returns string type for a message object of type '<vel>"
  "hkvs/vel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'vel)))
  "Returns string type for a message object of type 'vel"
  "hkvs/vel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<vel>)))
  "Returns md5sum for a message object of type '<vel>"
  "378ca590f55ecb8d30867c8ddf1db3c5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'vel)))
  "Returns md5sum for a message object of type 'vel"
  "378ca590f55ecb8d30867c8ddf1db3c5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<vel>)))
  "Returns full string definition for message of type '<vel>"
  (cl:format cl:nil "float32 vel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'vel)))
  "Returns full string definition for message of type 'vel"
  (cl:format cl:nil "float32 vel~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <vel>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <vel>))
  "Converts a ROS message object to a list"
  (cl:list 'vel
    (cl:cons ':vel (vel msg))
))
