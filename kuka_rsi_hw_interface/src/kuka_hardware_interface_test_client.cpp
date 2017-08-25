//
// Created by adamleon on 25.08.17.
//

#include "ros/ros.h"
#include "kuka_rsi_hw_interface_msgs/SetIO.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "kuka_rsi_hw_interface_test_client");


  ros::NodeHandle n;
  ros::ServiceClient client_ag1 = n.serviceClient<kuka_rsi_hw_interface_msgs::SetIO>("ag1/set_io");
  ros::ServiceClient client_ag2 = n.serviceClient<kuka_rsi_hw_interface_msgs::SetIO>("ag2/set_io");
  kuka_rsi_hw_interface_msgs::SetIO srv;
  std::map<std::string, bool> test;

  ros::Rate r(0.5);

  while(ros::ok()) {
    test.clear();
    test["02"] = true;
    test["03"] = true;
    test["05"] = false;
    test["06"] = false;

    std::vector<std::string> keys;
    std::vector<uint8_t > values;
    for (auto t : test) {
      keys.push_back(t.first);
      values.push_back(t.second?1:0);
    }

    srv.request.io_name = keys;
    srv.request.io_value = values;
    if (client_ag1.call(srv)) {
      ROS_INFO("Got response for ag1 opening gripper");
    } else {
      ROS_ERROR("Failed to call service set_io");
      return 1;
    }
    if (client_ag2.call(srv)) {
      ROS_INFO("Got response for ag2 opening gripper");
    } else {
      ROS_ERROR("Failed to call service set_io");
      return 1;
    }

    r.sleep();

    test.clear();
    test["02"] = false;
    test["03"] = false;
    test["05"] = true;
    test["06"] = true;

    keys.clear();
    values.clear();
    for (auto t : test) {
      keys.push_back(t.first);
      values.push_back(t.second?1:0);
    }

    srv.request.io_name = keys;
    srv.request.io_value = values;
    if (client_ag1.call(srv)) {
      ROS_INFO("Got response for ag1 opening gripper");
    } else {
      ROS_ERROR("Failed to call service set_io");
      return 1;
    }
    if (client_ag2.call(srv)) {
      ROS_INFO("Got response for ag2 opening gripper");
    } else {
      ROS_ERROR("Failed to call service set_io");
      return 1;
    }

    r.sleep();
  }

  return 0;
}