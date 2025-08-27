// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V4C_LIB_ACTION_H
#define COMPLETED_ADVENTURE_V4C_LIB_ACTION_H

#include <string>
#include <unordered_set>

namespace adventure::v4c {

class Pawn;

class Action {
public:
    Action() = default;
    Action(const Action&) = delete;
    Action(Action&&) = delete;
    Action& operator=(const Action&) = delete;
    Action& operator=(Action&&) = delete;
    virtual ~Action() = default;

    [[nodiscard]] virtual std::string Description() const = 0;
    virtual void Perform(Pawn& instigator) = 0;
};
} // namespace adventure::v4c

#endif // COMPLETED_ADVENTURE_V4C_LIB_ACTION_H
