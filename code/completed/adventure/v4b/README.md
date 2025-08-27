# Adventure V4b

## Proposed Changes

- Generalize the `Move` and `MoveIfPossible` member functions into `PerformAction` and
  `PerformActionIfPossible` member functions

## Implementation notes

- This leads to a bad API where we have to pass a location_ to every action, no matter
  whether it needs it or not
- Extension is possible by adding a new enumerator and a new case to the `switch`
  statement in the `PerformAction` member function
- This means that we need to change the code for every new action (violation of OCP)