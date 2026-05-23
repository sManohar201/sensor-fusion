# Sensor Fusion

ROS1 Noetic robot localization and sensor fusion implementation for the Automaton mobile robot.

This repository contains the original ROS1/Catkin packages from the `ros-noetic` branch:

- `src/sensor_fusion` - EKF/UKF-based robot localization package
- `src/robot_description` - ROS1 robot description, Gazebo launch files, URDF, meshes, controller config, and RViz config

## Sensor Fusion Package

Sensor fusion in the context of robot localization. This package takes continuous IMU and wheel odometry data and estimates a better robot pose state. The fusion can be configured for two-dimensional or three-dimensional motion through the parameter file.

### Config

- `src/sensor_fusion/config/sensor_fusion.yaml` - sensor fusion settings

### Subscribed Topics

- `/automaton_velocity_controller/odom` (`nav_msgs/Odometry`)
- `/imu/data` (`sensor_msgs/Imu`)

### Published Topics

- `/odometry/filtered` (`nav_msgs/Odometry`)

### Trajectory Plotter Topics

Subscriptions:

- `/robot-namespace/odom` (`nav_msgs/Odometry`) - wheel odometry with measurement noise
- `/ground_truth/state` (`nav_msgs/Odometry`) - Gazebo ground truth
- `/odometry/filtered` (`nav_msgs/Odometry`) - fused output from the sensor fusion package

Published paths:

- `/odom_path` (`nav_msgs/Path`) - raw odometry path history
- `/ground_truth_odom` (`nav_msgs/Path`) - ground truth path history
- `/ekf_path` (`nav_msgs/Path`) - EKF filtered path history

## Preview

<img height="470" width="700" src="src/sensor_fusion/resources/anim.gif">

- Red line: filtered path
- Dark yellow line: ground truth
- Green line: odometry data

When the robot moves in a straight line, the filtered path stays close to ground truth. During rotational maneuvers, the filtered path deviates, but it still represents the robot position better than raw odometry.

## Build

```bash
mkdir -p catkin_ws/src
cd catkin_ws/src
git clone git@github.com:sManohar201/sensor-fusion.git .
cd ..
catkin_make
source devel/setup.bash
```

## Launch

```bash
roslaunch robot_description gazebo_automaton.launch
roslaunch sensor_fusion sensor_fusion.launch
```
