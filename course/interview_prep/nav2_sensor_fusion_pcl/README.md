# C++, ROS2 Architecture, Nav2, Sensor Fusion, and PCL Interview Prep

This track is built for a live robotics software assignment round where the interviewer cares about open-ended problem solving, trade-offs, reliable system design, and clear communication.

It is tailored to Sabari's resume themes:

- Real-time C++ robotics systems on Jetson, STM32, QNX, dSPACE, and embedded deployment targets
- ROS2 package architecture, lifecycle, QoS, TF, diagnostics, testing, and deployment design
- ROS2 + Nav2 navigation stack for hospital UV disinfection robots
- RealSense point cloud processing projected into Nav2 costmaps
- Radar, camera, and LiDAR track-level fusion with Mahalanobis gating and Hungarian assignment
- Production trade-offs: latency, safety margin, degraded modes, calibration, observability, and field debugging

## How to Use This Track

Read in this order:

1. [Live Assignment Playbook](live_assignment_playbook.md)
2. [C++ Robotics Interview Deep Dive](cpp_robotics_interview_deep_dive.md)
3. [ROS2 Sound Architecture Design](ros2_architecture_design.md)
4. [Nav2 Deep Dive](nav2_deep_dive.md)
5. [Sensor Fusion Deep Dive](sensor_fusion_deep_dive.md)
6. [PCL and Point Cloud Pipeline Deep Dive](pcl_pointcloud_deep_dive.md)
7. [Interview Drills](interview_drills.md)

For each topic, practice saying the answer out loud in this structure:

1. State the goal and constraints.
2. Name the architecture.
3. Explain data flow.
4. Explain timing, frames, and failure handling.
5. Defend trade-offs.
6. Mention how you would test and debug it.

## Core Interview Positioning

Your strongest positioning is not "I know ROS2 APIs" or "I know C++ syntax." It is:

> I can turn messy robotics requirements into reliable C++ and ROS2 systems with clear ownership, testable algorithms, explicit interfaces, measurable latency, and field-debuggable failure modes.

Use that theme repeatedly.

## Two-Week Study Plan

| Day | Focus | Output |
|---|---|---|
| 1 | C++ ownership and RAII | Explain `unique_ptr`, `shared_ptr`, references, RAII, and failure-safe teardown |
| 2 | C++ interfaces and error handling | Design typed structs and status-return APIs for a point-cloud projector |
| 3 | C++ performance and concurrency | Explain copies, preallocation, locks, callback blocking, and bounded queues |
| 4 | ROS2 package and node architecture | Draw package boundaries for perception, localization, navigation, and bringup |
| 5 | ROS2 communication design | Defend topic/service/action/QoS/lifecycle choices |
| 6 | ROS2 TF, parameters, diagnostics, tests | Explain how to make a system observable and testable |
| 7 | Nav2 architecture | Draw full stack from sensors to `/cmd_vel` from memory |
| 8 | Costmaps and behavior trees | Explain obstacle insertion, inflation, recovery, and replanning |
| 9 | Localization and sensor fusion | Explain EKF/UKF, covariance, timestamp alignment, and gating |
| 10 | PCL pipelines | Explain ground removal, filtering, clustering, projection, and performance |
| 11 | Live assignment design | Solve two drills with architecture diagrams and trade-offs |
| 12 | Debugging and testing | Prepare bag replay, RViz, TF, diagnostics, and CI stories |
| 13 | Resume defense | Convert each resume bullet into a design story with trade-offs |
| 14 | Mock interview | Answer assignment prompts without reading notes |

## Must-Be-Able-To-Explain Topics

- Why RAII matters in robotics drivers and hardware interfaces.
- When to use references, raw pointers, `unique_ptr`, `shared_ptr`, and values.
- How to design a C++ API that makes frames, timestamps, covariance, and failure states explicit.
- Why pure C++ libraries should be separated from ROS2 node wrappers.
- How to choose ROS2 node and package boundaries.
- When to use topics, services, actions, parameters, lifecycle nodes, and TF.
- How QoS choices affect sensor streams, maps, commands, and diagnostics.
- Why Nav2 uses actions for navigation goals.
- How behavior trees differ from a hard-coded state machine.
- How global costmaps and local costmaps differ.
- Why obstacle inflation is not only about robot radius, but also localization error, controller tracking error, sensor noise, and braking distance.
- Why transient obstacles should usually affect costmaps, not the static map.
- What happens when TF timestamps are stale or frames are wrong.
- Why covariance is part of the measurement contract in sensor fusion.
- How Mahalanobis gating differs from Euclidean nearest-neighbor matching.
- Why point cloud downsampling can improve both speed and robustness.
- How to design degraded modes when LiDAR, depth, odom, or localization becomes unreliable.
