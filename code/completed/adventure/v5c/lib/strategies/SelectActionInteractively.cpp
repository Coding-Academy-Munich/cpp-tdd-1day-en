// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SelectActionInteractively.h"
#include <iostream>

namespace adventure::v5c {

ActionPtr SelectActionInteractively::SelectAction(
    const Player& player, const ActionVec& actions) const
{
    int selectedActionIndex {};
    while (true) {
        std::cout << "Available actions:\n";
        for (int i {}; i < actions.size(); ++i) {
            std::cout << "  " << i + 1 << ": " << actions[i]->Description() << '\n';
        }
        std::cin >> selectedActionIndex;
        if (selectedActionIndex >= 1 && selectedActionIndex <= actions.size()) {
            return actions.at(selectedActionIndex - 1);
        } else {
            std::cout << "Please select a valid action index.\n";
        }
    }
}

bool SelectActionInteractively::IsInteractive() const { return true; }

} // namespace adventure::v5c