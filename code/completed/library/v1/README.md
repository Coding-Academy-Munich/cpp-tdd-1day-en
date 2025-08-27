# Library V1

## Proposed Changes

- Initial implementation of the `Book` and `Member` and `MemberType`  classes

## Implementation notes

- `Book` represents the physical book in the library
- To store its data (e.g., authors, title, etc.) it uses a `BookInfo` class
- `BookInfo` objects are shared~~~~ between books, therefore we handle them as shared
  pointers
- To ensure that `BookInfo` objects are always created as shared pointers, we use a
  factory method to create the `BookInfo` objects and make the constructor private
- This makes using `make_shared()` a bit tricky, since it's not really possible to
  declare it as a friend because of its complicated specification
- We derive a local subclass `MakeSharedEnabler` class from `BookInfo` with public
  constructor to allow `make_shared()` to indirectly create `BookInfo` objects
- `Member` represents a library member
- `MemberType` represents the type of member (e.g., regular, student, senior, etc.)
- We use inheritance to differentiate between the different types of members
- This satisfies the Open-Closed principle