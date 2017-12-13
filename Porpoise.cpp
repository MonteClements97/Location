#include <iostream>
#include "Location.h"
#include "Porpoise.h"

Porpoise::Porpoise(Location location) : location(location){
    times_requested = 0;
    total_latitude = location.getLatitude();
    total_longitude = location.getLongitude();
    std::cout << location << std::endl;
}

bool Porpoise::compare_porpoise(Porpoise * porpoise){
    return (location.distance(porpoise->location) >= 0.02);
}

void Porpoise::total_location(Porpoise * porpoise){
    times_requested++;
    porpoise->times_requested++;
    total_latitude += porpoise->location.getLatitude();
    total_longitude += porpoise->location.getLongitude();
    porpoise->total_latitude += location.getLatitude();
    porpoise->total_longitude += location.getLongitude();
}

bool Porpoise::check_location_equal(Porpoise * porpoise){
    return (total_latitude == porpoise->total_latitude && total_longitude == porpoise->total_longitude);
}

void Porpoise::calculate_true_location(){
    location.setLocation(total_latitude/(times_requested+1), total_longitude/(times_requested+1));
}

