#include <iostream>
#include "mars_rover.h"

int main()
{
	rover::Rover rover{std::make_shared<rover::Grid>(100, 100)};
    rover.executeCommands("RMMMLM");
    std::cout << "Rover Position: (" << rover.getPosition().x << ", " << rover.getPosition().y << ")\n";
    return 0;
}
