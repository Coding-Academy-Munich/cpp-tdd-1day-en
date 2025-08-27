# Adventure V3c

## Proposed Changes

- Move creation of the `World` and `Location` objects into a factory class

## Implementation notes

- This means we have to exposed setters for the connections of the `Location` class
  which is not ideal
- A possibility to avoid this would be to make the factory a friend of the `Location`
  class