
(cl:in-package :asdf)

(defsystem "icra_roboin_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "CircleObstacle" :depends-on ("_package_CircleObstacle"))
    (:file "_package_CircleObstacle" :depends-on ("_package"))
    (:file "Obstacles" :depends-on ("_package_Obstacles"))
    (:file "_package_Obstacles" :depends-on ("_package"))
    (:file "SegmentObstacle" :depends-on ("_package_SegmentObstacle"))
    (:file "_package_SegmentObstacle" :depends-on ("_package"))
    (:file "YoloDetectionAction" :depends-on ("_package_YoloDetectionAction"))
    (:file "_package_YoloDetectionAction" :depends-on ("_package"))
    (:file "YoloDetectionActionFeedback" :depends-on ("_package_YoloDetectionActionFeedback"))
    (:file "_package_YoloDetectionActionFeedback" :depends-on ("_package"))
    (:file "YoloDetectionActionGoal" :depends-on ("_package_YoloDetectionActionGoal"))
    (:file "_package_YoloDetectionActionGoal" :depends-on ("_package"))
    (:file "YoloDetectionActionResult" :depends-on ("_package_YoloDetectionActionResult"))
    (:file "_package_YoloDetectionActionResult" :depends-on ("_package"))
    (:file "YoloDetectionFeedback" :depends-on ("_package_YoloDetectionFeedback"))
    (:file "_package_YoloDetectionFeedback" :depends-on ("_package"))
    (:file "YoloDetectionGoal" :depends-on ("_package_YoloDetectionGoal"))
    (:file "_package_YoloDetectionGoal" :depends-on ("_package"))
    (:file "YoloDetectionInfo" :depends-on ("_package_YoloDetectionInfo"))
    (:file "_package_YoloDetectionInfo" :depends-on ("_package"))
    (:file "YoloDetectionResult" :depends-on ("_package_YoloDetectionResult"))
    (:file "_package_YoloDetectionResult" :depends-on ("_package"))
  ))