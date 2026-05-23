// Moderate Exercise - Parameterized Robot Status Publisher
//
// Requirements:
//   1. Declare parameter `rate_hz` with default 1.0.
//   2. Reject rate_hz <= 0.0 by throwing std::runtime_error.
//   3. Publish std_msgs/msg/String on `/robot/status_text`.
//   4. Maintain an internal counter.
//   5. Add a std_srvs/srv/Trigger service named `reset_counter` that resets
//      the counter and reports success.

#include <chrono>
#include <stdexcept>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"

using namespace std::chrono_literals;

class RobotStatusPublisher : public rclcpp::Node {
public:
    RobotStatusPublisher()
        : rclcpp::Node("robot_status_publisher")
    {
        // TODO: declare and read rate_hz.
        // TODO: validate rate_hz > 0.0.
        // TODO: create publisher on /robot/status_text.
        // TODO: create reset_counter service.
        // TODO: create wall timer using rate_hz.
    }

private:
    void publish_status() {
        // TODO: publish "status count=<counter>" and increment counter.
    }

    // TODO: add publisher, timer, service, and counter members.
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotStatusPublisher>());
    rclcpp::shutdown();
    return 0;
}

