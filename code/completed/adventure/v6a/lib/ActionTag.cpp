// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "ActionTag.h"

namespace adventure::v6a {

ActionTagSet::ActionTagSet(std::initializer_list<ActionTag> tags) {
    for (auto tag : tags) {
        this->tagBits_.set(static_cast<std::size_t>(tag), true);
    }
}

bool ActionTagSet::Contains(ActionTag tag) const {
    return tagBits_.test(static_cast<std::size_t>(tag));
}

} // namespace adventure::v6a
