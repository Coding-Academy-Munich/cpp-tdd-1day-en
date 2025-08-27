// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef PROJECT_ADVENTURE_LIB_ROOM_H
#define PROJECT_ADVENTURE_LIB_ROOM_H

#include <string>

namespace adv
{

class Room
{
public:
    Room(const std::string& name, const std::string& description) :
        name_{name}, description_{description}
    {
    }

    std::string name() const;
    const std::string& description() const;

private:
    std::string name_{};
    std::string description_{};
};

} // namespace adv

#endif // PROJECT_ADVENTURE_LIB_ROOM_H
