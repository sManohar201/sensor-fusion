# ROS2 Module 05 - Executors & Concurrency

## Goal

Understand how ROS2 callbacks execute and how executor choices affect latency, throughput, and safety.

## Executors

Executors run callbacks. A single-threaded executor runs one callback at a time. A multi-threaded executor can run multiple callbacks concurrently.

Concurrency is not automatically better. It introduces shared-state hazards.

## Callback Groups

Callback groups define which callbacks may run concurrently.

Types:

- mutually exclusive
- reentrant

Use mutually exclusive groups when callbacks share state and should not overlap. Use reentrant groups only when the code is safe to run concurrently.

## Timers

Timers are useful for periodic health checks, stale-topic detection, control loops, and status publishing. Timer callbacks must have bounded runtime.

## Shared State

Protect shared state with mutexes or design callbacks to avoid sharing mutable state. Do not assume a callback cannot overlap unless the executor and callback group guarantee it.

## Capstone Direction

Build a concurrent sensor pipeline with subscriber callbacks storing latest samples, a timer callback processing snapshots, documented callback group choices, and bounded lock scope.

