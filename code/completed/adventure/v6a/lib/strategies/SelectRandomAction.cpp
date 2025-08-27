// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SelectRandomAction.h"
#include "Player.h"
#include <algorithm>
#include <iterator>

namespace adventure::v6a {

ActionPtr SelectRandomAction::SelectAction(
    const Player& player, const ActionVec& actions) const
{
    ActionVec resultActions {actions};
    std::sample(actions.begin(), actions.end(), std::back_inserter(resultActions), 1,
        player.GetRandomEngine());
    return resultActions.back();
}

} // namespace adventure::v6a