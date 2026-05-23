// Hard Exercise - robot_monitor Prototype
//
// Requirements:
//   1. Subscribe to a configurable status topic.
//   2. Track the last time a message was received.
//   3. Declare `stale_timeout_ms` and `check_period_ms`.
//   4. Publish `/robot/monitor_summary` as std_msgs/msg/String.
//   5. Report OK before timeout and STALE after timeout.
//   6. Use node time, not std::chrono wall time, for freshness checks.

#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class RobotMonitorPrototype : public rclcpp::Node {
public:
    RobotMonitorPrototype()
        : rclcpp::Node("robot_monitor_prototype")
    {
        // TODO: declare parameters:
        //   input_topic default "/robot/status_text"
        //   stale_timeout_ms default 1000
        //   check_period_ms default 200
        //
        // TODO: validate stale_timeout_ms and check_period_ms > 0.
        // TODO: subscribe to input_topic.
        // TODO: publish /robot/monitor_summary.
        // TODO: create timer for periodic health checks.
    }

private:
    void on_status(const std_msgs::msg::String& msg) {
        // TODO: store last message text and last receive time.
        (void)msg;
    }

    void check_health() {
        // TODO: publish OK or STALE summary.
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotMonitorPrototype>());
    rclcpp::shutdown();
    return 0;
}

