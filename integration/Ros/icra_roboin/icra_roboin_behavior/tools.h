#ifndef ICRA_ROBOIN_BEHAVIOR_TOOLS_H
#define ICRA_ROBOIN_BEHAVIOR_TOOLS_H
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <algorithm>

namespace icra_roboin_behavior { namespace tools
{

inline double GetPlanarDistance(const geometry_msgs::PoseStamped &pose1,
                     const geometry_msgs::PoseStamped &pose2) {
    const geometry_msgs::Point point1 = pose1.pose.position;
    const geometry_msgs::Point point2 = pose2.pose.position;
    const double dx = point1.x - point2.x;
    const double dy = point1.y - point2.y;
    return std::sqrt(dx * dx + dy * dy);
}

inline double GetAngle(const geometry_msgs::PoseStamped &pose1,
                  const geometry_msgs::PoseStamped &pose2) {
    const geometry_msgs::Quaternion quaternion1 = pose1.pose.orientation;
    const geometry_msgs::Quaternion quaternion2 = pose2.pose.orientation;
    tf::Quaternion rot1, rot2;
    tf::quaternionMsgToTF(quaternion1, rot1);
    tf::quaternionMsgToTF(quaternion2, rot2);
    double r,p,y;
    double yaw;
    tf::Matrix3x3 mat1(rot1);
    tf::Matrix3x3 mat2(rot2);
    mat1.getEulerYPR(y,p,r);
    yaw = y;
    mat2.getEulerYPR(y,p,r);
    yaw -= y;
    return yaw;
}

inline double GetYaw(const geometry_msgs::PoseStamped &pose) {
    const geometry_msgs::Quaternion quaternion = pose.pose.orientation;
    tf::Quaternion q;
    tf::quaternionMsgToTF(quaternion, q);
    double r,p,y;
    tf::Matrix3x3 mat(q);
    mat.getEulerYPR(y,p,r);
    return y;
}

inline double GetShortestYawSigned(const double yaw2, const double yaw1) {
    if(yaw2 == yaw1){
        return 0.01;
    } else {
      double x = remainder(yaw2 - yaw1,6.283184);
      if(-3.141592 <= x && x <= 3.141592){
        return x;
      } else if(x > 3.141592){
        return x - 6.283184;
      } else {
        return 6.283184 - x; 
      }
    }
}



/*
inline double GetAngle(const geometry_msgs::PoseStamped &pose1,
                  const geometry_msgs::PoseStamped &pose2) {
    const geometry_msgs::Quaternion quaternion1 = pose1.pose.orientation;
    const geometry_msgs::Quaternion quaternion2 = pose2.pose.orientation;
    tf::Quaternion rot1, rot2;
    tf::quaternionMsgToTF(quaternion1, rot1);
    tf::quaternionMsgToTF(quaternion2, rot2);
    //return rot1.angleShortestPath(rot2);
    return rot1.angle(rot2);
}
*/
template <class T>
inline T Clip(T n, T lower, T upper) {
  return std::max(lower, std::min(n, upper));
}



}
}

#endif