//
// Created by User on 19/04/2025.
//

#include "Combat.h"
#include "Misc_functions.cpp"
#include "Player_stats.cpp"
#pragma once

extern Player_stats player_stats;

int Combat::combat_char_to_int(char in) {//for use in switch-case statemnts
    int out;
    if (in=='t') {//slash
        out=1;
    }else if (in=='s') {//thrust
        out=2;
    }else if (in=='T') {//slash feint
        out=3;
    }else if (in=='S') {//thrust feint
        out=4;
    }else if (in=='g') {//guard
        out=5;
    }else if (in=='r') {//rests. open to attack
        out=6;
    }else {
        std::cout<<"Error: Invalid char passed in.\n";
        out=0;
    }
    return out;
}


int Combat::static_combat_combo_selection() {//player selects what to do
    std::cout<<"What action do you take?\n1. Thrust.\n2. Slash.\n3. Parry.\n4. Guard.\n";
    bool abu=true;
    std::string out="0";//originally this was an int, but it needs to be a string to avoid any strange behaviour with cin. The code will not return an error or otherwise break for any input.
    std::string nums[]={"1","2","3","4"};
    while (abu) {
        if (out=="0") {
            std::cout<<"--->";
            std::cin>>out;
        }else if (Misc_functions::is_in(out, nums,4)) {
            abu=false;
        }else {
            std::cout<<"Please write a number, 1, 2, 3 or 4.\n";
            out="0";
        }
    }
    return (int) out[0]-49;//recasts to an int. -49 to return the value represented, rather than the ascii value.
}

template <typename Enemy_Type>//done so any enemy type can be used
void Combat::static_combat_draw(Enemy_Type& enemy) {//was easier to pass the enemy into each function, by reference, to keep track of which enemy is being damaged.
    enemy.hit(player_stats.get_damage_multiplier());
    std::cout<<"You and the "<<enemy.get_name()<<" hit each-other! You deal "<<player_stats.get_damage_multiplier()<<" damage, while they deal "<<settings.get_enemy_damage()<<" damage!\n";
    player_stats.hit(settings.get_enemy_damage());
}

template <typename Enemy_Type>
void Combat::static_combat_hit(Enemy_Type& enemy) {
    enemy.hit(player_stats.get_damage_multiplier());
    std::cout<<"You hit the "<<enemy.get_name()<<" for 1 damage!\n";
}

template <typename Enemy_Type>
void Combat::static_combat_damage(Enemy_Type& enemy, int damage_type) {
    switch (damage_type) {
        case 0:
            std::cout<<"The "<<enemy.get_name()<<" hit you for "<<settings.get_enemy_damage()<<" damage!\n";
        break;
        case 1:
            std::cout<<"That was a feint! You left an opening. The "<<enemy.get_name()<<" hits you for "<<settings.get_enemy_damage()<<" damage.\n";
        break;
        case 2:
            std::cout<<"You attacked the "<<enemy.get_name()<<" while it was defending! It strikes back for "<<settings.get_enemy_damage()<<" damage.\n";
        break;
    }
    player_stats.hit(settings.get_enemy_damage());
}

template <typename Enemy_Type>
void Combat::static_combat_nothing(Enemy_Type& enemy, bool is_parry) {
    if (is_parry) {
        std::cout<<"You successfully parried the "<<enemy.get_name()<<"'s attack.\n";
        if (enemy.get_interrupt_on_parry()) {
            enemy.interrupt();
        }
    }else {
        std::cout<<"Neither you nor the "<<enemy.get_name()<<" score a hit.\n";
    }
}

template <typename Enemy_Type>
bool Combat::combat_outcome(int enemy_action, int player_action, Enemy_Type& enemy) {//bool rather than void to break enemy out of combos
    int hit_table[][4]={{0,0,0,0},{0,1,6,1},{0,1,6,5},{3,0,3,5},{3,0,3,5},{4,4,5,5},{2,2,5,5}};//The results of various actions in combat. See report for further details.
    int outcome=hit_table[enemy_action][player_action];
    bool out=false;
    switch (outcome) {
        case 0:
            static_combat_draw(enemy);
        break;
        case 1:
            static_combat_damage(enemy);
        break;
        case 2:
            static_combat_hit(enemy);
        if (enemy.get_interrupt_on_hit()) {
            out=true;
        }
        break;
        case 3:
            static_combat_damage(enemy, 1);
        break;
        case 4:
            static_combat_damage(enemy, 2);
        break;
        case 5:
            static_combat_nothing(enemy);
        break;
        case 6:
            static_combat_nothing(enemy,true);
        if (enemy.get_interrupt_on_parry()) {
            out=true;
        }
        break;
    }
    return out;
}

template <typename Enemy_Type>
void Combat::static_combat_combo(std::string combo, Enemy_Type& enemy) {
    int enemy_action;
    int player_action;
    std::string combat_dialogue[]={"The enemy thrusts.\n","The enemy slashes.\n","The enemy guards.\n","The enemy rests.\n"};
    for (int i=0; i<combo.length(); i++) {
        std::cout<<"You have "<<player_stats.get_health()<<" health remaining. The "<<enemy.get_name()<<" has "<<enemy.get_health()<<" health remaining.\n";
        enemy_action=combat_char_to_int(combo[i]);
        switch (enemy_action) {
            case 1:
                std::cout<<combat_dialogue[0];
            break;
            case 2:
                std::cout<<combat_dialogue[1];
            break;
            case 3:
                std::cout<<combat_dialogue[0];
            break;
            case 4:
                std::cout<<combat_dialogue[1];
            break;
            case 5:
                std::cout<<combat_dialogue[2];
            break;
            case 6:
                std::cout<<combat_dialogue[3];
            break;
        }
        player_action=static_combat_combo_selection();
        if (combat_outcome(enemy_action,player_action,enemy)) {//breaks loop if enemy is stunned
            break;
        }
        if (enemy.get_health()==0) {//these end the combat as soon as one side or the other has died
            break;
        }
        if (player_stats.is_ded()) {
            break;
        }
    }
}

template <typename Enemy_Type>
void Combat::static_combat(Enemy_Type& enemy) {//the only function to be called outside of this class
    enemy.print_intro_message();
    std::string combo;
    bool in_combat=true;
    while (in_combat) {
        if (player_stats.get_health()==0) {
            in_combat=false;
        }else if (enemy.get_health()==0) {
            std::cout<<"You have defeated the "<<enemy.get_name()<<"!\n";
            in_combat=false;
        }else {
            combo=enemy.get_combo();
            static_combat_combo(combo,enemy);
        }
    }
}