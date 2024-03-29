#include <iostream>
#include <iomanip>
#include "Location.h"
#include "Dolphin.h"

Dolphin::Dolphin(Location location) : location(location){
    times_requested = 0;
    total_latitude = location.getLatitude();
    total_longitude = location.getLongitude();
    std::cout << "Dolphin initial sighting: ";
    display_location();
}

Dolphin::~Dolphin(){
    location.setLocation(0,0);
    times_requested = 0;
    total_latitude = 0;
    total_longitude = 0;
}

bool Dolphin::compare_dolphin_pod(Dolphin *dolphin) {
    return (location.distance(dolphin->location) <= 0.1);
}

bool Dolphin::compare_dolphin(Dolphin * dolphin){
    return (location.distance(dolphin->location) >= 0.02);
}

void Dolphin::total_location(Dolphin * dolphin){
    times_requested++;
    dolphin->times_requested++;
    total_latitude += dolphin->location.getLatitude();
    total_longitude += dolphin->location.getLongitude();
    dolphin->total_latitude += location.getLatitude();
    dolphin->total_longitude += location.getLongitude();
}

bool Dolphin::check_location_equal(Dolphin * dolphin){
    return (total_latitude == dolphin->total_latitude && total_longitude == dolphin->total_longitude);
}

void Dolphin::calculate_true_location(){
    location.setLocation(total_latitude/(times_requested+1), total_longitude/(times_requested+1));
}

void Dolphin::display_location(){
    std::cout << std::setprecision(8) << location.getLatitude() << ' ';
    std::cout << std::setprecision(7) << location.getLongitude() << std::endl;
}