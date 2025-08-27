// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "CliPlayerObserver.h"
#include "Player.h"
#include <iostream>

void adventure::v5c::CliPlayerObserver::Notify(
    const adventure::v5c::Player& player, std::string_view msg) const
{
}

void adventure::v5c::CliPlayerObserver::NotePossibleActions(
    const adventure::v5c::Player& player,
    const adventure::v5c::ActionVec& actions) const
{
    if (!player.IsInteractive()) {
        std::cout << "Possible actions:\n";
        for (const auto& action : actions) {
            std::cout << "  " << action->Description() << '\n';
        }
    } else if (actions.empty()) {
        std::cout << "There is nothing you can do.\n";
    }
}

void adventure::v5c::CliPlayerObserver::NoteActionPerformed(
    const adventure::v5c::Player& player, const adventure::v5c::Action& action) const
{
    std::cout << "Performed action: " << action.Description() << '\n';
}

void adventure::v5c::CliPlayerObserver::NoteActionImpossible(
    const adventure::v5c::Player& player, const adventure::v5c::Action& action,
    const std::exception& err) const
{
    std::cout << "Cannot perform action: " << action.Description() << '\n';
    std::cout << "  (Error message: " << err.what() << "\n)";
}
