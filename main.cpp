#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include "Location.h"
#include "Mammal.h"
#include "Dolphin.h"
#include "Porpoise.h"

int main() {
    char type_of_mammal;
    double longitude;
    double latitude;
    char string_latitude[12];
    char string_longitude[12];
    std::vector<Dolphin*> dolphins;
    std::vector<Porpoise*> porpoises;
    std::ifstream file_in;
    std::string file_name;


    std::cout << "Enter the name of the file you wish to open: ";
    std::cin >> file_name;
    file_in.open(file_name);
    if(file_in.is_open()){
        while(file_in.good()){
            file_in.get(type_of_mammal);
            if(type_of_mammal == 'P'){
                file_in.get(type_of_mammal);
                file_in.getline(string_latitude, 20, ' ');
                file_in.getline(string_longitude, 20);
                Porpoise * porpoise = new Porpoise(Location(atof(string_latitude), atof(string_longitude)));
                porpoises.push_back(porpoise);

            } else if (type_of_mammal == 'D'){
                file_in.get(type_of_mammal);
                file_in.getline(string_latitude, 20, ' ');
                file_in.getline(string_longitude, 20);
                Dolphin * dolphin = new Dolphin(Location(atof(string_latitude), atof(string_longitude)));
                dolphins.push_back(dolphin);
            }
        }
    }
    std::cout << "Great circle test" << std::endl;

    std::cout << Location::PI << std::endl;

    Location aber(52.416090, -4.058268);
    Location snowdon(53.0685, -4.0763);

    Mammal fred(aber);

    std::cout << "Aberystwyth " << aber << std::endl;
    std::cout << "Snowdon " << aber << std::endl;

    std::cout << "Distance: " << aber.distance(snowdon) << std::endl;

    std::cout << "Aber latitude: " << aber.getLatitude() << std::endl;

    return 0;
}