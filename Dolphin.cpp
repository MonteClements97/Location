#include <iostream>
#include "Location.h"
#include "Dolphin.h"

Dolphin::Dolphin(Location location) : location(location) {
    std::cout << location << std::endl;
}
