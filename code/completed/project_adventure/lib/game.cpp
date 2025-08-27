// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "game.h"

#include <iostream>

namespace adv
{

Game::Game(const std::vector<Room>& rooms) : rooms_{rooms}
{
    if (rooms_.empty())
    {
        throw std::runtime_error{"No rooms given"};
    }
    current_room_ = &rooms_.front();
}

void Game::run()
{
    std::string input{};
    do
    {
        std::cout << current_room().description() << std::endl;
        std::cout << "Enter command: ";
        getline(std::cin, input);
        std::unique_ptr<Action> action = parse_command(input);
        perform(*action);
    }
    while (input != "bye");
}

const Room& Game::current_room() const
{
    return *current_room_;
}

void Game::perform(const Action& action)
{
    if (rooms_.size() > 1)
    {
        current_room_ = &rooms_[1];
    }
    else
    {
        throw std::runtime_error{"Not enough rooms."};
    }
}

std::unique_ptr<Action> Game::parse_command(std::string_view command_input)
{
    return std::make_unique<MoveAction>("north");
}

} // namespace adv
