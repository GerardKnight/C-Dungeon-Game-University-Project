cmake_minimum_required(VERSION 3.30)
project(Coursework)

set(CMAKE_CXX_STANDARD 20)


add_executable(Coursework main.cpp)
add_executable(Coursework Misc_functions.cpp)
add_executable(Coursework Misc_functions.h
        Player_stats.cpp
        Player_stats.h
        Enemy.cpp
        Enemy.h
        Combat.cpp
        Combat.h
        Room.cpp
        Room.h
        Settings.cpp
        Settings.h
        Default_Potion.cpp
        Default_Potion.h
        Floor.cpp
        Floor.h)
