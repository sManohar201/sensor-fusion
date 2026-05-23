# ROS2 Sound Architecture Design

Sound ROS2 architecture means the robot is understandable, testable, observable, and recoverable. It is not just splitting code into many nodes.

## Architecture Principle

Use this as your default answer:

> I separate pure robotics logic from ROS2 transport. ROS2 nodes own communication, parameters, lifecycle, and diagnostics. Libraries own algorithms. That makes the system easier to test, reuse, and debug.

## Node Boundary Rules

Create a separate node when:

- It has a different lifecycle.
- It has a different rate or timing constraint.
- It may fail independently.
- It talks to hardware.
- It has a clear interface useful to other packages.
- It needs separate CPU scheduling or composition.

Do not create a separate node when:

- It only wraps one helper function.
- It creates unnecessary serialization and latency.
- It splits tightly coupled state across topics.
- It makes debugging harder without improving ownership.

## Package Boundary Rules

Good package split:

```text
robot_interfaces        custom messages/actions/services
robot_bringup           launch and parameter orchestration
robot_description       URDF, meshes, frames
perception_core         pure C++ perception algorithms
perception_ros          ROS2 nodes wrapping perception_core
localization_core       filters, math, measurement adapters
localization_ros        ROS2 localization nodes
navigation_config       Nav2 params, behavior trees, maps
diagnostics             health checks and fault summaries
```

Interview point:

> Interface packages should be stable and small because changing messages has a large blast radius.

## Communication Choices

| Need | ROS2 Primitive | Reason |
|---|---|---|
| Streaming sensor data | Topic | Many consumers, time series data |
| Request immediate calculation | Service | Short synchronous request-response |
| Long-running preemptable task | Action | Feedback, cancel, result |
| Runtime tuning | Parameters | Explicit configuration surface |
| Coordinate transforms | TF2 | Time-indexed frame relationship |
| Startup orchestration | Launch | Bringup variants and configuration |
| Managed state | Lifecycle node | Deterministic configure/activate/deactivate |

Examples:

- Navigation goal: action.
- Set camera exposure once: service or parameter.
- Point cloud stream: topic.
- Robot mode transition: service or action depending on duration.
- Planner plugin choice: parameter.

## QoS Design

Use QoS intentionally:

- Sensor streams: best effort, volatile, small queue, because stale data is harmful.
- Commands: reliable when command loss is unacceptable, but monitor freshness.
- Maps: transient local, reliable, because late subscribers need the latest map.
- Diagnostics: reliable enough for operators, but not in the control hot path.

Strong phrase:

> QoS is part of the system contract. A wrong QoS profile can look like a perception bug because messages silently do not connect or arrive too late.

## Lifecycle Design

Lifecycle nodes are useful when startup order matters:

```text
unconfigured -> inactive -> active -> finalized
```

Use lifecycle transitions to:

- Validate parameters.
- Allocate resources.
- Connect hardware.
- Start publishers/subscribers/timers.
- Stop safely.
- Release resources.

For a robot stack:

1. Configure drivers.
2. Configure localization.
3. Configure perception.
4. Configure Nav2.
5. Activate only after TF, map, and required sensors are available.

## Parameters

Good parameter design:

- Validate at startup.
- Reject invalid runtime updates.
- Keep units in names or docs.
- Group related parameters.
- Record parameter files with experiments.

Bad parameter design:

- Magic numbers inside callbacks.
- Parameters with unclear units.
- Runtime changes that break invariants.
- Different launch files with duplicated inconsistent values.

## TF Architecture

Own every transform explicitly:

- URDF/static transforms: `robot_state_publisher` or static transform publisher.
- `odom -> base_link`: odometry/local filter.
- `map -> odom`: localization/global correction.
- Sensor extrinsics: URDF or calibrated static transforms.

Common mistakes:

- Two nodes publish the same transform.
- Frame IDs differ by typo.
- Transform exists but not at the message timestamp.
- Using `base_footprint`, `base_link`, `odom`, and `map` inconsistently.

## Observability

Every production ROS2 design should include:

- Health topics or diagnostics
- Input and output rates
- Latency measurements
- Stale data counters
- Dropped message counters
- Current mode/state
- Last error reason
- RViz visualization hooks
- Bag replay path

Strong phrase:

> If a field failure cannot be observed, it cannot be debugged responsibly.

## Testing Strategy

Test layers:

- Pure C++ unit tests for algorithms.
- ROS2 node tests for parameter validation and message behavior.
- Launch tests for graph and startup.
- Bag replay for perception/localization regressions.
- Simulation tests for integration.
- Hardware smoke tests for drivers and safety behavior.

For live assignments, say:

> I would test the pure logic without ROS first, then add ROS2 integration tests for interfaces and timing.

## Architecture Review Checklist

Before presenting a ROS2 design, check:

- What are the nodes and why are those the boundaries?
- What package owns each interface?
- Which topics/services/actions exist?
- What are the frame contracts?
- What are the QoS choices?
- What happens on stale data?
- What happens on missing TF?
- What is lifecycle-managed?
- How is it launched in dev, sim, and field?
- How do we inspect it in RViz and logs?
- How do we replay and test it?

## Assignment Answer Template

Use this structure when asked to design a ROS2 system:

```text
I would split the implementation into pure libraries and ROS wrappers.
The ROS wrappers own topics, parameters, lifecycle, diagnostics, and TF.
The pure libraries own filtering/planning/fusion logic and can be unit-tested.

The main data path is:
sensor topics -> validation/TF -> algorithm library -> output topic/action -> diagnostics.

The main failure paths are stale sensor data, missing transforms, invalid parameters,
and compute overrun. I would make each visible through diagnostics and test them with bags.
```

