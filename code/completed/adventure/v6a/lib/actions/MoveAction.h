// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_ADVENTURE_V6A_LIB_MOVEACTION_H
#define COMPLETED_ADVENTURE_V6A_LIB_MOVEACTION_H

#include "Action.h"
#include "ActionTag.h"

namespace adventure::v6a {

class MoveAction : public Action {
public:
    explicit MoveAction(std::string direction);
    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] ActionTagSet Tags() const override;
    void Perform(Player& instigator) const override;

protected:
    [[nodiscard]] bool Equals(const Action& other) const override;

private:
    std::string direction_;
};

} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_MOVEACTION_H
