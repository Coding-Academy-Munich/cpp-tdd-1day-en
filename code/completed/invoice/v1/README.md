# Invoice Generator

## Refactorings in this version

- Trying to extract the body of the `for`-loop as a function
    - Use Extract Method refactoring
    - Use Change Signature refactoring to reorder parameters
- This does not work out so well, so we will revert back to the previous version when
  we start the next refactoring step 