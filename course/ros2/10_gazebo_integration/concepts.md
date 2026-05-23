# ROS2 Module 10 - Gazebo Integration

## Goal

Use Gazebo as an integration environment while keeping simulation-specific wiring separate from production logic.

## Integration Boundaries

Gazebo provides physics, robot model execution, simulated sensors, and control interfaces. ROS2 nodes should consume the same style of interfaces they would consume on hardware.

## Sim Time

Simulation uses `/clock`. Nodes using `use_sim_time` must handle startup ordering and time jumps correctly.

## Bridges

Bridges translate between Gazebo transport and ROS2 topics. Bridge configuration is integration wiring, not business logic.

## Capstone Direction

Run the `robot_monitor` and sensor-health pipeline against the repository's robot simulation.

