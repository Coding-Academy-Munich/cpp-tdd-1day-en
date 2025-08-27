// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Player.h"
#include "Location.h"
#include "SelectActionStrategy.h"
#include "actions/ErrorAction.h"
#include "actions/InvestigateAction.h"
#include "actions/MoveAction.h"
#include "actions/QuitAction.h"
#include "strategies/SelectRandomAction.h"

#include <iostream>
#include <memory>
#include <stdexcept>

namespace adventure::v6a {

Player::Player(const std::string& name, const Location& location,
    std::unique_ptr<SelectActionStrategy> strategy, unsigned long seed)
    : pawn_ {std::make_unique<Pawn>(name, location)}
    , strategy_ {std::move(strategy)}
    , randomEngine_ {seed} { }

void Player::TakeTurn() {
    auto actions {GetPossibleActions()};
    auto action {SelectAction(actions)};
    if (!action) {
        action = std::make_shared<SkipTurnAction>();
    }
    PerformIfPossible(*action);
}

std::vector<ActionPtr> Player::GetPossibleActions() const {
    std::vector<ActionPtr> result {};
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
    NotePossibleActions(result);
    return result;
}

ActionPtr Player::SelectAction(const ActionVec& actions) const {
    if (actions.empty()) {
        return nullptr;
    }
    return strategy_->SelectAction(*this, actions);
}

void Player::Perform(const Action& action) // NOLINT(*-make-member-function-const)
{
    action.Perform(*this);
    NoteActionPerformed(action);
}

void Player::PerformIfPossible(const Action& action) {
    try {
        Perform(action);
    } catch (const QuitGameException&) {
        NoteGameQuit();
        throw;
    } catch (const std::exception& err) { NoteActionImpossible(action, err); }
}

void Player::RegisterObserver(std::shared_ptr<const PlayerObserver> observer) {
    observers_.insert(std::move(observer));
}

void Player::Notify(std::string_view msg) const {
    for (const auto& observer : observers_) {
        observer->Notify(*this, msg);
    }
}
void Player::NotePossibleActions(const ActionVec& actions) const {
    for (const auto& observer : observers_) {
        observer->NotePossibleActions(*this, actions);
    }
}

void Player::NoteActionPerformed(const Action& action) const {
    for (const auto& observer : observers_) {
        observer->NoteActionPerformed(*this, action);
    }
}

void Player::NoteActionImpossible(
    const Action& action, const std::exception& err) const {
    for (const auto& observer : observers_) {
        observer->NoteActionImpossible(*this, action, err);
    }
}

void Player::NoteGameQuit() const { Notify("Game quit"); }

const Location& GetLocation(const Player& player) {
    return player.GetPawn().GetLocation();
}

const std::string& GetName(const Player& player) { return player.GetPawn().GetName(); }

std::string GetDescription(const Player& player) {
    return GetName(player) + " at " + GetLocation(player).GetName();
}

void MoveToLocation(Player& player, const Location& newLocation) {
    player.GetPawn().MoveToLocation(newLocation);
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "name: " << GetName(player) << ", loc: " << GetLocation(player).GetName();
    return os;
}

} // namespace adventure::v6a
