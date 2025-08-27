// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5B_LIB_ACTION_H
#define COMPLETED_ADVENTURE_V5B_LIB_ACTION_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace adventure::v5b {

class Player;
class Pawn;

enum class ActionTag {
    Aggressive [[maybe_unused]],
    Error [[maybe_unused]],
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
    [[nodiscard]] virtual const std::unordered_set<ActionTag>& Tags() const = 0;
    virtual void Perform(Player& instigator) const = 0;

protected:
    friend bool operator==(const Action& lhs, const Action& rhs);
    [[nodiscard]] virtual bool Equals(const Action& other) const = 0;
};

bool operator==(const Action& lhs, const Action& rhs);
bool operator!=(const Action& lhs, const Action& rhs);

std::ostream& operator<<(std::ostream& os, const Action& action);

using ActionPtr = std::shared_ptr<const Action>;
using ActionVec = std::vector<ActionPtr>;

std::ostream& operator<<(std::ostream& os, const ActionVec& action);

ActionVec ActionsWithTag(const ActionVec& actions, ActionTag tag);
ActionVec ActionsWithoutTag(const ActionVec& actions, ActionTag tag);

} // namespace adventure::v5b

#endif // COMPLETED_ADVENTURE_V5B_LIB_ACTION_H
