;; Auto-generated. Do not edit!


(when (boundp 'hkvs::square)
  (if (not (find-package "HKVS"))
    (make-package "HKVS"))
  (shadow 'square (find-package "HKVS")))
(unless (find-package "HKVS::SQUARE")
  (make-package "HKVS::SQUARE"))

(in-package "ROS")
;;//! \htmlinclude square.msg.html


(defclass hkvs::square
  :super ros::object
  :slots (_zs_x _zx_x _ys_x _yx_x _o_x _o_y _zs_y _zx_y _ys_y _yx_y _square_num ))

(defmethod hkvs::square
  (:init
   (&key
    ((:zs_x __zs_x) 0.0)
    ((:zx_x __zx_x) 0.0)
    ((:ys_x __ys_x) 0.0)
    ((:yx_x __yx_x) 0.0)
    ((:o_x __o_x) 0.0)
    ((:o_y __o_y) 0.0)
    ((:zs_y __zs_y) 0.0)
    ((:zx_y __zx_y) 0.0)
    ((:ys_y __ys_y) 0.0)
    ((:yx_y __yx_y) 0.0)
    ((:square_num __square_num) 0.0)
    )
   (send-super :init)
   (setq _zs_x (float __zs_x))
   (setq _zx_x (float __zx_x))
   (setq _ys_x (float __ys_x))
   (setq _yx_x (float __yx_x))
   (setq _o_x (float __o_x))
   (setq _o_y (float __o_y))
   (setq _zs_y (float __zs_y))
   (setq _zx_y (float __zx_y))
   (setq _ys_y (float __ys_y))
   (setq _yx_y (float __yx_y))
   (setq _square_num (float __square_num))
   self)
  (:zs_x
   (&optional __zs_x)
   (if __zs_x (setq _zs_x __zs_x)) _zs_x)
  (:zx_x
   (&optional __zx_x)
   (if __zx_x (setq _zx_x __zx_x)) _zx_x)
  (:ys_x
   (&optional __ys_x)
   (if __ys_x (setq _ys_x __ys_x)) _ys_x)
  (:yx_x
   (&optional __yx_x)
   (if __yx_x (setq _yx_x __yx_x)) _yx_x)
  (:o_x
   (&optional __o_x)
   (if __o_x (setq _o_x __o_x)) _o_x)
  (:o_y
   (&optional __o_y)
   (if __o_y (setq _o_y __o_y)) _o_y)
  (:zs_y
   (&optional __zs_y)
   (if __zs_y (setq _zs_y __zs_y)) _zs_y)
  (:zx_y
   (&optional __zx_y)
   (if __zx_y (setq _zx_y __zx_y)) _zx_y)
  (:ys_y
   (&optional __ys_y)
   (if __ys_y (setq _ys_y __ys_y)) _ys_y)
  (:yx_y
   (&optional __yx_y)
   (if __yx_y (setq _yx_y __yx_y)) _yx_y)
  (:square_num
   (&optional __square_num)
   (if __square_num (setq _square_num __square_num)) _square_num)
  (:serialization-length
   ()
   (+
    ;; float32 _zs_x
    4
    ;; float32 _zx_x
    4
    ;; float32 _ys_x
    4
    ;; float32 _yx_x
    4
    ;; float32 _o_x
    4
    ;; float32 _o_y
    4
    ;; float32 _zs_y
    4
    ;; float32 _zx_y
    4
    ;; float32 _ys_y
    4
    ;; float32 _yx_y
    4
    ;; float32 _square_num
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _zs_x
       (sys::poke _zs_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _zx_x
       (sys::poke _zx_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ys_x
       (sys::poke _ys_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yx_x
       (sys::poke _yx_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _o_x
       (sys::poke _o_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _o_y
       (sys::poke _o_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _zs_y
       (sys::poke _zs_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _zx_y
       (sys::poke _zx_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ys_y
       (sys::poke _ys_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yx_y
       (sys::poke _yx_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _square_num
       (sys::poke _square_num (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _zs_x
     (setq _zs_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _zx_x
     (setq _zx_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ys_x
     (setq _ys_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yx_x
     (setq _yx_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _o_x
     (setq _o_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _o_y
     (setq _o_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _zs_y
     (setq _zs_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _zx_y
     (setq _zx_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ys_y
     (setq _ys_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yx_y
     (setq _yx_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _square_num
     (setq _square_num (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hkvs::square :md5sum-) "163b03e92fe2e6978d7ca6fcb8133a7c")
(setf (get hkvs::square :datatype-) "hkvs/square")
(setf (get hkvs::square :definition-)
      "float32 zs_x
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

")



(provide :hkvs/square "163b03e92fe2e6978d7ca6fcb8133a7c")


