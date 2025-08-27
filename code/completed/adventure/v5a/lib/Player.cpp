// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Player.h"
#include "Location.h"
#include "actions/MoveAction.h"

#include <memory>
#include <stdexcept>

namespace adventure::v5a
{

Player::Player(const std::string& name, const Location& location)
    : pawn{std::make_unique<Pawn>(name, location)}
{
}

void Player::TakeTurn()
{
    auto actions{GetPossibleActions()};
    auto action{SelectAction(actions)};
    if (!action) {
        action = std::make_shared<SkipTurnAction>();
    }
    PerformIfPossible(*action);
}

std::vector<ActionPtr> Player::GetPossibleActions() const
{
    std::vector<ActionPtr> result{};
    for (const auto& exit : GetLocation(*this).GetConnectedDirections()) {
        result.push_back(std::make_shared<MoveAction>(exit));
    }
    return result;
}

ActionPtr Player::SelectAction(const std::vector<ActionPtr>& actions)
{
    if (actions.empty()) {
        return nullptr;
    }
    return actions.back();
}

void Player::Perform(const Action& action) // NOLINT(*-make-member-function-const)
{
    action.Perform(*this);
}

void Player::PerformIfPossible(const Action& action)
{
    try {
        Perform(action);
    } catch (const std::out_of_range&) {
        // Ignore the exception.
    }
}

const Location& GetLocation(const Player& player) { return player.GetPawn().GetLocation(); }

const std::string& GetName(const Player& player) { return player.GetPawn().GetName(); }

std::string GetDescription(const Player& player)
{
    return GetName(player) + " at " + GetLocation(player).GetName();
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << "name: " << GetName(player) << ", loc: " << GetLocation(player).GetName();
    return os;
}
} // namespace adventure::v5a