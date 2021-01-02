#! /usr/bin/env python

import rospy
from geometry_msgs.msg import PoseStamped, Quaternion
from tf.transformations import quaternion_from_euler
import csv

rospy.init_node('rotate_husky')
pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=1)

filePath = rospy.get_param('~targetgoal_csv')
targetPos = []

with open(filePath) as csv_file:
  csv_reader = csv.reader(csv_file, delimiter=',')
  for row in csv_reader:
    targetPos = [float(row[0]), float(row[1]), float(row[2])]

target = PoseStamped()
target.header.frame_id = "odom"
target.header.stamp = rospy.Time.now()

target.pose.position.x = targetPos[0]
target.pose.position.y = targetPos[1]
target.pose.position.z = targetPos[2]

q = quaternion_from_euler(0.0, 0.0, 0.0)
target.pose.orientation = Quaternion(*q)

shutdown = False
while not shutdown:
  connections = pub.get_num_connections()
  if connections > 0:
    pub.publish(target)
    shutdown = True
    print "Goal has been published to Move Base Node"
  else:
    rospy.sleep(0.5)


  
