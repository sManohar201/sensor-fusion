// Moderate Exercise - Package Boundary Review
//
// Implement a node that publishes a text report describing package ownership:
//   - interfaces package
//   - monitoring package
//   - bringup package
//   - description package
//
// TODO:
//   1. Publish std_msgs/msg/String on /architecture/package_report.
//   2. Declare parameter robot_name.
//   3. Include robot_name in the report.
//   4. Publish periodically at 1 Hz.

#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("package_boundary_review");
    // TODO: implement publisher and timer.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

