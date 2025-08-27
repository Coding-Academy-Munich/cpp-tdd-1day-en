// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5B_LIB_MOVEACTION_H
#define COMPLETED_ADVENTURE_V5B_LIB_MOVEACTION_H

#include "Action.h"

namespace adventure::v5b {

class MoveAction : public Action {
public:
    MoveAction() = default;

    explicit MoveAction(std::string direction);
    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] const std::unordered_set<ActionTag>& Tags() const override;
    void Perform(Player& instigator) const override;

protected:
    [[nodiscard]] bool Equals(const Action& other) const override;

private:
    std::string direction;
};

} // namespace adventure::v5b

#endif // COMPLETED_ADVENTURE_V5B_LIB_MOVEACTION_H
