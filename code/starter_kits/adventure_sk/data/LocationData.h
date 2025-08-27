#pragma once
#ifndef STARTER_KITS_ADVENTURE_SK_DATA_LOCATIONDATA_H
#define STARTER_KITS_ADVENTURE_SK_DATA_LOCATIONDATA_H

#include <string>
#include <unordered_map>
#include <vector>

namespace adventure_sk::data {

struct LocationData {
    std::string name;
    std::string description;
    std::unordered_map<std::string, std::string> connections = {};
    std::vector<std::string> objects = {};
};

extern std::vector<LocationData> simpleLocations;
extern std::vector<LocationData> dungeonLocations;

} // namespace adventure_sk::data

#endif // STARTER_KITS_ADVENTURE_SK_DATA_LOCATIONDATA_H
