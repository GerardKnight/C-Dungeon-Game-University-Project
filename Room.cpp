//
// Created by User on 23/04/2025.
//

#include "Room.h"
#pragma once


void Room::work_out_doors() {//sets which doors the player may go through, depending on location.
    if (cords[0]==0) {
        doors_open[1]=true;
        doors_open[3]=false;
    }else if (cords[0]==3+floor) {
        doors_open[1]=false;
        doors_open[3]=true;
    }else {
        doors_open[1]=true;
        doors_open[3]=true;
    }
    if (cords[1]==0) {
        doors_open[2]=false;
        doors_open[0]=true;
    }else if (cords[1]==3+floor) {
        doors_open[2]=true;
        doors_open[0]=false;
    }else {
        doors_open[2]=true;
        doors_open[0]=true;
    }
}

void Room::init_Room(int new_cords[], int new_floor, std::string& new_enemy_type, std::string& new_item_type, bool is_trapdoor_room, bool has_key_new) {
    //function exists to initialise rooms in a for loop. initialising from an array is very awkward in c++
    if (has_been_initialised) {//prevents redoing the same one
        std::cout<<"You've already initialised this room.\n";
        return;
    }
    cords[0]=new_cords[0];
    cords[1]=new_cords[1];
    floor=new_floor;
    enemy_type=new_enemy_type;
    has_enemy=(enemy_type!="none");
    item_type=new_item_type;
    has_item=(item_type!="none");
    has_trapdoor=is_trapdoor_room;
    has_key=has_key_new;
    has_been_initialised=true;
    work_out_doors();
}
bool Room::get_doors_open(int n) {
    return doors_open[n];
}
bool Room::get_is_trapdoor_room() {
    return has_trapdoor;
}
std::string Room::get_enemy_type() {
    return enemy_type;
}
bool Room::get_has_enemy() {
    return has_enemy;
}
std::string Room::get_item_type(){
    return item_type;
}
bool Room::get_has_item(){
    return has_item;
}
bool Room::get_has_key() {
    return has_key;
}
void Room::take_key() {
    has_key=false;
}
void Room::take_item() {
    if (has_item) {
        if (item_type=="Invincibility Potion") {
            invincibility_potion.pick_up(1);
        }else if (item_type=="Health Potion") {
            health_potion.pick_up(1);
        }else if (item_type=="Double Damage Potion"){
            double_damage_potion.pick_up(1);
        }
        has_item=false;
        item_type="none";
    }
}
void Room::kill_enemy() {
    has_enemy=false;
    enemy_type="none";
}
