# C++ Robotics Interview Deep Dive

For this opportunity, learn C++ as the language of reliable robot behavior, not only as syntax. In a live assignment, the interviewer will look for ownership, timing, failure handling, interfaces, and performance decisions.

## Core Positioning

Say this clearly:

> I use C++ in robotics when I need predictable ownership, bounded latency, explicit interfaces, and efficient data processing close to sensors and actuators.

Then prove it with examples from point clouds, filters, controllers, and hardware interfaces.

## Must-Know C++ Areas

| Area | Robotics Meaning | Interview Example |
|---|---|---|
| RAII | Resources are released deterministically | Serial port, socket, file, GPU buffer, driver handle |
| Const correctness | Communicates mutation boundaries | A planner should not mutate the map while scoring paths |
| References and pointers | Express ownership and optionality | Reference for required dependency, pointer for nullable or polymorphic object |
| Smart pointers | Make ownership explicit | `unique_ptr` for plugins, `shared_ptr` for ROS2 messages and node handles |
| Move semantics | Avoid expensive copies | Point clouds, images, trajectories, large buffers |
| Templates | Type-safe reusable algorithms | Generic ring buffer, typed units, filter interface |
| STL algorithms | Clear data transformations | Filter stale tracks, transform detections, accumulate costs |
| Chrono | Correct time semantics | Sensor freshness, latency, timeouts |
| Threads and mutexes | Concurrent callbacks safely | Sensor ingestion thread and processing thread |
| Atomics | Small lock-free state flags | Shutdown flag, latest health state |
| CMake | Reproducible builds | Library boundaries, tests, dependencies |
| Sanitizers | Catch undefined behavior | Address, undefined behavior, thread race detection |

## Ownership Rules

Use this language:

- `std::unique_ptr<T>`: this object has one owner.
- `std::shared_ptr<T>`: ownership is shared and lifetime must outlive callbacks or async work.
- `std::weak_ptr<T>`: observe without extending lifetime.
- Raw pointer: non-owning and nullable, only when the lifetime is managed elsewhere.
- Reference: non-owning and required.

Robotics example:

```cpp
class PointCloudProjector {
public:
  explicit PointCloudProjector(ProjectorConfig config);

  ProjectionResult project(const sensor_msgs::msg::PointCloud2& cloud) const;

private:
  ProjectorConfig config_;
};
```

This says:

- Config is owned by the projector.
- The input cloud is required and not modified.
- The function returns a value with no hidden lifetime dependency.

## Interface Design

Good robotics C++ interfaces make contracts visible:

- What frame is expected?
- What timestamp is expected?
- Who owns the data?
- Can the function fail?
- Is the function realtime-sensitive?
- Does it allocate?
- Is it thread-safe?

Prefer domain-specific types over loose primitives:

```cpp
struct TimedPose {
  rclcpp::Time stamp;
  std::string frame_id;
  Eigen::Isometry3d pose;
  Eigen::Matrix<double, 6, 6> covariance;
};
```

This is stronger than passing `x`, `y`, `yaw`, and a `double timestamp` separately.

## Error Handling

In robotics, errors are often operational states, not exceptions.

Use:

- `std::optional<T>` when absence is expected.
- `std::variant` when there are several valid outcomes.
- Status enums when caller must branch.
- Exceptions mainly for construction/configuration errors outside hot loops.

Example:

```cpp
enum class ProjectionStatus {
  kOk,
  kStaleInput,
  kMissingTransform,
  kTooFewPoints,
};

struct ProjectionResult {
  ProjectionStatus status;
  std::vector<GridCell> occupied_cells;
  std::chrono::microseconds latency;
};
```

This is interview-friendly because it shows observability and failure handling.

## Real-Time and Performance Thinking

When C++ performance matters, discuss:

- Avoiding copies of point clouds and images
- Preallocating buffers in hot paths
- Cropping and downsampling before expensive work
- Using contiguous storage for cache locality
- Keeping locks short
- Avoiding blocking work in ROS2 callbacks
- Measuring before optimizing

Strong phrase:

> I care about predictable latency more than average speed. A robot that is usually fast but occasionally stalls is hard to trust.

## Concurrency

Robotics concurrency hazards:

- Sensor callbacks update shared state while planner reads it.
- Timer callback and subscription callback race.
- Service updates parameters while processing is running.
- Long point-cloud processing blocks executor progress.

Safe patterns:

- Copy small immutable snapshots.
- Use mutexes around shared state, but keep lock scope tiny.
- Use callback groups in ROS2.
- Use a worker thread or queue for heavy processing.
- Prefer message passing over shared mutable state when possible.

Example design:

```text
PointCloud callback:
  validate timestamp
  move/copy message handle into bounded queue
  return quickly

Worker thread:
  pop latest cloud
  transform/filter/project
  publish result and diagnostics
```

## C++ Questions You Should Answer Well

Why RAII?

> RAII ties resource lifetime to object lifetime, so resources are released even on early returns or exceptions. That matters for drivers, sockets, files, locks, and hardware handles.

Why `unique_ptr`?

> It expresses exclusive ownership. In robotics plugins or hardware interfaces, that makes teardown and lifecycle behavior easier to reason about.

Why avoid copying point clouds?

> Point clouds are large. Copies add latency, memory bandwidth pressure, and jitter. I crop/downsample early and pass by const reference or move where ownership transfer is intended.

How do you debug memory bugs?

> I use sanitizers first, then focused tests and minimal reproduction. For robotics, I also test shutdown paths and lifecycle transitions because many bugs happen during startup, reconfiguration, and teardown.

What is good C++ architecture?

> Small classes with explicit ownership, clear data contracts, deterministic failure modes, testable pure logic separated from ROS2 transport, and measured hot paths.

