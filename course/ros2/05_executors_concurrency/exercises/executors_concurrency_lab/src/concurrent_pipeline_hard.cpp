// Hard Exercise - Concurrent Sensor Pipeline
// TODO: use callback groups and mutex-protected caches for scan, imu, and odom
// status strings; process snapshots in a timer with bounded lock scope.
#include "rclcpp/rclcpp.hpp"
int main(int argc, char** argv) { rclcpp::init(argc, argv); auto node = std::make_shared<rclcpp::Node>("concurrent_pipeline_hard"); rclcpp::spin(node); rclcpp::shutdown(); return 0; }

