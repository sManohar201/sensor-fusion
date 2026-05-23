# Nav2 Deep Dive

Nav2 is a ROS2 navigation framework built around lifecycle-managed servers, plugins, behavior trees, costmaps, actions, and TF. In an interview, explain it as a distributed system with explicit contracts, not as one monolithic package.

## Mental Model

Nav2 turns:

```text
goal pose + map + robot pose + sensor obstacles + robot constraints
```

into:

```text
time-varying velocity commands with feedback, recovery, and safety limits
```

The key contracts are:

- TF tells Nav2 where the robot, sensors, map, and odom frames are.
- Costmaps tell Nav2 where the robot should not go.
- Planners produce feasible paths.
- Controllers convert paths into velocity commands.
- Behavior trees decide when to plan, follow, wait, clear, recover, or abort.
- Lifecycle nodes make startup, configuration, activation, and shutdown explicit.

## Core Servers

| Component | Responsibility | Interview Notes |
|---|---|---|
| BT Navigator | Owns the navigation behavior tree and action interface | Long-running goals, preemption, recovery flow |
| Planner Server | Runs global planner plugins | Usually lower frequency; map-scale reasoning |
| Controller Server | Runs local controller plugins | Higher frequency; tracks path under dynamic constraints |
| Smoother Server | Smooths paths before tracking | Useful when planner output is jagged |
| Behavior Server | Executes recovery behaviors | Spin, backup, wait, assisted teleop, custom behaviors |
| Costmap 2D | Maintains global and local costmaps | Static, obstacle, voxel, inflation, filters |
| Lifecycle Manager | Brings nodes through lifecycle transitions | Deterministic startup and restart |
| Waypoint Follower | Executes sequences of goals | Useful for coverage and inspection tasks |

## TF Frame Contract

A common production frame tree:

```text
map -> odom -> base_link -> sensor frames
```

- `odom -> base_link`: smooth local motion from wheel odom/IMU fusion.
- `map -> odom`: global correction from AMCL, SLAM, GPS, or localization.
- Sensor frames: fixed extrinsics from URDF or calibration.

Interview point:

> `odom` is locally smooth but drifts. `map` is globally meaningful but can jump when localization corrects. Splitting them protects controllers from discontinuities while still allowing global localization.

## Costmaps

Global costmap:

- Larger area
- Lower update rate
- Used by global planner
- Includes static map and longer-range obstacles

Local costmap:

- Robot-centered rolling window
- Higher update rate
- Used by controller
- Focused on near-field dynamic obstacles

Common layers:

- Static layer: occupancy grid from map server.
- Obstacle layer: 2D LiDAR, depth projection, point cloud marking and clearing.
- Voxel layer: 3D obstacle representation before 2D projection.
- Inflation layer: expands obstacle cost around lethal cells.
- Costmap filters: keepout zones, speed zones, route constraints.

Inflation should account for:

- Robot footprint
- Localization uncertainty
- Controller tracking error
- Sensor noise
- Braking distance
- Human-safety margin

## Planner and Controller Trade-Offs

Global planners:

- Grid-based planners are predictable and easy to debug.
- Sampling or optimization-based planners may handle constraints better but are more complex.
- Smac-style planners are useful when orientation, footprint, or nonholonomic constraints matter.

Controllers:

- Pure pursuit-style controllers are simple and robust for moderate speeds.
- DWB-style controllers sample velocity commands and score trajectories.
- Regulated pure pursuit adds speed regulation near curvature and obstacles.
- MPPI-style controllers optimize sampled trajectories and can handle richer costs at higher compute cost.

Interview answer:

> I would start with the simplest controller that meets the dynamics and environment. If the robot is slow indoor differential drive, regulated pure pursuit or DWB is often easier to tune and debug than a heavy optimizer. If speed, nonholonomic constraints, or obstacle-dense behavior dominates, I would evaluate MPPI with timing measurements.

## Behavior Trees

Behavior trees are used because navigation is not a straight-line function call. A robot must:

- Plan
- Follow
- Replan when blocked
- Clear costmaps when stale
- Wait
- Recover
- Abort safely

BTs make this flow inspectable and configurable without recompiling core logic.

Explain key node types:

- Sequence: all children must succeed in order.
- Fallback: try alternatives until one succeeds.
- Decorator: modify behavior, such as retry, timeout, rate control.
- Condition: checks state.
- Action: performs work.

## Resume Story: Hospital UV Robot

Use this story:

> For the hospital UV robot, I separated static localization from dynamic obstacle avoidance. AMCL used a pre-built room map for stable localization, while RealSense point clouds were filtered and projected into the Nav2 obstacle layer for transient equipment such as beds, trolleys, and drip stands. I did not update the static map with these objects because that would corrupt localization assumptions. The costmap carried transient risk; the map carried long-term structure.

Then add trade-offs:

- Conservative projection reduces collision risk but can block narrow passages.
- Full 3D projection captures complex medical equipment better than a single height slice.
- Depth cameras have range, lighting, and reflective-surface limitations, so diagnostics and degraded stop behavior are needed.

## Debugging Flow

When Nav2 fails, debug in this order:

1. TF tree and timestamps
2. Initial pose and localization confidence
3. Costmap topics in RViz
4. Footprint and inflation
5. Planner output path
6. Controller local plan and velocity limits
7. Behavior tree status
8. Lifecycle node states and logs

Useful ROS2 commands:

```bash
ros2 topic list
ros2 topic echo /tf
ros2 topic hz /scan
ros2 topic hz /cmd_vel
ros2 node list
ros2 param list /controller_server
ros2 lifecycle get /controller_server
ros2 action list
```

## Strong Interview Questions to Ask

- Is the environment mostly static, semi-structured, or highly dynamic?
- Is the robot holonomic, differential drive, ackermann, or legged?
- What is the acceptable stop distance and maximum speed?
- What sensors are safety-rated versus advisory?
- Do we need coverage, point-to-point navigation, docking, or fleet routing?
- What failures should stop the robot versus degrade behavior?

