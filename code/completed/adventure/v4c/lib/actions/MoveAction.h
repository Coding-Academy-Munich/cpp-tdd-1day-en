// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V4C_LIB_MOVEACTION_H
#define COMPLETED_ADVENTURE_V4C_LIB_MOVEACTION_H

#include "Action.h"

namespace adventure::v4c {

class MoveAction : public Action {
public:
    explicit MoveAction(std::string direction);

    [[nodiscard]] std::string Description() const override;
    void Perform(Pawn& instigator) override;

private:
    std::string direction;
};

} // namespace adventure::v4c

#endif // COMPLETED_ADVENTURE_V4C_LIB_MOVEACTION_H
