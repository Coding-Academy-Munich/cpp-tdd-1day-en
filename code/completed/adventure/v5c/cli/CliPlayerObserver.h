// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5C_CLI_CLIPLAYEROBSERVER_H
#define COMPLETED_ADVENTURE_V5C_CLI_CLIPLAYEROBSERVER_H

#include "PlayerObserver.h"

namespace adventure::v5c {

class CliPlayerObserver : public PlayerObserver {
public:
    void Notify(const Player& player, std::string_view msg) const override;
    void NotePossibleActions(
        const Player& player, const ActionVec& actions) const override;
    void NoteActionPerformed(const Player& player, const Action& action) const override;
    void NoteActionImpossible(const Player& player, const Action& action,
        const std::exception& err) const override;
};

} // namespace adventure::v5c
#endif // COMPLETED_ADVENTURE_V5C_CLI_CLIPLAYEROBSERVER_H
