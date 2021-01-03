#CHIRONIX HUSKY 

##Introduction

- This is a ROS package - Developed as part of a job interview test.
- Two ROS nodes (one in c++ and the other in python) have been developed which are able to read a 3D position within a 3D map and command the ROS Move Base package to command a Clearpath Husky robot to plan an autnomous trajectory to reach that target goal. 
- The CSV file with the target goal can be found in the assets folder

##How to run
- Setup a catkin workspace within your linux distribution with ROS Melodic
- Navigate to your src folder within the catkin workspace and clone this project 
- In the same src folder also clone the Husky package from [Clear path Husky github repo](https://github.com/husky/husky)
- navigate to your catkin workspace root folder and build the packages with `catkin_make`. Do not forget to source the setup.bash located in your /devel folder
- Then run the following commands in separate terminal windows to get the python node to work.

To start the gazebo simulation for the husky robot 

 `roslaunch husky_gazebo husky_playpen.launch`

To start RViz 

 `roslaunch husky_viz view_robot.launch`

To start the MoveBase node and the rotate_husky.py python node 

 `roslaunch chironix_husky husky_rotate_py.launch`

- To test the c++ node, first ctrl+c on all the terminals 
- In the third terminal window where you entered the third command seen above enter the following

 `roslaunch chironix_husky husky_rotate_cpp.launch`


##Methodology
Both cpp and python nodes have been implemented with the same methodlogy. 
The `move_base` node subscribes to the `move_base_simple/goal` topic on startup to recieve simple pose goals in the type of `geometery_msg/PoseStamped`. So the two nodes after startup first set up a publisher to the same above topic. Then locates the csv file with the 3D position and reads the file and creates a msg that matches the format of `geometery_msg/PoseStamped`. Once this is successful this message is published once.

Upon receiving the message `move_base` node with the help of its navigation stack plans an autonomous path to get to that given goal pose.

####Author - Jerome Justin - Robotics & Automation Software Engineer




