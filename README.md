# Sensor Fusion

ROS1 Noetic robot localization and sensor fusion implementation for the Automaton mobile robot.

This repository contains the original ROS1/Catkin packages from the `ros-noetic` branch:

- `src/sensor_fusion` - EKF/UKF-based robot localization package
- `src/robot_description` - ROS1 robot description, Gazebo launch files, URDF, meshes, controller config, and RViz config

## Sensor Fusion

Sensor fusion in the context of robot localization. This package takes in continuous data from IMU and wheel odometry in arbitrary number, to get a better estimate of position state of the robot. The fusion can be carried out in both two dimensional movement and three dimensional movement. The appropriate configuration can be enabled in the parameter file attached below.

### Config Parameter File

- `src/sensor_fusion/config/sensor_fusion.yaml` - configuration file to setup sensor fusion settings

### Subscribed Topics

- `/automaton_velocity_controller/odom` (`nav_msgs/Odometry`)
- `/imu/data` (`sensor_msgs/Imu`)

### Published Topics

- `/odometry/filtered` (`nav_msgs/Odometry`)

### Dependencies - Trajectory Plotter

Subscriptions:

- `/robot-namespace/odom` (`nav_msgs/Odometry`) - odometry from the wheel encoder with measurement noise
- `/ground_truth/state` (`nav_msgs/Odometry`) - ground truth data from Gazebo
- `/odometry/filtered` (`nav_msgs/Odometry`) - fused and filtered output from the sensor fusion package

Published paths:

- `/odom_path` (`nav_msgs/Path`) - odometry data stringed together as path history
- `/ground_truth_odom` (`nav_msgs/Path`) - ground truth data stringed together as path history
- `/ekf_path` (`nav_msgs/Path`) - EKF filtered data stringed together as path history

## Preview

<img height="470" width="700" src="src/sensor_fusion/resources/anim.gif">

- Red line - filtered path
- Dark yellow line - ground truth
- Green line - odometry data

It is evident that when the robot keeps a straight line the filtered path in red is close to the ground truth in yellow. But as soon as the robot performs a rotational maneuver the filtered path deviates from the ground truth. Nonetheless, the filtered path represents the position of the robot far better than the raw odometry data in green.

## Repository Layout

```text
src/
├── robot_description/
│   ├── config/
│   ├── launch/
│   ├── meshes/
│   ├── rviz_config/
│   └── urdf/
└── sensor_fusion/
    ├── config/
    ├── include/sensor_fusion/
    ├── launch/
    ├── resources/
    ├── src/
    └── srv/
```

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
