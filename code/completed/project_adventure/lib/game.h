// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef PROJECT_ADVENTURE_LIB_GAME_H
#define PROJECT_ADVENTURE_LIB_GAME_H

#include <memory>
#include <stdexcept>
#include <vector>


#include "action.h"
#include "room.h"

namespace adv
{

class Game
{
public:
    explicit Game(const std::vector<Room>& rooms);

    void run();
    const Room& current_room() const;
    void perform(const Action& action);

    std::unique_ptr<Action> parse_command(std::string_view command_input);

private:
    Room* current_room_;
    std::vector<Room> rooms_;
};

} // namespace adv

#endif // PROJECT_ADVENTURE_LIB_GAME_H
