// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_ADVENTURE_V5C_LIB_ACTIONS_SKIPTURNACTION_H
#define COMPLETED_ADVENTURE_V5C_LIB_ACTIONS_SKIPTURNACTION_H

#include "Action.h"
#include "ActionTag.h"

namespace adventure::v5c {

class SkipTurnAction : public Action {
public:
    SkipTurnAction() = default;

    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] ActionTagSet Tags() const override;
    void Perform(Player& instigator) const override;

protected:
    [[nodiscard]] bool Equals(const Action& other) const override;
};

} // namespace adventure::v5c

#endif // COMPLETED_ADVENTURE_V5C_LIB_ACTIONS_SKIPTURNACTION_H
