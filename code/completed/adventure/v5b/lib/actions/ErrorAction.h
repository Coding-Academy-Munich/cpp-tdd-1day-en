// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5B_LIB_ACTIONS_ERRORACTION_H
#define COMPLETED_ADVENTURE_V5B_LIB_ACTIONS_ERRORACTION_H

#include "Action.h"

namespace adventure::v5b {

class ErrorAction : public Action {
public:
    ErrorAction() = default;

    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] const std::unordered_set<ActionTag>& Tags() const override;
    void Perform(Player& instigator) const override;

protected:
    bool Equals(const Action& other) const override;
};

} // namespace adventure::v5b

#endif // COMPLETED_ADVENTURE_V5B_LIB_ACTIONS_ERRORACTION_H
