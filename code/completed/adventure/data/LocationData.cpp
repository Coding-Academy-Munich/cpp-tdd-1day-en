// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"

namespace adventure::data {

std::vector<LocationData> simpleLocationDataVector
    = { { "Room 1", "You are in a bright room. There is a door to the north.",
            { { "north", "Room 2" } } },
          { "Room 2", "You are in a dark room. There is a door to the south.",
              { { "south", "Room 1" } } } };

std::vector<LocationData> dungeonLocationDataVector = {
    { "Vestibule", "You are in the Vestibule", { { "north", "Entrance Hall" } } },
    { "Entrance Hall", "You are in the Entrance Hall",
        { { "west", "Dark Corridor" }, { "east", "Brightly Lit Corridor" },
            { "south", "Vestibule" } } },
    { "Dark Corridor", "You are in the Dark Corridor",
        { { "west", "Treasure Chamber" }, { "east", "Entrance Hall" } } },
    { "Brightly Lit Corridor", "You are in the Brightly Lit Corridor",
        { { "west", "Entrance Hall" } }, { "Torch" } },
    { "Treasure Chamber", "You are in the Treasure Chamber",
        { { "east", "Dark Corridor" } }, { "Treasure Chest" } },
};
}