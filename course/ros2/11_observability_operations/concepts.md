# ROS2 Module 11 - Observability & Operations

## Goal

Design robot software so field operators and engineers can understand what the robot is doing and why it failed.

## Observability Signals

Field systems need:

- diagnostics
- logs
- bags
- metrics
- health summaries
- fault reports

## Diagnostic Levels

Use clear health levels:

- OK
- WARN/DEGRADED
- ERROR/FAILED

Health output should be machine-readable and operator-readable.

## Operational Workflows

Every fault should have a path:

- detect
- report
- degrade or stop safely
- recover if possible
- preserve evidence

## Capstone Direction

Build an operator-facing health system that aggregates subsystem status and produces actionable summaries.

