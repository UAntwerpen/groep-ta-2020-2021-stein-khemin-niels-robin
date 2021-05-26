cmake_minimum_required(VERSION 3.16)
project(TA)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(TA main.cpp CellulaireAutomaat.cpp CellulaireAutomaat.h
        Cell.cpp Cell.h
        Lib.h lib/DesignByContract.h
        Rules.cpp Rules.h
        Utils.cpp Utils.h
        CitySimulation.h
        Vehicle.cpp Vehicle.h
        Citizen.cpp Citizen.h
        Transport.cpp Transport.h Pathfinding.cpp PFCell.cpp PFCell.h Pathfinding.cpp Pathfinding.h Template.cpp)