//
// Created by User on 19/04/2025.
//

#include "Player_stats.h"
#include <iostream>
#pragma once

Player_stats::Player_stats(){
    max_health=settings.get_starting_health();
    health=max_health;
    base_damage=settings.get_base_damage();
    damage_multiplier=1;
    invincible=settings.get_perma_invincible();
}

void Player_stats::hit(int damage){//player takes damage
    if (invincible){
        std::cout<<"However, you are invincible and take no damage.\n";
    }else{
        health-=damage;
        if (health<=0){
            health=0;
        }
    }
}

void Player_stats::heal(int health_bonus){
    health+=health_bonus;
    if (health>max_health){
        health=max_health;
    }
}

void Player_stats::replenish_health(){
    health=max_health;
}

int Player_stats::get_health(){
    return health;
}

int Player_stats::get_max_health(){
    return max_health;
}

int Player_stats::get_damage_multiplier(){
    return damage_multiplier*base_damage;
}

void Player_stats::set_invincible(){
    invincible=true;
}

void Player_stats::set_damage(int new_mult) {
    damage_multiplier=new_mult;
}

void Player_stats::clear_effects(){
    invincible=settings.get_perma_invincible();
    set_damage(1);
    std::cout<<"All potion effects have cleared.\n";
}

bool Player_stats::has_effects(){
    return invincible||(damage_multiplier!=1);
}

bool Player_stats::is_ded() {
    return health==0;
}

void Player_stats::set_max_health(int setto) {
    max_health=setto;
}

void Player_stats::floor_reward(int n) {//buffs the player upon entering the next layer
    switch (n) {
        case 1:
            std::cout<<"As a reward for completing this level, your max health has increased!\n";
            max_health+=settings.get_starting_health();
            heal(settings.get_starting_health());
            std::cout<<"You now have "<<get_health()<<" health!\n";
        break;
        case 2:
            std::cout<<"As a reward for completing this level, you max health and damage output have increased!\n";
            max_health+=settings.get_starting_health();
            base_damage*=2;
            heal(settings.get_starting_health());
            std::cout<<"You now have "<<get_health()<<" health and do "<<get_damage_multiplier()<<" damage!\n";
            std::cout<<"This is the final floor. The treasure is near.\n";
        break;
    }
}

void Player_stats::update_cheats() {
    base_damage=settings.get_base_damage();
    invincible=settings.get_perma_invincible();
}

void Player_stats::set_name(std::string setto) {
    name=setto;
}