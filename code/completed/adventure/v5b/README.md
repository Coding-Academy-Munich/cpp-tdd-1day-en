# Adventure V5b

## Proposed Changes

- Allow the player to play interactively
- Allow NPCs with multiple strategies
- Add more actions (investigate, quit, etc.)

## Implementation notes

- Very naive approach to integrate the changes
- Leads to quite messy code
- `Player::GetPossibleActions` adds an error action for interactive players_
- `Player::SelectAction` is no longer static, since it accesses the state of the
  `Player` object
- `Player::SelectAction` hard-codes the interaction with the user.
    - This bakes the user-interface code into the game logic
- `Player::SelectAction` is tied very closely to the possible actions
    - It is not possible to add new actions without changing the code
    - It is possible to add new actions without changing the code, but the
      actions are not available to the player
- `Player::Perform` and `Player::PerformIfPossible` print output if the player is
  interactive
- `ActionsWithTag` and `ActionsWithoutTag` helper functions to get all actions
  with/without a given tag