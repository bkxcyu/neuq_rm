
(cl:in-package :asdf)

(defsystem "hkvs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "square" :depends-on ("_package_square"))
    (:file "_package_square" :depends-on ("_package"))
    (:file "vel" :depends-on ("_package_vel"))
    (:file "_package_vel" :depends-on ("_package"))
  ))