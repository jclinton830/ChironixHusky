#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

int main(int argc, char  *argv[])
{
  ros::init(argc, argv, "rotate_node");

  // Create a private ROS node handle
  ros::NodeHandle nh, pnh("~");

  ros::Publisher pub = nh.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);

  std::string param;
  pnh.getParam("targetgoal_csv", param);

  std::fstream file;
  file.open(param, std::fstream::in);
  
  if(file.is_open()) {
    
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

    ros::Duration(1).sleep();  

    std::cout << target << std::endl;

    pub.publish(target);
  } 
  else 
  {
    std::cout << "FILE NOT FOUND" << std::endl;
  }

  ros::spin();
}
