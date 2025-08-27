// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5A_LIB_ACTION_H
#define COMPLETED_ADVENTURE_V5A_LIB_ACTION_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace adventure::v5a {

class Player;
class Pawn;

enum class ActionKind {
    Aggressive [[maybe_unused]],
    HandleObject [[maybe_unused]],
    Helpful [[maybe_unused]],
    Investigate [[maybe_unused]],
    Move [[maybe_unused]],
    Quit [[maybe_unused]],
    Rest [[maybe_unused]],
    SkipTurn [[maybe_unused]],
};

class Action {
public:
    Action() = default;
    Action(const Action&) = delete;
    Action(Action&&) = delete;
    Action& operator=(const Action&) = delete;
    Action& operator=(Action&&) = delete;
    virtual ~Action() = default;

    [[nodiscard]] virtual std::string Description() const = 0;
    [[nodiscard]] virtual const std::unordered_set<ActionKind>& Tags() const = 0;
    virtual void Perform(Player& instigator) const = 0;
};

using ActionPtr = std::shared_ptr<const Action>;
using ActionVec = std::vector<ActionPtr>;

std::ostream& operator<<(std::ostream& os, const Action& action);
std::ostream& operator<<(std::ostream& os, const ActionVec& action);

} // namespace adventure::v5a

#endif // COMPLETED_ADVENTURE_V5A_LIB_ACTION_H
