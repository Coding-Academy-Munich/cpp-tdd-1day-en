// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Player.h"
#include "Location.h"
#include "actions/ErrorAction.h"
#include "actions/InvestigateAction.h"
#include "actions/MoveAction.h"
#include "actions/QuitAction.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace adventure::v5b
{

Player::Player(
    const std::string& name, const Location& location, PlayerStrategy strategy,
    unsigned long seed
)
    : pawn{std::make_unique<Pawn>(name, location)}, strategy{strategy}, randomEngine{seed}
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
    result.push_back(std::make_shared<InvestigateAction>());
    result.push_back(std::make_shared<SkipTurnAction>());
    if (IsInteractive()) {
        result.push_back(std::make_shared<QuitAction>());
#ifndef NDEBUG
        result.push_back(std::make_shared<ErrorAction>());
#endif
    }
    if (!IsInteractive()) {
        std::cout << "Possible actions:\n";
        for (const auto& action : result) {
            std::cout << "  " << action->Description() << '\n';
        }
    }
    return result;
}

ActionPtr Player::SelectAction(const ActionVec& actions) const
{
    if (actions.empty()) {
        if (IsInteractive()) {
            std::cout << "No actions available.\n";
        }
        return nullptr;
    }
    if (strategy == PlayerStrategy::Interactive) {
        return SelectActionInteractively(actions);
    } else if (strategy == PlayerStrategy::LastAction) {
        return actions.back();
    } else if (strategy == PlayerStrategy::RandomAction) {
        ActionVec resultActions{actions};
        std::sample(
            actions.begin(), actions.end(), std::back_inserter(resultActions), 1,
            randomEngine
        );
        return resultActions.back();
    } else if (strategy == PlayerStrategy::Aggressive) {
        ActionVec resultActions{ActionsWithTag(actions, ActionTag::Aggressive)};
        if (resultActions.empty()) {
            resultActions = ActionsWithoutTag(actions, ActionTag::Helpful);
        }
        return resultActions.empty() ? nullptr : resultActions.back();
    } else if (strategy == PlayerStrategy::Helpful) {
        ActionVec resultActions{ActionsWithTag(actions, ActionTag::Helpful)};
        if (resultActions.empty()) {
            resultActions = ActionsWithoutTag(actions, ActionTag::Aggressive);
        }
        return resultActions.empty() ? nullptr : resultActions.back();
    } else {
        throw std::logic_error{"Unknown player strategy"};
    }
}

void Player::Perform(const Action& action) // NOLINT(*-make-member-function-const)
{
    action.Perform(*this);
    std::cout << "Performed action: " << action.Description() << '\n';
}

void Player::PerformIfPossible(const Action& action)
{
    try {
        Perform(action);
    } catch (const QuitGameException&) {
        throw;
    } catch (const std::exception& err) {
        std::cout << "Cannot perform action: " << action.Description() << '\n';
        std::cout << "  error message: " << err.what() << '\n';
    }
}

const Location& GetLocation(const Player& player) { return player.GetPawn().GetLocation(); }

const std::string& GetName(const Player& player) { return player.GetPawn().GetName(); }

std::string GetDescription(const Player& player)
{
    return GetName(player) + " at " + GetLocation(player).GetName();
}

ActionPtr SelectActionInteractively(const std::vector<ActionPtr>& actions)
{
    int selectedActionIndex{};
    while (true) {
        std::cout << "Available actions:\n";
        for (int i{}; i < actions.size(); ++i) {
            std::cout << "  " << i + 1 << ": " << actions[i]->Description() << '\n';
        }
        std::cin >> selectedActionIndex;
        if (selectedActionIndex >= 1 && selectedActionIndex <= actions.size()) {
            return actions.at(selectedActionIndex - 1);
        } else {
            std::cout << "Please select a valid action index.\n";
        }
    }
}

void MoveToLocation(Player& player, const Location& newLocation)
{
    player.GetPawn().MoveToLocation(newLocation);
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << "name: " << GetName(player) << ", loc: " << GetLocation(player).GetName();
    return os;
}
} // namespace adventure::v5b
