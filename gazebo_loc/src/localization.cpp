#include "ros/ros.h"
#include <tf/transform_broadcaster.h>

#include <sstream>

#include "gazebo_msgs/ModelStates.h"

struct robot_state
{
    double pos_x;
    double pos_y;
    double pos_z;

    double quat_x;
    double quat_y;
    double quat_z;
    double quat_w;
};

robot_state robot;


void robotCallback(const gazebo_msgs::ModelStates state)
{
    robot.pos_x = state.pose[2].position.x;
    robot.pos_y = state.pose[2].position.y;
    robot.pos_z = state.pose[2].position.z;

    robot.quat_x = state.pose[2].orientation.x;
    robot.quat_y = state.pose[2].orientation.y;
    robot.quat_z = state.pose[2].orientation.z;
    robot.quat_w = state.pose[2].orientation.w;
}
 

int main(int argc, char **argv)
{
    // check input parameters
    ros::init(argc, argv, "gazebo_localization");

    tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::NodeHandle n;

    ros::Subscriber sub_joint = n.subscribe("sub_robot_state", 1, robotCallback);
    
    std::string robot_name;
    std::string world_frame;
    double rate = 0;
    n.getParam("gazebo_loc/freq", rate);
    n.getParam("gazebo_loc/robot_name", robot_name);
    n.getParam("gazebo_loc/world_frame", world_frame);
    
    ros::Rate loop_rate(rate);
    while (n.ok())
    {
        
        transform.setOrigin( tf::Vector3(robot.pos_x, robot.pos_y, robot.pos_z) );                      
        transform.setRotation( tf::Quaternion(robot.quat_x, robot.quat_y, robot.quat_z, robot.quat_w));
    
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), world_frame, robot_name));   
        
        ros::spinOnce();
        loop_rate.sleep();
    }   
    
    return 0; 
};


