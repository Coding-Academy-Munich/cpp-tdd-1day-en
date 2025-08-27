// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LIB_PLAYER_H
#define COMPLETED_ADVENTURE_V6A_LIB_PLAYER_H

#include "Pawn.h"
#include "PlayerObserver.h"
#include "SelectActionStrategy.h"
#include "strategies/SelectRandomAction.h"
#include <memory>
#include <ostream>
#include <random>
#include <set>
#include <string>
#include <vector>

namespace adventure::v6a {

enum class PlayerStrategyEnum {
    Interactive [[maybe_unused]],
    LastAction [[maybe_unused]],
    RandomAction [[maybe_unused]],
    Aggressive [[maybe_unused]],
    Helpful [[maybe_unused]],
};

class Player {
public:
    using RandomEngineType = std::default_random_engine;

    explicit Player(const std::string& name, const Location& location,
        std::unique_ptr<SelectActionStrategy> strategy
        = std::make_unique<SelectRandomAction>(),
        unsigned long seed = 42L);

    void TakeTurn();

    [[nodiscard]] std::vector<ActionPtr> GetPossibleActions() const;
    [[nodiscard]] ActionPtr SelectAction(const ActionVec& actions) const;
    void Perform(const Action& action);
    void PerformIfPossible(const Action& action);

    [[nodiscard]] const Pawn& GetPawn() const { return *pawn_; }
    [[nodiscard]] Pawn& GetPawn() { return *pawn_; }
    [[nodiscard]] RandomEngineType& GetRandomEngine() const { return randomEngine_; }

    [[nodiscard]] bool IsInteractive() const { return strategy_->IsInteractive(); }

    void RegisterObserver(std::shared_ptr<const PlayerObserver> observer);

private:
    virtual void Notify(std::string_view msg) const;
    virtual void NotePossibleActions(const ActionVec& actions) const;
    virtual void NoteActionPerformed(const Action& action) const;
    virtual void NoteActionImpossible(
        const Action& action, const std::exception& err) const;
    void NoteGameQuit() const;

    std::unique_ptr<Pawn> pawn_;
    std::unique_ptr<SelectActionStrategy> strategy_;
    std::unordered_set<std::shared_ptr<const PlayerObserver>> observers_ {};
    mutable std::default_random_engine randomEngine_;
};

[[nodiscard]] const std::string& GetName(const Player& player);
[[nodiscard]] const Location& GetLocation(const Player& player);
[[nodiscard]] std::string GetDescription(const Player& player);

void MoveToLocation(Player& player, const Location& newLocation);

std::ostream& operator<<(std::ostream& os, const Player& player);

std::unique_ptr<SelectActionStrategy> StrategyClassFor(
    PlayerStrategyEnum playerStrategyEnum);

} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_PLAYER_H
