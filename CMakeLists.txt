cmake_minimum_required(VERSION 3.16)
project(TA)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS -pthread)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

#QT
set(Qt5Core_DIR "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5Core")
set(Qt5Widgets_DIR "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5Widgets")
set(Qt5Gui_DIR "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake\\Qt5Gui")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

set(CMAKE_CXX_FLAGS "-Wall -Werror -fopenmp")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

add_executable(TA
        main.cpp
        CellulaireAutomaat.cpp CellulaireAutomaat.h
        Cell.cpp Cell.h
        Lib.h lib/DesignByContract.h
        GeneticAlgorithm.cpp GeneticAlgorithm.h
        CitySimulation.cpp CitySimulation.h
        Vehicle.cpp Vehicle.h
        Citizen.cpp Citizen.h
        Transport.cpp Transport.h 
        PFCell.cpp PFCell.h 
        Pathfinding.cpp Pathfinding.h
        Building.cpp Building.h
        MainWindow.cpp MainWindow.h
        )

qt5_use_modules(TA Core Widgets Gui)
