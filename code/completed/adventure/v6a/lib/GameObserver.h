// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LIB_GAMEOBSERVER_H
#define COMPLETED_ADVENTURE_V6A_LIB_GAMEOBSERVER_H

#include "PlayerObserver.h"
#include "Result.h"
#include <string_view>

namespace adventure::v6a {

class Game;

enum class GameOverReason {
    PlayerWon [[maybe_unused]],
    PlayerDied [[maybe_unused]],
    Quit [[maybe_unused]],
    Error [[maybe_unused]],
    TurnLimitReached [[maybe_unused]],
};

class GameObserver : public PlayerObserver {
public:
    virtual void NoteGameStarted(const Game& game) const = 0;
    virtual void NoteGameOver(const Game& game, GameOverReason reason) const = 0;
    virtual void NoteResult(const Game& game, const Result& result) const = 0;
    virtual void NoteException(const Game& game, const std::exception& err) const = 0;
};
} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_GAMEOBSERVER_H
