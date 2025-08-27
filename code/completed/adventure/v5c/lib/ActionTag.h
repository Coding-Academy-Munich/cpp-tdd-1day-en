// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_ADVENTURE_V5C_LIB_ACTIONTAG_H
#define COMPLETED_ADVENTURE_V5C_LIB_ACTIONTAG_H

#include <bitset>
#include <string>
#include <unordered_set>

namespace adventure::v5c {
enum class ActionTag : unsigned int {
    Aggressive [[maybe_unused]] = 0,
    Error [[maybe_unused]],
    HandleObject [[maybe_unused]],
    Helpful [[maybe_unused]],
    Investigate [[maybe_unused]],
    Move [[maybe_unused]],
    Quit [[maybe_unused]],
    Rest [[maybe_unused]],
    SkipTurn [[maybe_unused]],
    // To determine the required size of the sets used to store tags.
    TAG_SET_SIZE
};

class ActionTagSet {
public:
    ActionTagSet() = default;
    ActionTagSet(std::initializer_list<ActionTag> tags);

    [[nodiscard]] bool Contains(ActionTag tag) const;

private:
    std::bitset<static_cast<std::size_t>(ActionTag::TAG_SET_SIZE)> TagBits;
};

} // namespace adventure::v5c

#endif // COMPLETED_ADVENTURE_V5C_LIB_ACTIONTAG_H
