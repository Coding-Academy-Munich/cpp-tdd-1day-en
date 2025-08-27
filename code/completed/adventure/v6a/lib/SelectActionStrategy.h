// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LIB_SELECTACTIONSTRATEGY_H
#define COMPLETED_ADVENTURE_V6A_LIB_SELECTACTIONSTRATEGY_H

#include "Action.h"

namespace adventure::v6a {

class SelectActionStrategy {
public:
    SelectActionStrategy() = default;
    SelectActionStrategy(const SelectActionStrategy&) = delete;
    SelectActionStrategy(SelectActionStrategy&&) = delete;
    SelectActionStrategy& operator=(const SelectActionStrategy&) = delete;
    SelectActionStrategy& operator=(SelectActionStrategy&&) = delete;
    virtual ~SelectActionStrategy() = default;

    [[nodiscard]] virtual ActionPtr SelectAction(
        const Player& player, const ActionVec& actions) const
        = 0;
    [[nodiscard]] virtual bool IsInteractive() const { return false; }
};

} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_SELECTACTIONSTRATEGY_H
