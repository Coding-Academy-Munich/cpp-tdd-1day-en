// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "room.h"

namespace adv
{

std::string Room::name() const
{
    return name_;
}

const std::string& Room::description() const
{
    return description_;
}

} // namespace adv
