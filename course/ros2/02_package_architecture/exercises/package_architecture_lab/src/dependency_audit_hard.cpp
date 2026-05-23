// Hard Exercise - Dependency Audit
//
// Implement a dependency audit tool as a ROS2 node.
//
// TODO:
//   1. Model package dependencies in code.
//   2. Detect forbidden dependencies:
//      - interfaces -> application packages
//      - description -> monitoring/navigation packages
//      - cyclic dependency examples
//   3. Publish a summary on /architecture/dependency_audit.
//   4. Print actionable diagnostics.

#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("dependency_audit_hard");
    // TODO: implement audit model and publisher.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

