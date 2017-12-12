cmake_minimum_required(VERSION 3.6)
project(Locations)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Location.cpp Location.h Mammal.h Mammal.cpp Dolphin.h Dolphin.cpp Porpoise.cpp Porpoise.h)
add_executable(Locations ${SOURCE_FILES})