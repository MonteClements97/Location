
#ifndef LOCATIONS_DOLPHIN_H
#define LOCATIONS_DOLPHIN_H

class Dolphin {

public:
    Dolphin(Location location);
    bool compare_dolphin(Dolphin * dolphin);
    void total_location(Dolphin * dolphin);
    bool check_location_equal(Dolphin * dolphin);
    void calculate_true_location();

private:
    Location location;
    double total_longitude;
    double total_latitude;
    int times_requested;

};

#endif //LOCATIONS_DOLPHIN_H
