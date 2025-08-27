// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_CLI_CLIGAMEOBSERVER_H
#define COMPLETED_ADVENTURE_V6A_CLI_CLIGAMEOBSERVER_H

#include "GameObserver.h"

namespace adventure::v6a {

class CliGameObserver : public GameObserver {
public:
    void Notify(const Player& player, std::string_view msg) const override;
    void
    NotePossibleActions(const Player& player, const ActionVec& actions) const override;
    void NoteActionPerformed(const Player& player, const Action& action) const override;
    void NoteActionImpossible(
        const Player& player, const Action& action, const std::exception& err
    ) const override;
    void NoteGameStarted(const Game& game) const override;
    void NoteGameOver(const Game& game, GameOverReason reason) const override;
    void NoteResult(const Game& game, const Result& result) const override;
    void NoteException(const Game& game, const std::exception& err) const override;
    void NoteTurnStarted(const Player& player) const override;
};

} // namespace adventure::v6a
#endif // COMPLETED_ADVENTURE_V6A_CLI_CLIGAMEOBSERVER_H
