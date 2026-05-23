# ROS2 Module 06 - Sensor Integration

## Goal

Integrate real or simulated robot sensor streams with correct timestamps, frames, QoS, and health monitoring.

## Sensor Topics

Common sensor streams:

- `/imu/data`
- `/odom`
- `/front_laser/scan`
- `/top_lidar_3d/points`
- `/gps/fix`

Each stream has semantics beyond its message type: rate, frame, timestamp source, covariance, and failure modes.

## Timestamps

Timestamps define when data was measured, not when it was processed. Field systems must reason about stale data and time synchronization.

With simulation, `use_sim_time` changes the node clock source. Nodes must be tested under both wall time and sim time assumptions.

## Frames and TF2

Spatial data must have a frame. Consumers need transforms between `map`, `odom`, `base_link`, and sensor frames.

Incorrect frame IDs can make valid numeric data useless.

## Message Rates

Monitoring expected rate is a production requirement. A topic can exist and still be unhealthy if it publishes too slowly or irregularly.

## Gazebo Introduction

This is the first point where Gazebo topics should enter the course. Use simulation as an integration target after students understand ROS2 graph, packages, lifecycle, QoS, and concurrency.

## Capstone Direction

Build a sensor health and synchronization pipeline that subscribes to IMU, odom, and scan; validates frame IDs; tracks rates and stale inputs; publishes sensor health; and runs against synthetic publishers first, then Gazebo.

