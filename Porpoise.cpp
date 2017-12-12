#include <iostream>
#include "Location.h"
#include "Porpoise.h"

Porpoise::Porpoise(Location location) : location(location) {
    std::cout << location << std::endl;
}

