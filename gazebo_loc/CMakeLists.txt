cmake_minimum_required(VERSION 2.8.3)
project(gazebo_loc)

##Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  std_msgs
  geometry_msgs
  nav_msgs
  sensor_msgs

)

##Declare a catkin package
catkin_package()

##Build
include_directories(include
${catkin_INCLUDE_DIRS})

add_executable(gazebo_loc 
  src/localization.cpp
)

target_link_libraries(gazebo_loc
${catkin_LIBRARIES})