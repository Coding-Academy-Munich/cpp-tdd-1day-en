// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5C_LIB_STRATEGIES_SELECTAGGRESSIVEACTION_H
#define COMPLETED_ADVENTURE_V5C_LIB_STRATEGIES_SELECTAGGRESSIVEACTION_H

#include "SelectActionStrategy.h"

namespace adventure::v5c {

class SelectAggressiveAction : public SelectActionStrategy {
public:
    SelectAggressiveAction() = default;
    [[nodiscard]] ActionPtr SelectAction(
        const Player& player, const ActionVec& actions) const override;
};

} // namespace adventure::v5c

#endif // COMPLETED_ADVENTURE_V5C_LIB_STRATEGIES_SELECTAGGRESSIVEACTION_H
