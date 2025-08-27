# Adventure V5a

## Proposed Changes

- Introduce the `Player` class
- Implement a simple strategy_ for automatic play in the `Player` class

## Implementation notes

- Rather naive approach to integrate the changes
- Leads to an inflexible solution (as we will se in the next version) that is difficult
  to extend
- `Player::GetPossibleActions` needs to know about all possible actions.
    - For example, it needs to know how to generate move actions for the current
      location_
    - This makes it difficult to add new actions