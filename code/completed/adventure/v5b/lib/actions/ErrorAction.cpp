// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "ErrorAction.h"
#include <stdexcept>

namespace adventure::v5b {

std::string ErrorAction::Description() const
{
    return "Raise an error for testing purposes.";
}

const std::unordered_set<ActionTag>& ErrorAction::Tags() const
{
    static const std::unordered_set<ActionTag> tags {ActionTag::Error};
    return tags;
}

void ErrorAction::Perform(Player& instigator) const
{
    throw std::runtime_error("This is an error for testing purposes.");
}

bool ErrorAction::Equals(const Action& other) const
{
    return dynamic_cast<const ErrorAction*>(&other) != nullptr;
}

} // namespace adventure::v5b