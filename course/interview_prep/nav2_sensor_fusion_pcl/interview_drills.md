# Interview Drills

Use these drills like a live whiteboard assignment. Spend 20 minutes designing, then 5 minutes explaining trade-offs.

## Drill 1: Hospital Robot Navigation

Prompt:

> Build a ROS2 navigation stack for an indoor hospital robot that must visit patient rooms, avoid staff and movable equipment, and stop safely on sensor failures.

Expected answer:

- Use Nav2 with map server, AMCL, planner server, controller server, behavior tree navigator, local/global costmaps, and lifecycle manager.
- Use wheel odom + IMU for `odom -> base_link`.
- Use AMCL for `map -> odom` on a pre-built static map.
- Use depth camera or 3D LiDAR point cloud projected into obstacle layer for movable equipment.
- Keep transient obstacles out of the static map.
- Add diagnostics for localization confidence, sensor freshness, costmap update rate, and command output.
- Use waypoint follower or custom coverage planner for room sequence.
- Stop or degrade when localization or obstacle sensor confidence drops.

Trade-offs to discuss:

- AMCL versus SLAM.
- 2D LiDAR versus depth camera versus 3D LiDAR.
- Conservative projection versus narrow-passage availability.
- DWB/regulated pure pursuit versus MPPI.
- Static map stability versus dynamic obstacle handling.

## Drill 2: Nav2 Fails in the Field

Prompt:

> The robot sees a goal in RViz but does not move. How do you debug it?

Answer order:

1. Check lifecycle states.
2. Check action status and BT navigator logs.
3. Check TF: `map -> odom -> base_link`.
4. Check localization and initial pose.
5. Check global and local costmaps in RViz.
6. Check footprint and inflation.
7. Check planner output.
8. Check controller output and `/cmd_vel`.
9. Check velocity limits and safety controller.
10. Reproduce with bag or launch test.

Strong closing:

> I would avoid random parameter tuning until I know which contract is broken: pose, map, costmap, planning, control, or safety gating.

## Drill 3: Radar-Camera-LiDAR Fusion

Prompt:

> Design a track-level sensor fusion system for an autonomous vehicle using radar, camera, and LiDAR.

Expected answer:

- Define common track state.
- Convert each sensor output into common measurement schema.
- Include timestamp, frame, covariance, object class, and confidence.
- Predict tracks to measurement time.
- Use Mahalanobis gating.
- Use Hungarian assignment.
- Update tracks with Kalman/EKF.
- Manage tentative, confirmed, coasted, and deleted tracks.
- Publish tracked objects and association diagnostics.

Trade-offs:

- Track-level fusion is easier to deploy than raw fusion.
- Radar is strong for range/range-rate, camera for classification/lateral cues, LiDAR for geometry.
- Bad covariance can be worse than no fusion.
- Time alignment and calibration are as important as filter equations.

## Drill 4: PCL Obstacle Projection

Prompt:

> A depth camera sees chairs and trolleys, but the robot sometimes drives too close to thin legs. Redesign the point cloud pipeline.

Expected answer:

- Check camera extrinsics and TF timestamps.
- Avoid relying on one horizontal slice.
- Use full projection or multiple height bands.
- Reduce voxel size for near-field thin objects.
- Add temporal persistence for intermittent returns.
- Inflate based on footprint and uncertainty.
- Add RViz debug layers: raw cloud, filtered cloud, projected obstacles, costmap.
- Validate with bag replay in narrow passages and cluttered rooms.

Trade-offs:

- Conservative projection reduces collision risk but may block paths.
- Smaller voxels improve detail but increase CPU cost.
- Persistence reduces flicker but can leave stale obstacles.

## Drill 5: Assignment Architecture Under Constraints

Prompt:

> You have two days to build a demo where a robot navigates a warehouse aisle using ROS2, a 2D LiDAR, wheel odometry, and an IMU. What do you build first?

Expected answer:

Day 1:

- Bring up URDF and TF.
- Validate odom and IMU topics.
- Configure robot_localization for local odom fusion.
- Configure Nav2 with map, AMCL or SLAM depending on map availability.
- Configure costmaps with 2D LiDAR obstacle layer.
- Verify in RViz.

Day 2:

- Tune footprint, inflation, controller, velocity limits.
- Add lifecycle launch and parameter validation.
- Add diagnostics for sensor freshness and localization.
- Record bags for regression.
- Prepare failure cases and recovery behavior.

Strong trade-off:

> I would not start with custom planners. I would first prove the standard stack contracts: TF, localization, costmaps, planning, control, and safety stop.

## Resume Defense Questions

Practice these until they are crisp:

1. Why did you use AMCL instead of SLAM for the hospital UV robot?
2. How did the RealSense point cloud become useful to Nav2?
3. What does "full projection onto 2D floor plane" mean?
4. What false positives and false negatives did that projection create?
5. How did you prevent transient medical equipment from corrupting the map?
6. How would you debug a bad `map -> odom` transform?
7. Why Mahalanobis gating instead of Euclidean distance?
8. How does Hungarian assignment improve multi-object association?
9. What would make you choose EKF versus UKF?
10. How would you test a point cloud obstacle pipeline without the robot?

## Crisp Answers

Why AMCL, not SLAM?

> The hospital rooms had known layouts, so AMCL on pre-built maps gave stable localization with lower operational complexity. Dynamic objects like trolleys and beds were handled as costmap obstacles, not map updates, because they are transient and should not redefine the static environment.

What is full point-cloud projection?

> Instead of taking one height slice, I transform valid 3D points into the robot/world frame, filter by useful bounds, and mark their floor-plane cells as occupied. That captures thin legs and irregular equipment footprints more conservatively for base collision avoidance.

Why Mahalanobis gating?

> Euclidean distance ignores uncertainty. Mahalanobis distance scores a measurement relative to the predicted covariance, so a radar measurement with high lateral uncertainty is treated differently from a LiDAR measurement with tight geometric uncertainty.

How do you handle stale sensor data?

> I compare message timestamps against the processing time and expected sensor rate, reject stale data, publish diagnostics, and trigger degraded behavior if the sensor is required for safety.

What makes a robotics system field-deployable?

> Clear ownership of frames and interfaces, deterministic startup, parameter validation, observable diagnostics, bag-based regression tests, bounded latency, and explicit degraded modes.

