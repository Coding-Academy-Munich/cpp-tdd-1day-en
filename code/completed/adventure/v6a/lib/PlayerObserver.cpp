// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "PlayerObserver.h"

namespace adventure::v6a {

bool operator==(const PlayerObserver& lhs, const PlayerObserver& rhs) noexcept
{
    return &lhs == &rhs;
}

bool operator!=(const PlayerObserver& lhs, const PlayerObserver& rhs) noexcept
{
    return !(lhs == rhs);
}
} // namespace adventure::v6a