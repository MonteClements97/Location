#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include "Location.h"
#include "Dolphin.h"
#include "Porpoise.h"

int main() {
    char type_of_mammal;
    char string_latitude[12];
    char string_longitude[12];
    std::vector<Dolphin*> dolphins;
    std::vector<Porpoise*> porpoises;
    std::ifstream file_in;
    std::string file_name;


    std::cout << "Enter the name of the file you wish to open: ";
    std::cin >> file_name;
    file_in.open(file_name);
    while(!file_in.is_open()){
        std::cout << "That wasn't right, try again (enter q to quit): ";
    }
    if(file_in.is_open()){
        while(file_in.good()){
            file_in.get(type_of_mammal);
            file_in.get();
            if(type_of_mammal == 'P'){
                Porpoise * porpoise = new Porpoise(Location(file_in));
                file_in.get();
                porpoises.push_back(porpoise);
            } else if (type_of_mammal == 'D'){
                Dolphin * dolphin = new Dolphin(Location(file_in));
                file_in.get();
                dolphins.push_back(dolphin);
            }
            type_of_mammal = 0;
        }
    }
    file_in.close();
    std::vector<Dolphin*> fixed_dolphins;
    while(dolphins.size() != 0){
        Dolphin * current_dolphin = dolphins.front();
        dolphins.erase(dolphins.begin());
        fixed_dolphins.push_back(current_dolphin);
        for(int i = 0; i < dolphins.size(); i++){
            if(current_dolphin->compare_dolphin(dolphins[i])){
                continue;
            } else {
                current_dolphin->total_location(dolphins[i]);
            }
        }

    }

    dolphins.push_back(fixed_dolphins[0]);
    for (int i = 0; i < fixed_dolphins.size(); i++){
        bool are_the_same = false;
        unsigned long size_of_dolphins = dolphins.size();
        for (int j = 0; j < size_of_dolphins; j++){
            if(fixed_dolphins[i]->check_location_equal(dolphins[j])){
                are_the_same = true;
            }
        }
        if(!are_the_same){
            dolphins.push_back(fixed_dolphins[i]);
        }
    }
    for (int i = 0; i < dolphins.size(); i++){
        dolphins[i]->calculate_true_location();
    }

    std::vector<Porpoise*> fixed_porpoises;
    while(porpoises.size() != 0){
        Porpoise * current_porpoise = porpoises.front();
        porpoises.erase(porpoises.begin());
        fixed_porpoises.push_back(current_porpoise);
        for(int i = 0; i < porpoises.size(); i++){
            if(current_porpoise->compare_porpoise(porpoises[i])){
                continue;
            } else {
                current_porpoise->total_location(porpoises[i]);
            }
        }

    }

    porpoises.push_back(fixed_porpoises[0]);
    for (int i = 0; i < fixed_porpoises.size(); i++){
        bool are_the_same = false;
        unsigned long size_of_porpoises = porpoises.size();
        for (int j = 0; j < size_of_porpoises; j++){
            if(fixed_porpoises[i]->check_location_equal(porpoises[j])){
                are_the_same = true;
            }
        }
        if(!are_the_same){
            porpoises.push_back(fixed_porpoises[i]);
        }
    }
    for (int i = 0; i < porpoises.size(); i++){
        porpoises[i]->calculate_true_location();
    }

    std::cout << "Great circle test" << std::endl;

    std::cout << Location::PI << std::endl;

    Location aber(52.416090, -4.058268);
    Location snowdon(53.0685, -4.0763);


    std::cout << "Aberystwyth " << aber << std::endl;
    std::cout << "Snowdon " << aber << std::endl;

    std::cout << "Distance: " << aber.distance(snowdon) << std::endl;

    std::cout << "Aber latitude: " << aber.getLatitude() << std::endl;

    return 115;
}