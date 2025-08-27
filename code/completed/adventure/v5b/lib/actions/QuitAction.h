// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5B_LIB_ACTIONS_QUITACTION_H
#define COMPLETED_ADVENTURE_V5B_LIB_ACTIONS_QUITACTION_H

#include "Action.h"
#include <string>
#include <unordered_set>

namespace adventure::v5b {

class QuitAction : public Action {
public:
    QuitAction() = default;

    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] const std::unordered_set<ActionTag>& Tags() const override;
    void Perform(Player& instigator) const override;

protected:
    bool Equals(const Action& other) const override;
};

class QuitGameException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override { return "Quit game"; }
};

} // namespace adventure::v5b

#endif // COMPLETED_ADVENTURE_V5B_LIB_ACTIONS_QUITACTION_H
