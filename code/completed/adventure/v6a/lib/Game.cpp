// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Game.h"
#include "WorldFactory.h"
#include "actions/QuitAction.h"
#include "strategies/SelectActionInteractively.h"
#include "strategies/SelectAggressiveAction.h"
#include "strategies/SelectHelpfulAction.h"
#include "strategies/SelectLastAction.h"
#include <iostream>

namespace adventure::v6a {

std::optional<std::unique_ptr<SelectActionStrategy>>
SelectStrategy(std::string_view strategy) {
    if (strategy == "interactive") {
        return {std::make_unique<SelectActionInteractively>()};
    } else if (strategy == "last" || strategy == "last-action") {
        return {std::make_unique<SelectLastAction>()};
    } else if (strategy == "random" || strategy == "random-action") {
        return {std::make_unique<SelectRandomAction>()};
    } else if (strategy == "aggressive" || strategy == "aggressive-action") {
        return {std::make_unique<SelectAggressiveAction>()};
    } else if (strategy == "helpful" || strategy == "helpful-action") {
        return {std::make_unique<SelectHelpfulAction>()};
    } else {
        return {};
    }
}

Game::Game(
    const std::vector<data::LocationData>& locationDataVector,
    std::shared_ptr<GameObserver> observer
)
    : world_ {WorldFactory::create(locationDataVector)} {
    RegisterObserver(observer);
}

Player&
Game::AddPlayer(std::string_view name, std::string_view strategy, unsigned long seed) {
    return AddPlayer(name, strategy, world_.GetInitialLocation(), seed);
}

Player& Game::AddPlayer(
    std::string_view name, std::string_view strategy, const Location& location,
    unsigned long seed
) {
    if (auto selectedStrategy {SelectStrategy(strategy)}) {
        return AddPlayer(name, std::move(*selectedStrategy), location, seed);
    }
    throw std::invalid_argument {"Unknown strategy: " + std::string {strategy}};
}

Player& Game::AddPlayer(
    std::string_view name, std::unique_ptr<SelectActionStrategy> strategy,
    const Location& location, unsigned long seed
) {
    return AddPlayer(std::make_unique<Player>(
        std::string {name}, location, std::move(strategy), seed
    ));
}

Player& Game::AddPlayer(std::unique_ptr<Player> player) {
    for (const auto& observer : observers_) {
        player->RegisterObserver(observer);
    }
    players_.push_back(std::move(player));
    return *players_.back();
}

void Game::Run() {
    try {
        NotifyGameStarted();
        for (const auto& player : players_) {
            for (int i {}; i < 10; ++i) {
                NotifyTurnStarted(*player);
                player->TakeTurn();
            }
        }
        NotifyGameOver(GameOverReason::TurnLimitReached);
        NotifyResult(*gameResult_);
    } catch (const QuitGameException&) {
        NotifyGameOver(GameOverReason::Quit);
    } catch (const std::exception& e) {
        NotifyException(e);
        NotifyGameOver(GameOverReason::Error);
    }
}

void Game::RegisterObserver(std::shared_ptr<GameObserver> observer) {
    for (const auto& player : players_) {
        player->RegisterObserver(observer);
    }
    observers_.push_back(std::move(observer));
}

void Game::NotifyGameStarted() const {
    for (const auto& observer : observers_) {
        observer->NoteGameStarted(*this);
    }
}

void Game::NotifyTurnStarted(const Player& player) const {
    for (const auto& observer : observers_) {
        observer->NoteTurnStarted(player);
    }
}

void Game::NotifyGameOver(GameOverReason reason) const {
    for (const auto& observer : observers_) {
        observer->NoteGameOver(*this, reason);
    }
}
void Game::NotifyResult(const Result& result) const {
    for (const auto& observer : observers_) {
        observer->NoteResult(*this, result);
    }
}

void Game::NotifyException(const std::exception& err) const {
    for (const auto& observer : observers_) {
        observer->NoteException(*this, err);
    }
}

} // namespace adventure::v6a