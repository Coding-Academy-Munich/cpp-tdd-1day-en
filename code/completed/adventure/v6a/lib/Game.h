// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LIB_GAME_H
#define COMPLETED_ADVENTURE_V6A_LIB_GAME_H

#include "GameObserver.h"
#include "Player.h"
#include "World.h"
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace adventure::v6a {

std::optional<std::unique_ptr<SelectActionStrategy>>
SelectStrategy(std::string_view strategy);

class Game {
public:
    explicit Game(
        const std::vector<data::LocationData>& locationDataVector,
        std::shared_ptr<GameObserver> observer
    );
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;
    ~Game() = default;

    Player& AddPlayer(
        std::string_view name, std::string_view strategy = "random",
        unsigned long seed = 42L
    );
    Player& AddPlayer(
        std::string_view name, std::string_view strategy, const Location& location,
        unsigned long seed
    );
    Player& AddPlayer(
        std::string_view name, std::unique_ptr<SelectActionStrategy> strategy,
        const Location& location, unsigned long seed
    );
    Player& AddPlayer(std::unique_ptr<Player> player);

    void RegisterObserver(std::shared_ptr<GameObserver> observer);

    void Run();

private:
    void NotifyGameStarted() const;
    void NotifyTurnStarted(const Player& player) const;
    void NotifyException(const std::exception& err) const;
    void NotifyGameOver(GameOverReason reason) const;
    void NotifyResult(const Result& result) const;

    World world_;
    std::vector<std::unique_ptr<Player>> players_;
    std::vector<std::shared_ptr<GameObserver>> observers_;
    std::unique_ptr<Result> gameResult_ {std::make_unique<GameInProgress>()};
};

} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_GAME_H
