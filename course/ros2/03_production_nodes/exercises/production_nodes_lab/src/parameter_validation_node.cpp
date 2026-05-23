// Moderate Exercise - Parameter Validation Node
//
// TODO:
//   1. Declare input_topic, output_topic, expected_rate_hz, stale_timeout_ms.
//   2. Reject invalid values.
//   3. Publish a startup status message on output_topic.

#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("parameter_validation_node");
    // TODO: implement validation and publisher.
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

