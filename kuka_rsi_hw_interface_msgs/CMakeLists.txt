cmake_minimum_required(VERSION 2.8.3)
project(kuka_rsi_hw_interface_msgs)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib_msgs
  message_generation
  roscpp
  rospy
  std_msgs
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  SetIO.srv
)

generate_messages(
  DEPENDENCIES
  actionlib_msgs
  std_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime)

include_directories(
  ${catkin_INCLUDE_DIRS}
)