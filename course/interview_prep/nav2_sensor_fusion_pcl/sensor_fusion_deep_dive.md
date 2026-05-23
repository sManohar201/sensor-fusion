# Sensor Fusion Deep Dive

Sensor fusion combines measurements so the robot has a better estimate than any single sensor can provide. In interviews, focus on the state, measurement models, timing, uncertainty, and failure handling.

## Fusion Levels

| Level | Meaning | Example |
|---|---|---|
| Raw-data fusion | Combine sensor data before feature extraction | Fuse LiDAR points and camera pixels |
| Feature-level fusion | Combine extracted features | Fuse lane lines, object corners, cluster centroids |
| Track-level fusion | Combine object tracks from independent sensors | Radar track + camera track + LiDAR track |
| Decision-level fusion | Combine final decisions | Vision says pedestrian, radar says obstacle |

Resume angle:

> My ADAS work used track-level fusion because radar, camera, and LiDAR each had their own measurement characteristics and object outputs. Track-level fusion gave a practical interface for association, covariance handling, and deployment.

## State Definition

Before choosing EKF, UKF, or another method, define the state.

Robot localization state examples:

```text
[x, y, yaw, vx, vy, yaw_rate]
```

Object tracking state examples:

```text
[x, y, vx, vy]
[x, y, z, vx, vy, vz]
[x, y, heading, speed, yaw_rate]
```

The state should be just rich enough to support prediction and control. Extra state variables increase tuning burden and observability problems.

## Prediction and Update

Prediction:

- Uses a motion model to advance state.
- Increases uncertainty.
- Examples: constant velocity, constant turn rate, bicycle model, IMU propagation.

Update:

- Uses measurements to correct state.
- Reduces uncertainty when the measurement is consistent.
- Requires measurement model and covariance.

Interview phrase:

> The filter prediction answers "where should I be now if my model is right?" The update answers "how much should I trust this measurement relative to my prediction?"

## Covariance

Covariance represents uncertainty and coupling between state variables.

Common mistakes:

- Setting covariance unrealistically low.
- Ignoring sensor-dependent noise.
- Mixing frames without transforming covariance.
- Treating classification confidence as geometric certainty.

Strong answer:

> I tune covariance from sensor specs, empirical residuals, and failure behavior. If the system becomes jumpy, I check innovation distributions and whether a sensor is overconfident.

## Association

Association decides which measurement belongs to which track.

Euclidean nearest neighbor:

- Simple
- Fast
- Fails when uncertainty differs by direction or sensor

Mahalanobis gating:

- Uses covariance
- Creates an ellipsoidal gate
- Rejects measurements inconsistent with predicted uncertainty

Hungarian assignment:

- Solves global one-to-one matching
- Avoids greedy local mistakes
- Useful when multiple tracks and detections are close

Resume answer:

> In the radar-camera-LiDAR fusion pipeline, I used Mahalanobis distance gating to reject unlikely associations and the Hungarian algorithm to choose the globally consistent assignment among remaining candidates.

## Time Synchronization

Fusion quality often fails because of time, not math.

Handle:

- Sensor timestamps versus receive time
- Clock synchronization
- Latency compensation
- Out-of-sequence measurements
- Buffering and interpolation
- Rejecting stale data

Rule:

> Never fuse data unless you know what time and frame it represents.

## Robot Localization Fusion

Typical ROS2 localization split:

- Wheel odometry + IMU -> smooth `odom -> base_link`
- AMCL/SLAM/GPS -> global `map -> odom`

This protects local control from global jumps.

Use `robot_localization` concepts:

- EKF for locally smooth odometry fusion
- Sensor config masks for which variables each sensor observes
- Differential or relative modes where appropriate
- Separate local and global filters when GPS or map corrections exist

## Object Fusion Pipeline

Example track-level fusion architecture:

```text
Radar detections       Camera detections       LiDAR clusters
      |                      |                       |
sensor-specific adapter  sensor-specific adapter  sensor-specific adapter
      |                      |                       |
common detection message with pose, covariance, class, timestamp, frame
      |
prediction -> gating -> assignment -> update -> track management
      |
tracked objects + diagnostics + visualization
```

Track management:

- Tentative track after first detection
- Confirmed after repeated hits
- Coast when temporarily missing
- Delete after timeout or high uncertainty

## Failure Modes

| Failure | Cause | Mitigation |
|---|---|---|
| Jumpy pose | Overconfident global updates | Increase covariance, split map/odom, reject outliers |
| Ghost tracks | Poor deletion/coasting logic | Track age, hit count, missed count |
| Merged tracks | Association ambiguity | Better gating, class constraints, shape cues |
| Delayed response | Latency not compensated | Timestamp correctly, predict to common time |
| Sensor dominates fusion | Bad covariance | Tune from residuals and sensor limits |
| Frame-dependent errors | Bad extrinsics or transform | Calibrate, validate TF, add static checks |

## Choosing a Fusion Method

Use this decision table:

| Situation | Good Starting Point |
|---|---|
| Linear-ish dynamics, Gaussian noise | Kalman filter |
| Nonlinear measurement or motion model | EKF |
| Strong nonlinearity, moderate state size | UKF |
| Multi-modal localization | Particle filter |
| Offline smoothing or SLAM | Factor graph |
| Multiple object sensors with existing detections | Track-level fusion |

## Interview Drill Answer

Question:

> How would you fuse radar, camera, and LiDAR for obstacle tracking?

Answer outline:

1. Define common object state: position and velocity in a shared vehicle frame.
2. Convert each sensor detection into a common measurement format with timestamp, frame, covariance, and class.
3. Predict existing tracks to the measurement time.
4. Apply Mahalanobis gating per track-measurement pair.
5. Use Hungarian assignment for globally consistent matching.
6. Update assigned tracks with Kalman/EKF updates.
7. Initialize tentative tracks for unmatched detections.
8. Coast and delete stale tracks.
9. Publish tracked objects and diagnostics.
10. Validate with bag replay, innovation plots, association visualization, and corner cases.

