
(cl:in-package :asdf)

(defsystem "icra_roboin_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "BlackboardGeneralInfo" :depends-on ("_package_BlackboardGeneralInfo"))
    (:file "_package_BlackboardGeneralInfo" :depends-on ("_package"))
    (:file "PitchGain" :depends-on ("_package_PitchGain"))
    (:file "_package_PitchGain" :depends-on ("_package"))
    (:file "XYOffset" :depends-on ("_package_XYOffset"))
    (:file "_package_XYOffset" :depends-on ("_package"))
    (:file "YawGain" :depends-on ("_package_YawGain"))
    (:file "_package_YawGain" :depends-on ("_package"))
  ))