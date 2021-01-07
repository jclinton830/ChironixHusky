cmake_minimum_required(VERSION 3.0.2)
project(chironix_husky)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  move_base_msgs
)

# ## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   geometry_msgs
# )

#catkin config
catkin_package(
 LIBRARIES chironix_husky
 CATKIN_DEPENDS roscpp rospy std_msgs message_runtime geometry_msgs move_base_msgs
 DEPENDS system_lib
)

# build
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(rotate_node src/rotate_node.cpp)

set_target_properties(rotate_node PROPERTIES COMPILE_FLAGS "-std=c++17")

target_link_libraries(rotate_node ${catkin_LIBRARIES})

add_dependencies(rotate_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
