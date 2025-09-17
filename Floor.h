//
// Created by User on 25/04/2025.
//

#ifndef FLOOR_H
#define FLOOR_H
#include <iostream>
#include "Room.cpp"
#pragma once

class Floor {
private:
    int floor_num;
    Room rooms[10][10];//array deliberately too large. simpler than making it dynamic.
    int trapdoor_cords[2];//to next floor
    int key_cords[2];//needed to open trapdoor
    int entrance_cords[2];//first room entered
    int size;
    std::string enemies[10][10];
    std::string items[10][10];
    int current_cords[2];
    bool has_left_floor=false;
    bool player_has_key=false;
    void generate_rooms();
    void calm();
    void enter_room();
public:
    Floor(int new_floor_num);
    int floor_main();
    ~Floor()=default;
};



#endif //FLOOR_H
