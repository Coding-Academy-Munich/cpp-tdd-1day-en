// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "ErrorAction.h"
#include "ActionTag.h"
#include <stdexcept>

namespace adventure::v5c {

std::string ErrorAction::Description() const
{
    return "Raise an error for testing purposes.";
}

ActionTagSet ErrorAction::Tags() const { return {ActionTag::Error}; }

void ErrorAction::Perform(Player& instigator) const
{
    throw std::runtime_error("This is an error for testing purposes.");
}

bool ErrorAction::Equals(const Action& other) const
{
    return dynamic_cast<const ErrorAction*>(&other) != nullptr;
}

} // namespace adventure::v5c