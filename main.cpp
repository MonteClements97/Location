#include <iostream>
#include <fstream>
#include <vector>
#include "Location.h"
#include "Dolphin.h"
#include "Porpoise.h"

int main() {
    char type_of_mammal;
    std::vector<Dolphin*> dolphins;
    std::vector<Porpoise*> porpoises;
    std::ifstream file_in;
    std::string file_name;
    std::cout << "Enter the name of the file you wish to open: ";
    std::cin >> file_name;
    file_in.open(file_name);
    char debug;
    while(!file_in.is_open()){
        std::cout << "That wasn't right, try again (enter q to quit): ";
        std::cin >> file_name;
        file_in.open(file_name);
    }
    std::cout << "Read in sightings are as follows: " << std::endl << std::endl;
    if(file_in.is_open()){
        while(file_in.good()){
            file_in.get(type_of_mammal);
            if (type_of_mammal == '\n') file_in.get(type_of_mammal);
            file_in.get(debug);
            if(type_of_mammal == 'P'){
                Porpoise * porpoise = new Porpoise(Location(file_in));
                file_in.get(debug);
                porpoises.push_back(porpoise);
            } else if (type_of_mammal == 'D'){
                Dolphin * dolphin = new Dolphin(Location(file_in));
                file_in.get(debug);
                dolphins.push_back(dolphin);
            }
            type_of_mammal = 0;
        }
    }
    file_in.close();

    std::cout << std::endl;

    std::vector<Dolphin*> fixed_dolphins;
    // checks to see if the current dolphin is 0.02 nautical miles from the ith dolphin,
    // if it is, both the current and ith dolphin will increase their total latitude, longitude and times requested
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
    fixed_dolphins.erase(fixed_dolphins.begin());
    // loops through each dolphin in the newly created vector. Deletes all duplicated dolphins and assigns each
    // unique dolphin back to the dolphin vector
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
        } else {
            delete fixed_dolphins[i];
        }
    }
    std::cout << "The true locations of the mammals are as follows: " << std::endl << std::endl;
    for (int i = 0; i < dolphins.size(); i++){
        dolphins[i]->calculate_true_location();
        std::cout << "True dolphin location: ";
        dolphins[i]->display_location();
    }

    // checks to see if the current porpoise is 0.02 nautical miles from the ith porpoise,
    // if it is, both the current and ith porpoise will increase their total latitude, longitude and times requested
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
    // loops through each porpoise in the newly created vector. Deletes all duplicated porpoises and assigns each
    // unique porpoise back to the porpoise vector
    if(fixed_porpoises.size() != 0){
        porpoises.push_back(fixed_porpoises[0]);
        fixed_porpoises.erase(fixed_porpoises.begin());
    }
    for (int i = 0; i < fixed_porpoises.size(); i++) {
        bool are_the_same = false;
        unsigned long size_of_porpoises = porpoises.size();
        for (int j = 0; j < size_of_porpoises; j++) {
            if (fixed_porpoises[i]->check_location_equal(porpoises[j])) {
                are_the_same = true;
            }
        }
        if (!are_the_same) {
            porpoises.push_back(fixed_porpoises[i]);
        } else {
            delete fixed_porpoises[i];
        }
    }

    for (int i = 0; i < porpoises.size(); i++){
        porpoises[i]->calculate_true_location();
        std::cout << "True porpoise location: ";
        porpoises[i]->display_location();
    }

    std::cout << std::endl;

    fixed_dolphins.clear();
    fixed_porpoises.clear();

    //POD MISSION

    // Goes through every dolphin and checks if the dolphin is within 0.1 nautical miles from any other dolphin
    // Once it has done that, if it found any, it will then check if that dolphin is within 0.1 nautical miles from
    // any dolphin. This will keep happening until there isn't any dolphins left to check. Every dolphin it found that
    // were near each other will then be printed out as a pod. Single dolphins are simply discarded.
    // The fixed vector is re-used from earlier so another vector did not need to be created.
    bool there_are_pods = false;
    int total_pods = 0;
    int animals_in_current_pod;
    std::vector<Dolphin *> dolphin_pod;
    Dolphin * current_dolphin;
    while(dolphins.size() != 0){
        dolphin_pod.clear();
        fixed_dolphins.clear();
        animals_in_current_pod = 1;
        current_dolphin = dolphins.front();
        dolphins.erase(dolphins.begin());
        fixed_dolphins.push_back(current_dolphin);
        while(fixed_dolphins.size() != 0){
            for(int i = 0; i < dolphins.size(); i++){
                if(current_dolphin->compare_dolphin_pod(dolphins[i])){
                    fixed_dolphins.push_back(dolphins[i]);
                    animals_in_current_pod++;
                    dolphins.erase(dolphins.begin() + i);
                    i--;
                }
            }
            if (animals_in_current_pod > 1){
                dolphin_pod.push_back(current_dolphin);
                fixed_dolphins.erase(fixed_dolphins.begin());
                if(fixed_dolphins.size() != 0){
                    current_dolphin = fixed_dolphins.front();
                }
            } else {
                fixed_dolphins.erase(fixed_dolphins.begin());
                delete current_dolphin;
            }

        }
        if(animals_in_current_pod > 1){
            total_pods++;
            if (!there_are_pods){
                std::cout << "Dolphin pods are as follows: " << std::endl;
                there_are_pods = true;
            }
            std::cout << std::endl << "A dolphin pod containing " << animals_in_current_pod << " dolphins: " << std::endl;
            for (int i = 0; i < dolphin_pod.size(); i++){
                std::cout << "Dolphin location: ";
                dolphin_pod[i]->display_location();
            }
        }


    }

    // Goes through every porpoise and checks if the porpoise is within 0.1 nautical miles from any other porpoise
    // Once it has done that, if it found any, it will then check if that porpoise is within 0.1 nautical miles from
    // any porpoise. This will keep happening until there isn't any porpoises left to check. Every porpoise it found that
    // were near each other will then be printed out as a pod. Single porpoises are simply discarded.
    // The fixed vector is re-used from earlier so another vector did not need to be created.
    there_are_pods = false;
    std::vector<Porpoise *> porpoise_pod;
    Porpoise * current_porpoise;
    while(porpoises.size()!=0){
        porpoise_pod.clear();
        fixed_porpoises.clear();
        animals_in_current_pod = 1;
        current_porpoise = porpoises.front();
        porpoises.erase(porpoises.begin());
        fixed_porpoises.push_back(current_porpoise);
        while(fixed_porpoises.size() != 0){
            for(int i = 0; i < porpoises.size(); i++){
                if(current_porpoise->compare_porpoise_pod(porpoises[i])){
                    fixed_porpoises.push_back(porpoises[i]);
                    animals_in_current_pod++;
                    porpoises.erase(porpoises.begin() + i);
                    i--;
                }
            }
            if (animals_in_current_pod > 1){
                porpoise_pod.push_back(current_porpoise);
                fixed_porpoises.erase(fixed_porpoises.begin());
                if(fixed_porpoises.size() != 0){
                    current_porpoise = fixed_porpoises.front();
                }
            } else {
                fixed_porpoises.erase(fixed_porpoises.begin());
                delete current_porpoise;
            }

        }
        if(animals_in_current_pod > 1){
            total_pods++;
            if (!there_are_pods){
                std::cout << std::endl << "Porpoise pods are as follows: " << std::endl;
                there_are_pods = true;
            }
            std::cout << std::endl << "A porpoise pod containing " << animals_in_current_pod << " porpoises"<< std::endl;
            for (int i = 0; i < porpoise_pod.size(); i++){
                std::cout << "Porpoise location: ";
                porpoise_pod[i]->display_location();
            }
        }


    }

    std::cout << "There are a total of " << total_pods << " pods" << std::endl;

    return 115;
}