// Moderate Exercise - QoS Status Publisher
// TODO: publish /robot/status with transient-local QoS so late subscribers
// receive the last status.
#include "rclcpp/rclcpp.hpp"
int main(int argc, char** argv) { rclcpp::init(argc, argv); auto node = std::make_shared<rclcpp::Node>("qos_status_publisher"); rclcpp::spin(node); rclcpp::shutdown(); return 0; }

