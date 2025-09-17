//
// Created by User on 23/04/2025.
//

#ifndef ROOM_H
#define ROOM_H
#pragma once
#include <iostream>
#include "Default_Potion.cpp"
#include "Misc_functions.cpp"
#include "Player_stats.cpp"


extern Invincibility_Potion invincibility_potion;
extern Health_Potion health_potion;
extern Double_Damage_Potion double_damage_potion;
extern Player_stats player_stats;

class Room {
protected:
    int cords[2];//x,y
    int floor;//level of the dungeon
    bool doors_open[4];//north, east, south, west
    bool has_enemy;
    std::string enemy_type;//enemy types
    bool has_item;
    std::string item_type;//potion, keys, etc.
    bool has_trapdoor;//exit to next floor. cant go through without the key.
    bool has_key;
    bool has_been_initialised=false;
    void work_out_doors();
public:
    void init_Room(int new_cords[], int new_floor, std::string& new_enemy_type, std::string& new_item_type, bool is_trapdoor_room, bool has_key_new);
    bool get_doors_open(int n);
    bool get_is_trapdoor_room();
    std::string get_enemy_type();
    bool get_has_enemy();
    std::string get_item_type();
    bool get_has_item();
    bool get_has_key();
    void take_key();
    void take_item();
    void kill_enemy();
    ~Room()= default;
};

#endif //ROOM_H
