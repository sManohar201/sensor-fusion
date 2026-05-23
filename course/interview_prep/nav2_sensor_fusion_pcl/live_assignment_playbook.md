# Live Assignment Playbook

The live round is not only testing whether you know a library. It is testing whether you can structure an ambiguous robotics problem, make defensible trade-offs, and communicate while designing.

## First Five Minutes

Ask clarifying questions before proposing a system:

- What is the robot operating environment: indoor, outdoor, dynamic, mapped, unmapped?
- What sensors are available: 2D LiDAR, 3D LiDAR, depth camera, IMU, wheel odometry, GPS, camera, radar?
- What are the safety constraints: max speed, stopping distance, people nearby, fail-safe behavior?
- What is the assignment output: architecture, pseudocode, ROS2 nodes, debugging plan, or working code?
- What are the constraints: CPU/GPU budget, latency, update rate, memory, deployment hardware?
- What does success mean: reach goal, avoid obstacles, localize robustly, classify objects, generate map, recover from faults?

Then state your working assumptions.

## Architecture Answer Template

Use this when the problem is open-ended:

```text
I would split the system into five layers:

1. Sensor ingestion and timestamp validation
2. Frame transforms and calibration checks
3. Perception or fusion layer
4. Planning/control interface
5. Monitoring, fallback, and test harness

The main reason is to keep noisy sensor-specific logic away from planning,
and to make each failure mode observable.
```

## Nav2 Assignment Template

For a navigation assignment, propose this baseline:

- `robot_state_publisher` publishes the URDF tree.
- Wheel odometry and IMU feed `robot_localization` for `odom -> base_link`.
- AMCL, SLAM, GPS, or fused localization publishes `map -> odom`.
- Nav2 consumes `map`, TF, sensor topics, footprint, costmap params, planner params, controller params, and behavior tree XML.
- Global planner produces a path from current pose to goal.
- Controller tracks the path and emits `/cmd_vel`.
- Costmaps receive static map, obstacle data, voxel/depth/point cloud data, inflation, filters, and keepout/speed zones.
- Recovery behaviors handle stuck, blocked, oscillating, or localization-failed states.

## Sensor Fusion Assignment Template

For a fusion assignment, separate the problem into:

- State definition: pose, velocity, heading, acceleration, object track state, or landmark state.
- Prediction model: constant velocity, bicycle model, IMU propagation, wheel odom integration.
- Measurement models: GPS position, wheel odom velocity, IMU angular velocity, radar range/range-rate, camera bearing/classification, LiDAR cluster position.
- Association: nearest neighbor, Mahalanobis gating, Hungarian assignment, JPDA/MHT if ambiguity is high.
- Update: EKF, UKF, particle filter, complementary filter, factor graph, or track-level Kalman filters.
- Track management: initialize, confirm, coast, delete, merge, split.
- Time handling: interpolate, buffer, reject stale data, compensate latency.

State that covariance is not an afterthought. It decides how much each sensor is trusted and prevents overconfident fusion.

## PCL Assignment Template

For a 3D perception assignment:

- Validate input: frame, timestamp, density, range limits, NaNs.
- Crop to region of interest.
- Downsample with voxel grid.
- Remove ground or dominant plane when relevant.
- Segment obstacles with Euclidean clustering or region growing.
- Estimate shape: bounding box, convex hull, centroid, footprint projection.
- Publish outputs: `PointCloud2`, markers, obstacle array, costmap input, or tracked objects.
- Measure runtime per stage and tune the expensive steps first.

## Trade-Off Language

Use concrete trade-offs:

- "I would choose a conservative projection into the 2D costmap because false negatives are more dangerous than false positives in a hospital robot."
- "I would avoid writing transient obstacles into the static map because it corrupts long-lived localization assumptions."
- "I would downsample before clustering because clustering complexity grows quickly with point count, and centimeter-level precision is unnecessary for obstacle avoidance."
- "I would use actions for navigation because goals are long-running, preemptable, and need feedback/result semantics."
- "I would start with track-level fusion if object detectors already exist, but choose raw/factor-level fusion if calibration and timing are excellent and the problem needs maximum accuracy."

## Reliability Checklist

For every design, mention:

- Time synchronization and stale data rejection
- TF frame ownership and transform availability
- QoS profile choices for sensor streams and commands
- Parameter validation at startup
- Diagnostics for sensor freshness, localization confidence, planner failures, and command saturation
- Bag replay tests for regressions
- RViz visualization for TF, costmaps, paths, point clouds, and detections
- Degraded modes and stop behavior

## Common Failure Modes

| Symptom | Likely Causes | Debug Path |
|---|---|---|
| Robot refuses to plan | Missing map, invalid pose, blocked global costmap, wrong footprint, planner plugin failed | Check `/tf`, initial pose, costmap topics, planner logs |
| Robot spins or oscillates | Bad controller tuning, poor localization, obstacle inflation too aggressive, velocity limits inconsistent | Inspect local plan, odom, controller server logs |
| Obstacles appear behind robot | Wrong sensor frame, bad extrinsics, timestamp mismatch | Check TF tree, `ros2 run tf2_ros tf2_echo`, RViz fixed frame |
| Robot hits dynamic objects | Costmap not receiving sensor data, obstacle layer params wrong, clearing too aggressive | Inspect obstacle layer topics, marking/clearing, raytrace limits |
| Fusion estimate jumps | Bad covariance, out-of-sequence data, wrong frame, association error | Plot innovations, reject stale messages, validate frames |
| Point cloud pipeline too slow | Too many points, no ROI, expensive clustering, copies between CPU/GPU | Add timing, crop/downsample early, avoid unnecessary conversions |

