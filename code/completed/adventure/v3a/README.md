# Adventure V3a

## Proposed Changes

- Add connections between locations_

## Implementation notes

- We're doing this the wrong way and managing the connections in the `World` class
- This leads to too high coupling in the system, since you need the `World` class to
  move from `Location` to `Location`