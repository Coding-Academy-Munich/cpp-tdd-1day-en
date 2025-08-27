// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5B_LIB_PLAYER_H
#define COMPLETED_ADVENTURE_V5B_LIB_PLAYER_H

#include "Pawn.h"
#include <memory>
#include <ostream>
#include <random>
#include <string>
#include <vector>

namespace adventure::v5b
{

enum class PlayerStrategy {
    Interactive,
    LastAction,
    RandomAction,
    Aggressive,
    Helpful,
};

class Player
{
public:
    explicit Player(
        const std::string& name, const Location& location,
        PlayerStrategy strategy = PlayerStrategy::RandomAction, unsigned long seed = 42L
    );

    void TakeTurn();

    [[nodiscard]] std::vector<ActionPtr> GetPossibleActions() const;
    [[nodiscard]] ActionPtr SelectAction(const ActionVec& actions) const;
    void Perform(const Action& action);
    void PerformIfPossible(const Action& action);

    [[nodiscard]] const Pawn& GetPawn() const { return *pawn; }
    [[nodiscard]] Pawn& GetPawn() { return *pawn; }

    [[nodiscard]] bool IsInteractive() const
    {
        return strategy == PlayerStrategy::Interactive;
    }

private:
    std::unique_ptr<Pawn> pawn;
    PlayerStrategy strategy{};
    mutable std::default_random_engine randomEngine;
};

[[nodiscard]] const std::string& GetName(const Player& player);
[[nodiscard]] const Location& GetLocation(const Player& player);
[[nodiscard]] std::string GetDescription(const Player& player);

ActionPtr SelectActionInteractively(const std::vector<ActionPtr>& actions);
void MoveToLocation(Player& player, const Location& newLocation);

std::ostream& operator<<(std::ostream& os, const Player& player);

} // namespace adventure::v5b

#endif // COMPLETED_ADVENTURE_V5B_LIB_PLAYER_H
