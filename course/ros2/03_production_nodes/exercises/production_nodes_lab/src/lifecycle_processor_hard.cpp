// Hard Exercise - Lifecycle-Style Processor
//
// TODO:
//   1. Model states: unconfigured, inactive, active, failed.
//   2. Validate config before active processing.
//   3. Subscribe only when active.
//   4. Publish DEGRADED if input becomes stale.

#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("lifecycle_processor_hard");
    // TODO: implement state machine and stale checks.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

