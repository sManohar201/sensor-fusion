# ROS2 Module 09 - Testing & CI

## Goal

Test ROS2 systems at multiple layers: pure C++ logic, nodes, launch files, bags, and simulation integration.

## Test Layers

Use the cheapest test that catches the bug:

- unit tests for pure logic
- node tests for ROS wrappers
- launch tests for process wiring
- bag replay tests for recorded behavior
- simulation tests for integrated behavior

## Bag Replay

Bags are regression fixtures. They let you replay real or simulated data and verify behavior after code changes.

## CI Discipline

CI should build, test, lint, and run representative launch checks. Keep long simulation tests separate from fast presubmit tests.

## Capstone Direction

Build a regression suite for `robot_monitor` using unit tests, synthetic publishers, and bag replay.

