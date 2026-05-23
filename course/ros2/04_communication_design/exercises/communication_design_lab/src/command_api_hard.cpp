// Hard Exercise - Command and Telemetry API
// TODO: publish telemetry, expose reset service, validate command topic naming,
// and document QoS choices in code comments.
#include "rclcpp/rclcpp.hpp"
int main(int argc, char** argv) { rclcpp::init(argc, argv); auto node = std::make_shared<rclcpp::Node>("command_api_hard"); rclcpp::spin(node); rclcpp::shutdown(); return 0; }

