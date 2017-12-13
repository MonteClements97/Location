

#ifndef LOCATIONS_PORPOISE_H
#define LOCATIONS_PORPOISE_H

class Porpoise {
public:
    Porpoise(Location location);
    ~Porpoise();
    bool compare_porpoise(Porpoise *porpoise);
    bool compare_porpoise_pod(Porpoise * porpoise);
    void total_location(Porpoise *porpoise);
    bool check_location_equal(Porpoise *porpoise);
    void calculate_true_location();
    void display_location();

private:
    Location location;
    double total_longitude;
    double total_latitude;
    int times_requested;
};
#endif //LOCATIONS_PORPOISE_H