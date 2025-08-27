// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SkipTurnAction.h"

namespace adventure::v4c {

std::string SkipTurnAction::Description() const { return "Skip one turn."; }

void SkipTurnAction::Perform(Pawn& instigator) { }

} // namespace adventure::v4c