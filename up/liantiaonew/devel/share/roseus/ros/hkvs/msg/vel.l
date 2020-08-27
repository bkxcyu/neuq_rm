;; Auto-generated. Do not edit!


(when (boundp 'hkvs::vel)
  (if (not (find-package "HKVS"))
    (make-package "HKVS"))
  (shadow 'vel (find-package "HKVS")))
(unless (find-package "HKVS::VEL")
  (make-package "HKVS::VEL"))

(in-package "ROS")
;;//! \htmlinclude vel.msg.html


(defclass hkvs::vel
  :super ros::object
  :slots (_vel ))

(defmethod hkvs::vel
  (:init
   (&key
    ((:vel __vel) 0.0)
    )
   (send-super :init)
   (setq _vel (float __vel))
   self)
  (:vel
   (&optional __vel)
   (if __vel (setq _vel __vel)) _vel)
  (:serialization-length
   ()
   (+
    ;; float32 _vel
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vel
       (sys::poke _vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vel
     (setq _vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hkvs::vel :md5sum-) "378ca590f55ecb8d30867c8ddf1db3c5")
(setf (get hkvs::vel :datatype-) "hkvs/vel")
(setf (get hkvs::vel :definition-)
      "float32 vel

")



(provide :hkvs/vel "378ca590f55ecb8d30867c8ddf1db3c5")


