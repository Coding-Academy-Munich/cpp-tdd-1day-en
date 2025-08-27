// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SelectHelpfulAction.h"
#include "ActionTag.h"

namespace adventure::v6a {

ActionPtr SelectHelpfulAction::SelectAction(
    const Player& player, const ActionVec& actions) const
{
    ActionVec resultActions {ActionsWithTag(actions, ActionTag::Helpful)};
    if (resultActions.empty()) {
        resultActions = ActionsWithoutTag(actions, ActionTag::Aggressive);
    }
    return resultActions.empty() ? nullptr : resultActions.back();
}

} // namespace adventure::v6a