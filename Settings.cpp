//
// Created by User on 24/04/2025.
//

#include "Settings.h"
#include <iostream>
#pragma once


bool Settings::get_perma_invincible() {
    return perma_invincible;
}
void Settings::set_perma_invincible(bool setto) {
    perma_invincible=setto;
}
int Settings::get_base_damage() {
    return base_damage;
}
void Settings::set_base_damage(int setto) {
    base_damage=setto;
    std::cout<<"poob";
}
int Settings::get_starting_health() {
    return starting_health;
}
void Settings::set_starting_health(int setto) {
    starting_health=setto;
}


bool Settings::get_heal_on_leave_room() {
    return heal_on_leave_room;
}


int Settings::get_enemy_damage() {
    return enemy_damage;
}


void Settings::set_difficulty(std::string setto) {
    if (setto=="easy") {
        starting_health=10;
        heal_on_leave_room=true;
        enemy_damage=1;
        perma_invincible=false;
        difficulty=setto;
    }else if (setto=="medium") {
        starting_health=5;
        heal_on_leave_room=true;
        enemy_damage=1;
        perma_invincible=false;
        difficulty=setto;
    }else if (setto=="hard") {
        starting_health=5;
        heal_on_leave_room=false;
        enemy_damage=2;
        perma_invincible=false;
        difficulty=setto;
    }else {
        std::cout<<"Error: invalid difficulty.\n";
    }
}

std::string Settings::get_difficulty() {
    return difficulty;
}

int Settings::health_on_current_difficulty() {
    int out=0;
    if (difficulty=="easy") {
        out=10;
    }else if (difficulty=="medium"||difficulty=="hard") {
        out=5;
    }
    return out;
}