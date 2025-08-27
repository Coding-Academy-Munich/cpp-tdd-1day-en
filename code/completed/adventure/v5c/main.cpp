// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"
#include "Player.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/QuitAction.h"
#include "cli/CliPlayerObserver.h"
#include "strategies/SelectActionInteractively.h"
#include "strategies/SelectAggressiveAction.h"
#include "strategies/SelectHelpfulAction.h"
#include "strategies/SelectLastAction.h"
#include <iostream>
#include <memory>
#include <optional>

using namespace adventure::data;
using namespace adventure::v5c;

std::optional<std::unique_ptr<SelectActionStrategy>> SelectStrategy(
    const std::string& strategyArg);

int main(int argc, const char* argv[])
{
    World world {WorldFactory::create(dungeonLocationDataVector)};
    std::unique_ptr<SelectActionStrategy> strategy {
        std::make_unique<SelectActionInteractively>()};

    if (argc > 1) {
        const std::string strategyOption {argv[1]};
        if (auto selectedStrategy {SelectStrategy(strategyOption)}) {
            strategy = std::move(*selectedStrategy);
        } else {
            std::cout << "Unknown option: " << argv[1] << '\n';
            return 1;
        }
    }

    Player player {"Test Player", world.GetInitialLocation(), std::move(strategy)};
    std::shared_ptr<PlayerObserver> observer {std::make_shared<CliPlayerObserver>()};
    player.RegisterObserver(observer);

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

std::optional<std::unique_ptr<SelectActionStrategy>> SelectStrategy(
    const std::string& strategyArg)
{
    if (strategyArg == "interactive") {
        return {std::make_unique<SelectActionInteractively>()};
    } else if (strategyArg == "last" || strategyArg == "last-action") {
        return {std::make_unique<SelectLastAction>()};
    } else if (strategyArg == "random" || strategyArg == "random-action") {
        return {std::make_unique<SelectRandomAction>()};
    } else if (strategyArg == "aggressive" || strategyArg == "aggressive-action") {
        return {std::make_unique<SelectAggressiveAction>()};
    } else if (strategyArg == "helpful" || strategyArg == "helpful-action") {
        return {std::make_unique<SelectHelpfulAction>()};
    } else {
        return {};
    }
}
