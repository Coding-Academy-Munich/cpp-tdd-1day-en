// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_ADVENTURE_DATA_LOCATIONDATA_H
#define COMPLETED_ADVENTURE_DATA_LOCATIONDATA_H

#include <string>
#include <unordered_map>
#include <vector>

namespace adventure::data {
struct LocationData {
    std::string name;
    std::string description;
    std::unordered_map<std::string, std::string> connections = {};
    std::vector<std::string> objects = {};
};

extern std::vector<LocationData> simpleLocationDataVector;
extern std::vector<LocationData> dungeonLocationDataVector;
} // namespace adventure::data

#endif // COMPLETED_ADVENTURE_DATA_LOCATIONDATA_H
