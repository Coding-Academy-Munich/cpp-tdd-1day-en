// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5C_LIB_ACTION_H
#define COMPLETED_ADVENTURE_V5C_LIB_ACTION_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace adventure::v5c {

class ActionTagSet;
enum class ActionTag : unsigned int;
class Pawn;
class Player;

class Action {
public:
    Action() = default;
    Action(const Action&) = delete;
    Action(Action&&) = delete;
    Action& operator=(const Action&) = delete;
    Action& operator=(Action&&) = delete;
    virtual ~Action() = default;

    [[nodiscard]] virtual std::string Description() const = 0;
    [[nodiscard]] virtual ActionTagSet Tags() const = 0;
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

} // namespace adventure::v5c

#endif // COMPLETED_ADVENTURE_V5C_LIB_ACTION_H
