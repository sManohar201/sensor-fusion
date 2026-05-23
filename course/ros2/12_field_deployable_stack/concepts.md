# ROS2 Module 12 - Field Deployable Stack

## Goal

Assemble the full architecture for a field-deployable robot stack: startup, configuration, monitoring, degraded modes, recovery, testing, simulation, and operator workflows.

## Deployment Architecture

A deployable stack defines:

- package boundaries
- launch hierarchy
- robot-specific configs
- environment-specific configs
- lifecycle order
- diagnostics
- logging and bagging policy
- recovery behavior

## Degraded Modes

A field robot should define what it can still do when something fails:

- LiDAR stale
- GPS unavailable
- localization uncertain
- planner failed
- controller inactive

Not every fault requires full shutdown, but every fault needs a safe policy.

## Recovery

Recovery behavior must be bounded and observable. Repeated silent retries hide failures and delay operator action.

## Final Capstone Direction

Build a production-grade robot stack skeleton that can run in development, simulation, and field-style configurations.

