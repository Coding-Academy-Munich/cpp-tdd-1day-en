// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V4C_LIB_ACTIONS_SKIPTURNACTION_H
#define COMPLETED_ADVENTURE_V4C_LIB_ACTIONS_SKIPTURNACTION_H

#include "Action.h"

namespace adventure::v4c {

class SkipTurnAction : public Action {
public:
    SkipTurnAction() = default;

    [[nodiscard]] std::string Description() const override;
    void Perform(Pawn& instigator) override;
};

} // namespace adventure::v4c

#endif // COMPLETED_ADVENTURE_V4C_LIB_ACTIONS_SKIPTURNACTION_H
