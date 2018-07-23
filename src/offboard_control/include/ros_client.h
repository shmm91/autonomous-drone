#ifndef ROS_CLIENT_H
#define ROS_CLIENT_H

#include "collision_avoid.h"
#include "drone_control.h"

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/Image.h>

class DroneControl; // Forward declaration because of circular reference

class ROSClient
{
  public:
    ROSClient(int &argc, char **argv);

    void init(DroneControl *const drone_control);

    ros::Subscriber state_sub_;
    ros::Subscriber marker_pos_sub_;
    ros::Subscriber local_pos_sub_;
    ros::Subscriber svo_pos_sub_;
    ros::Subscriber depth_cam_sub_;

    ros::Publisher vision_pos_pub_;
    ros::Publisher svo_cmd_pub_;

    ros::ServiceClient arming_client_;
    ros::ServiceClient land_client_;
    ros::ServiceClient set_mode_client_;

    void depth_cam_cb(const sensor_msgs::Image::ConstPtr& msg);
    void publishSetpoint(const geometry_msgs::PoseStamped& setpoint_pos_ENU);

  private:
    ros::NodeHandle *nh_;
    ros::Publisher setpoint_pos_pub_;

    CollisionAvoid collision_avoid_;
    sensor_msgs::Image depth_cam_img_;
};

#endif /* ROS_CLIENT_H */
