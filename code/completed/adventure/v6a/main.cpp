// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Game.h"
#include "LocationData.h"
#include "WorldFactory.h"
#include "cli/CliGameObserver.h"
#include "strategies/SelectActionInteractively.h"
#include <iostream>
#include <memory>
#include <optional>

using namespace adventure::data;
using namespace adventure::v6a;

std::optional<std::unique_ptr<SelectActionStrategy>>
SelectStrategy(const std::string& strategyArg);

int main(int argc, const char* argv[]) {
    std::string strategyOption {"random"};
    if (argc > 1) {
        strategyOption = argv[1];
    }

    Game game {dungeonLocationDataVector, std::make_shared<CliGameObserver>()};
    game.AddPlayer("Test Player", strategyOption);
    game.Run();

    return 0;
}
