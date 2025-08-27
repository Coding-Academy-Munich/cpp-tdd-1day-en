// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SelectAggressiveAction.h"
#include "ActionTag.h"

namespace adventure::v5c {
ActionPtr SelectAggressiveAction::SelectAction(
    const Player& player, const ActionVec& actions) const
{
    ActionVec resultActions {ActionsWithTag(actions, ActionTag::Aggressive)};
    if (resultActions.empty()) {
        resultActions = ActionsWithoutTag(actions, ActionTag::Helpful);
    }
    return resultActions.empty() ? nullptr : resultActions.back();
}

} // namespace adventure::v5c