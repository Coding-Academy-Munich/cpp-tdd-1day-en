// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5C_LIB_STRATEGIES_SELECTACTIONINTERACTIVELY_H
#define COMPLETED_ADVENTURE_V5C_LIB_STRATEGIES_SELECTACTIONINTERACTIVELY_H

#include "SelectActionStrategy.h"
namespace adventure::v5c {

class SelectActionInteractively : public SelectActionStrategy {
public:
    SelectActionInteractively() = default;
    [[nodiscard]] ActionPtr SelectAction(
        const Player& player, const ActionVec& actions) const override;
    [[nodiscard]] bool IsInteractive() const override;
};

} // namespace adventure::v5c

#endif // COMPLETED_ADVENTURE_V5C_LIB_STRATEGIES_SELECTACTIONINTERACTIVELY_H
