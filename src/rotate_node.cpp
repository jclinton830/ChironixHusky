#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

#include <boost/chrono.hpp>

typedef boost::chrono::steady_clock time_source;

void rotate(std::string dir = "cw", float duration = 10.0f)
{
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("twist_marker_server/cmd_vel", 1);

  geometry_msgs::Twist twist; 
  twist.linear.x = 100.0;
  twist.linear.y = 100.0;

  if(dir == "cw")
  {
    twist.angular.z = 0.5;
  }
  else 
  {
    twist.angular.z = -0.5;
  }

  time_source::time_point start_time = time_source::now();

  bool send = true;

  while(send)
  {
    pub.publish(twist);

    boost::chrono::duration<double> elapsed = time_source::now() - start_time;
    if(elapsed.count() >= duration) send = false;
  }
  
  return;
}

geometry_msgs::PoseStamped getTargetPose(std::fstream &file)
{
  std::string line;
  std::vector<float> goalTarget;
  std::stringstream ss;

  while (getline(file, line))
  {
    std::string temp;
    // load line in stringstream
    ss << line;
    // we need for columns only so use a loop 4 times
    for (int i = 0; i < 3; i++)
    {
      getline(ss, temp, ',');
      goalTarget.push_back(std::stof(temp));
    }

    ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    ss.clear();
  }

  geometry_msgs::PoseStamped target;
  geometry_msgs::Pose pose;
  geometry_msgs::Point point;

  point.x = goalTarget[0]; 
  point.y = goalTarget[1]; 
  point.z = goalTarget[2];

  pose.position = point;
  pose.orientation = geometry_msgs::Quaternion();
  pose.orientation.w = 1.0;
  
  target.header = std_msgs::Header();
  target.header.stamp = ros::Time::now();
  target.header.frame_id = "odom";
  target.pose = pose;

  return target;
}

int main(int argc, char  *argv[])
{
  ros::init(argc, argv, "rotate_node");

  // Create a private ROS node handle
  ros::NodeHandle nh, pnh("~");

  ros::Publisher pub = nh.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);

  std::string param;
  pnh.getParam("targetgoal_csv", param);

  float duration = 10.0;//seconds

  rotate("cw", duration);
  rotate("ccw", duration);

  std::fstream file;
  file.open(param, std::fstream::in);

  if(file.is_open()) 
  {
    geometry_msgs::PoseStamped target = getTargetPose(file);
    ros::Duration(1).sleep();  

    // std::cout << target << std::endl;

    pub.publish(target);
  } 
  else 
  {
    std::cout << "FILE NOT FOUND" << std::endl;
  }

  ros::spin();
}
