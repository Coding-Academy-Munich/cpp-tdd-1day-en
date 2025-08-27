#include "LocationData.h"
#include "World.h"
#include <iostream>

using namespace adventure_sk2;

int main()
{
    World world { data::simpleLocations };
    std::cout << world << '\n';
    for (const auto& [name, location] : world.GetLocations()) {
        std::cout << location << '\n';
    }
    std::cout << world.GetLocation("Room 1") << '\n'
              << world.GetLocation("Room 2") << '\n';
    return 0;
}