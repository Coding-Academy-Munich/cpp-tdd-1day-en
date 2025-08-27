# Invoice Generator

## Refactorings in this version

- Rename `OrderTracker::PrintVolumeDiscountAndTotal()` to
  `OrderTracker::PrintDiscountAndTotal()`
- Inline `OrderTrackeer::PrintDiscount()` member function
- Remove unused `invoice::v8::ComputeDiscount()` function
- Rename `Item` to `ItemDescription`
- Add `LineItem` class
- Store `LineItem` objects in `OrderTracker`
