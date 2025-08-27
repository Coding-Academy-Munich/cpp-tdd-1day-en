// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"
#include "Player.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/QuitAction.h"
#include <iostream>
#include <optional>

using namespace adventure::data;
using namespace adventure::v5b;

std::optional<PlayerStrategy> SelectStrategy(const std::string& strategyArg);

int main(int argc, const char* argv[])
{
    World world {WorldFactory::create(dungeonLocationDataVector)};
    PlayerStrategy strategy {PlayerStrategy::Interactive};

    if (argc > 1) {
        const std::string strategyOption {argv[1]};
        if (auto selectedStrategy {SelectStrategy(strategyOption)}) {
            strategy = *selectedStrategy;
        } else {
            std::cout << "Unknown option: " << argv[1] << '\n';
            return 1;
        }
    }

    Player player {"Test Player", world.GetInitialLocation(), strategy};
    try {
        for (int i {}; i < 10; ++i) {
            std::cout << "Turn " << i + 1 << ": Player [" << player << "]\n";
            player.TakeTurn();
        }
    } catch (const QuitGameException&) {
        std::cout << "Goodbye!\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    std::cout << "Player [" << player << "]\n";

    return 0;
}

std::optional<PlayerStrategy> SelectStrategy(const std::string& strategyArg)
{
    if (strategyArg == "interactive") {
        return {PlayerStrategy::Interactive};
    } else if (strategyArg == "last" || strategyArg == "last-action") {
        return {PlayerStrategy::LastAction};
    } else if (strategyArg == "random" || strategyArg == "random-action") {
        return {PlayerStrategy::RandomAction};
    } else if (strategyArg == "aggressive" || strategyArg == "aggressive-action") {
        return {PlayerStrategy::Aggressive};
    } else if (strategyArg == "helpful" || strategyArg == "helpful-action") {
        return {PlayerStrategy::Helpful};
    } else {
        return {};
    }
}
