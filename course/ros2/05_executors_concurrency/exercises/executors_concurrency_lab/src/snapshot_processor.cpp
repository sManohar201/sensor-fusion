// Moderate Exercise - Snapshot Processor
// TODO: subscriber stores latest message under mutex; timer copies snapshot
// under lock, releases lock, then publishes processed status.
#include "rclcpp/rclcpp.hpp"
int main(int argc, char** argv) { rclcpp::init(argc, argv); auto node = std::make_shared<rclcpp::Node>("snapshot_processor"); rclcpp::spin(node); rclcpp::shutdown(); return 0; }

