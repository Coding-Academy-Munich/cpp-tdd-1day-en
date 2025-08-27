# Library V2a

## Proposed Changes

- Add `Library` class
- Implement registration of new members
- Implement addition of books to the library
- Implement finding books and members by various criteria

## Implementation notes

- Assign responsibilities for adding members and books to the Library class
- Introducing a `Librarian` class would probably not improve the design
  - Actually it would probably make it worse (e.g., having the `Librarian` class
      create or manipulate `Book` objects would go against Creator and Information
      Expert principles)
- To allow the creation of books from a shared pointer to `BookInfo`, we derive
  `BookInfo` from `enable_shared_from_this<BookInfo>` so that we can create the
  required shared pointer from a reference
