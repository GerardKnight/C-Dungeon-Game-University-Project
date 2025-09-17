//
// Created by User on 19/04/2025.
//

#ifndef PLAYER_STATS_H
#define PLAYER_STATS_H
#pragma once
#include "Settings.cpp"

extern Settings settings;

class Player_stats {
private:
    int max_health;
    int health;
    int base_damage;
    int damage_multiplier;//temporary buff
    bool invincible;//changed in cheats
    std::string name;
public:
    Player_stats();
    void hit(int damage);
    void heal(int health_bonus);
    void replenish_health();
    int get_health();
    int get_max_health();
    void set_max_health(int setto);

    int get_damage_multiplier();
    void set_invincible();
    void set_damage(int new_mult);
    void update_cheats();
    void clear_effects();
    void set_name(std::string setto);

    bool has_effects();
    bool is_ded();
    void floor_reward(int n);
};



#endif //PLAYER_STATS_H
