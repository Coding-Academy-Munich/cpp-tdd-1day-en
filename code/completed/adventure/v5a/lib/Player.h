// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5A_LIB_PLAYER_H
#define COMPLETED_ADVENTURE_V5A_LIB_PLAYER_H

#include "Pawn.h"
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace adventure::v5a
{

class Player
{
public:
    explicit Player(const std::string& name, const Location& location);

    void TakeTurn();

    [[nodiscard]] std::vector<ActionPtr> GetPossibleActions() const;
    [[nodiscard]] static ActionPtr SelectAction(const std::vector<ActionPtr>& actions);
    void Perform(const Action& action);
    void PerformIfPossible(const Action& action);

    [[nodiscard]] const Pawn& GetPawn() const { return *pawn; }
    [[nodiscard]] Pawn& GetPawn() { return *pawn; }

private:
    std::unique_ptr<Pawn> pawn;
};

[[nodiscard]] const std::string& GetName(const Player& player);
[[nodiscard]] const Location& GetLocation(const Player& player);
[[nodiscard]] std::string GetDescription(const Player& player);

inline void MoveToLocation(Player& player, const Location& newLocation)
{
    player.GetPawn().MoveToLocation(newLocation);
}

std::ostream& operator<<(std::ostream& os, const Player& player);

} // namespace adventure::v5a

#endif // COMPLETED_ADVENTURE_V5A_LIB_PLAYER_H
