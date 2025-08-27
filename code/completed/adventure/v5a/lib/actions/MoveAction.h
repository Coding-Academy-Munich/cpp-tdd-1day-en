// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5A_LIB_MOVEACTION_H
#define COMPLETED_ADVENTURE_V5A_LIB_MOVEACTION_H

#include "Action.h"

namespace adventure::v5a {

class MoveAction : public Action {
public:
    explicit MoveAction(std::string direction);
    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] const std::unordered_set<ActionKind>& Tags() const override;
    void Perform(Player& instigator) const override;

private:
    std::string direction;
};

} // namespace adventure::v5a

#endif // COMPLETED_ADVENTURE_V5A_LIB_MOVEACTION_H
