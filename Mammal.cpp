
#include <iostream>
#include "Location.h"
#include "Mammal.h"

Mammal::Mammal(Location location) : location(location){
    std::cout << location << std::endl;
}
