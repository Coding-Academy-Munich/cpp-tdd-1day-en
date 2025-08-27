# Adventure V4a

## Proposed Changes

- Add a `Pawn` class with `Move` and `MoveIfPossible` member functions

## Implementation notes

- This is a rather straightforward change, given our domain model
- The `Move` and `MoveIfPossible` member functions will become problematic once we
  try to add more actions since we need a mapping from action to member function
  to execute