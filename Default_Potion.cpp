//
// Created by User on 24/04/2025.
//

#include "Default_Potion.h"
#include "Misc_functions.cpp"
#pragma once

void Default_Potion::effect() {
    std::cout<<"You have "<<player_stats.get_health()<<" health remaining.\n";//this should never be called.
}

void Default_Potion::apply_effect() {
    if (num_carried==0) {
        std::cout<<"You have no "<<name<<"s.\n";
    }else {
        num_carried--;
        effect();
    }
}
void Default_Potion::pick_up(int num_picked_up) {
    num_carried=Misc_functions::min(max_capacity,num_carried+num_picked_up);
    std::cout<<"You picked up a "<<name<<". You now have "<<num_carried<<" out of a maximum capacity of "<<max_capacity<<".\n";
}
int Default_Potion::get_num_carried() {
    return num_carried;
}
void Default_Potion::describe() {
    std::cout<<description;
}
Default_Potion::Default_Potion() {
    name="Default potion";
    description="Default potion. Does nothing.\n";
}

void Invincibility_Potion::effect(){
    player_stats.set_invincible();
    std::cout<<"You have gained invincibility!\n";
}

Invincibility_Potion::Invincibility_Potion() {
    description="You are take no damage during your next fight. Wears off after the fight.\n";
    name="Invincibility potion";
}


void Health_Potion::effect(){
    player_stats.replenish_health();
    std::cout<<"You have healed up to max health! You now have "<<player_stats.get_health()<<" health!\n";
}
Health_Potion::Health_Potion() {
    description="Heals you up to max health.\n";
    name="Health potion";
}

void Double_Damage_Potion::effect() {
    player_stats.set_damage(2);
}

Double_Damage_Potion::Double_Damage_Potion() {
    description="Deal double damage in your next encounter.\n";
    name="Double Damage Potion";
}
