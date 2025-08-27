// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "ActionTag.h"

namespace adventure::v5c {

ActionTagSet::ActionTagSet(std::initializer_list<ActionTag> tags)
{
    for (auto tag : tags) {
        this->TagBits.set(static_cast<std::size_t>(tag), true);
    }
}

bool ActionTagSet::Contains(ActionTag tag) const
{
    return TagBits.test(static_cast<std::size_t>(tag));
}

} // namespace adventure::v5c
