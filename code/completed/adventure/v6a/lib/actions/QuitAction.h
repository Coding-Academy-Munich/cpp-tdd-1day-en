// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_ADVENTURE_V6A_LIB_ACTIONS_QUITACTION_H
#define COMPLETED_ADVENTURE_V6A_LIB_ACTIONS_QUITACTION_H

#include "Action.h"
#include <string>
#include <unordered_set>

namespace adventure::v6a {

class QuitAction : public Action {
public:
    QuitAction() = default;

    [[nodiscard]] std::string Description() const override;
    [[nodiscard]] ActionTagSet Tags() const override;
    void Perform(Player& instigator) const override;

protected:
    [[nodiscard]] bool Equals(const Action& other) const override;
};

class QuitGameException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override { return "Quit game"; }
};

} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_ACTIONS_QUITACTION_H
