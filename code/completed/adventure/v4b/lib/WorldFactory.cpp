// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "WorldFactory.h"

namespace adventure::v4b {

World WorldFactory::create(const std::vector<data::LocationData>& locationDataVector,
    const std::string& initialLocationName)
{
    World world {initialLocationName};
    world.locations.reserve(locationDataVector.size());
    for (const auto& locationData : locationDataVector) {
        world.locations.emplace(locationData.name, locationData);
    }
    for (const auto& locationData : locationDataVector) {
        for (const auto& [direction, target] : locationData.connections) {
            world.GetLocation(locationData.name)
                .SetConnectedLocation(direction, world.GetLocation(target));
        }
    }
    return world;
}

World WorldFactory::create(const std::vector<data::LocationData>& locationDataVector)
{
    return create(locationDataVector, locationDataVector[0].name);
}
}