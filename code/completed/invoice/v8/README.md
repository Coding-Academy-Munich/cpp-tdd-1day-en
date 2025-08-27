# Invoice Generator

## Refactorings in this version

- Add `customerName` member to `OrderTracker`
- Add `products` member to `OrderTracker`
- Add member functions to `Product`
  - `Discount(int quantity)`
  - `DiscountedPrice(int quantity)`
  - `TotalPrice(int quantity)`
- Add `RegisterSale()` method to `OrderTracker`
