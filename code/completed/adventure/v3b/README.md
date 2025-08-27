# Adventure V3b

## Proposed Changes

- Fix the management of connections by moving the responsibility to the `Location`
  class.

## Implementation notes

- We could improve this code by splitting the construction in the `World` class into
  two parts: `CreateLocations()`, `BuildLocationConnections()`
