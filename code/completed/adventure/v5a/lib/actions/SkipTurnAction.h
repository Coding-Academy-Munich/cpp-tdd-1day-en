// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5A_LIB_ACTIONS_SKIPTURNACTION_H
#define COMPLETED_ADVENTURE_V5A_LIB_ACTIONS_SKIPTURNACTION_H

#include "Action.h"

namespace adventure::v5a {

class SkipTurnAction : public Action {
public:
    SkipTurnAction() = default;

    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] const std::unordered_set<ActionKind>& Tags() const override;
    void Perform(Player& instigator) const override;
};

} // namespace adventure::v5a

#endif // COMPLETED_ADVENTURE_V5A_LIB_ACTIONS_SKIPTURNACTION_H
