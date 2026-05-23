# ROS2 Module 07 - State Estimation Architecture

## Goal

Design localization and state-estimation software as a subsystem with clear interfaces, measurement adapters, reset behavior, diagnostics, and failure modes.

## Architecture Focus

State estimation is not just an EKF implementation. A deployable localization subsystem needs:

- measurement inputs with timestamps and frames
- covariance handling
- prediction/update boundaries
- reset and reinitialization services
- diagnostics for stale or rejected measurements
- clear ownership of output frames

## Measurement Adapters

Adapters convert ROS messages into estimator-specific measurement objects. This keeps the filter core independent from ROS message types and makes it easier to test with deterministic inputs.

## Reset and Reinitialization

Field robots need controlled reset paths:

- reset pose
- reset covariance
- reject reset while moving
- report reset reason
- log and diagnose reset events

## Capstone Direction

Build a localization subsystem shell with ROS-facing adapters, a filter interface, reset service, diagnostics, and a testable non-ROS filter core.

