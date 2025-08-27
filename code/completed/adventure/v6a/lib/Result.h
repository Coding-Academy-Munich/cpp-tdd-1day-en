// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LIB_RESULT_H
#define COMPLETED_ADVENTURE_V6A_LIB_RESULT_H

namespace adventure::v6a {

class Result {
public:
    Result() = default;
    Result(const Result&) = delete;
    Result(Result&&) = delete;
    Result& operator=(const Result&) = delete;
    Result& operator=(Result&&) = delete;
    virtual ~Result() = default;

    [[nodiscard]] virtual bool IsGameInProgress() const { return false; }
    [[nodiscard]] virtual bool HasPlayerWon() const { return false; }
    [[nodiscard]] virtual bool HasPlayerDied() const { return false; }
};

class GameInProgress : public Result {
public:
    GameInProgress() = default;
    [[nodiscard]] bool IsGameInProgress() const override { return true; }
};

class PlayerWon : public Result {
public:
    PlayerWon() = default;
    [[nodiscard]] bool HasPlayerWon() const override { return true; }
};

class PlayerDied : public Result {
public:
    PlayerDied() = default;
    [[nodiscard]] bool HasPlayerDied() const override { return true; }
};

} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_RESULT_H
