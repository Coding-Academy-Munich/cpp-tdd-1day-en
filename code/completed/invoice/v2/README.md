# Invoice Generator

## Refactorings in this version

- Reverted back to V0
- Refactoring to prepare for the `ProcessSingleLine()` function
  - Introduce `DepartmentStatistics` struct
  - Destructure `lineItem` in the for loop body
- Simplify the finding of `itemPrice` and `department`
