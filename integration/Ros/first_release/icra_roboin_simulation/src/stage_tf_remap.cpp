#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>




class Remapper{
    public:
        Remapper(std::string ns) :ns_(ns){
            ros::NodeHandle nh;
            odom_pub_ = nh.advertise<nav_msgs::Odometry>(ns_ + "odom",10);
            scan_pub_ = nh.advertise<sensor_msgs::LaserScan>(ns_ + "scan",10);
            odom_sub_ = nh.subscribe(ns_+"base_odom",10,&Remapper::odomCB,this);
            scan_sub_ = nh.subscribe(ns_+"base_scan",10,&Remapper::scanCB,this);
        }
        ~Remapper() = default;

        void odomCB(const nav_msgs::OdometryConstPtr& msg){
            nav_msgs::Odometry msg_copy = *msg;
            msg_copy.header.frame_id = ns_ + "base_link";
            msg_copy.child_frame_id = ns_ + "base_footprint";
            odom_pub_.publish(msg_copy);
        }
        void scanCB(const sensor_msgs::LaserScanConstPtr& msg){
            sensor_msgs::LaserScan msg_copy = *msg;
            msg_copy.header.frame_id = ns_ + "base_laser_link";
            scan_pub_.publish(msg_copy);
        }



    private:
        ros::Subscriber odom_sub_;
        ros::Subscriber scan_sub_;
        ros::Publisher odom_pub_;
        ros::Publisher scan_pub_;
        const std::string ns_;



};









int main(int argc, char** argv)
{
    ros::init(argc,argv,"stage_tf_remap");
    ros::NodeHandle nh("~");
    Remapper* rp0;
    Remapper* rp1;
    Remapper* rp2;
    Remapper* rp3;

    int count;
    nh.getParam("robot_count",count);
    if(count >= 4){
        rp3 = new Remapper("robot_3/");
    }
    if(count >= 3){
        rp2 = new Remapper("robot_2/");
    }
    if(count >= 2){
        rp1 = new Remapper("robot_1/");
    }
    if(count >= 1){
        rp0 = new Remapper("robot_0/");
    } else {
        ROS_ERROR("stage tf remapper error");
        return 1;
    }
    ros::spin();
    delete rp3;
    delete rp2;
    delete rp1;
    delete rp0;
    return 0;
}
