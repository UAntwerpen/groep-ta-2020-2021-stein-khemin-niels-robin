cmake_minimum_required(VERSION 3.16)
project(TA)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_CXX_FLAGS "-Wall -Werror")
#set(CMAKE_EXE_LINKER_FLAGS -pthread)

add_executable(TA main.cpp CellulaireAutomaat.cpp CellulaireAutomaat.h Cell.cpp Cell.h Lib.h lib/DesignByContract.h)