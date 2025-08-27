// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "CliGameObserver.h"
#include "Player.h"
#include <iostream>

void adventure::v6a::CliGameObserver::Notify(
    const adventure::v6a::Player& player, std::string_view msg
) const { }

void adventure::v6a::CliGameObserver::NotePossibleActions(
    const adventure::v6a::Player& player, const adventure::v6a::ActionVec& actions
) const {
    if (!player.IsInteractive()) {
        std::cout << "Possible actions:\n";
        for (const auto& action : actions) {
            std::cout << "  " << action->Description() << '\n';
        }
    } else if (actions.empty()) {
        std::cout << "There is nothing you can do.\n";
    }
}

void adventure::v6a::CliGameObserver::NoteActionPerformed(
    const adventure::v6a::Player& player, const adventure::v6a::Action& action
) const {
    std::cout << "Performed action: " << action.Description() << '\n';
}

void adventure::v6a::CliGameObserver::NoteActionImpossible(
    const adventure::v6a::Player& player, const adventure::v6a::Action& action,
    const std::exception& err
) const {
    std::cout << "Cannot perform action: " << action.Description() << '\n';
    std::cout << "  (Error message: " << err.what() << "\n)";
}

void adventure::v6a::CliGameObserver::NoteGameStarted(const adventure::v6a::Game& game
) const { }

void adventure::v6a::CliGameObserver::NoteGameOver(
    const adventure::v6a::Game& game, adventure::v6a::GameOverReason reason
) const { }

void adventure::v6a::CliGameObserver::NoteResult(
    const adventure::v6a::Game& game, const adventure::v6a::Result& result
) const { }

void adventure::v6a::CliGameObserver::NoteException(
    const adventure::v6a::Game& game, const std::exception& err
) const { }

void adventure::v6a::CliGameObserver::NoteTurnStarted(
    const adventure::v6a::Player& player
) const { }
