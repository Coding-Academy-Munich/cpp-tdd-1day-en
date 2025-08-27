// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LIB_PLAYEROBSERVER_H
#define COMPLETED_ADVENTURE_V6A_LIB_PLAYEROBSERVER_H

#include "Action.h"
#include <functional>
#include <string_view>

namespace adventure::v6a {

class Player;

class PlayerObserver {
public:
    PlayerObserver() = default;
    PlayerObserver(const PlayerObserver&) = delete;
    PlayerObserver(PlayerObserver&&) = delete;
    PlayerObserver& operator=(const PlayerObserver&) = delete;
    PlayerObserver& operator=(PlayerObserver&&) = delete;
    virtual ~PlayerObserver() = default;

    virtual void Notify(const Player& player, std::string_view msg) const = 0;
    virtual void NoteTurnStarted(const Player& player) const = 0;
    virtual void NotePossibleActions(
        const Player& player, const ActionVec& actions) const
        = 0;
    virtual void NoteActionPerformed(const Player& player, const Action& action) const
        = 0;
    virtual void NoteActionImpossible(
        const Player& player, const Action& action, const std::exception& err) const
        = 0;
};

bool operator==(const PlayerObserver& lhs, const PlayerObserver& rhs) noexcept;

bool operator!=(const PlayerObserver& lhs, const PlayerObserver& rhs) noexcept;

} // namespace adventure::v6a

template <>
struct std::hash<adventure::v6a::PlayerObserver> {
    std::size_t operator()(
        const adventure::v6a::PlayerObserver& observer) const noexcept {
        return std::hash<const adventure::v6a::PlayerObserver*> {}(&observer);
    }
};

#endif // COMPLETED_ADVENTURE_V6A_LIB_PLAYEROBSERVER_H
