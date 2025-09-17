//
// Created by User on 25/04/2025.
//

#include "Floor.h"
#include <iostream>
#include "Enemy.cpp"
#include "Combat.cpp"
#pragma once


void Floor::generate_rooms() {//randomly generates distribution of items+enemies.
    size=4+floor_num;//done outside of constructor to make it smaller
    //key items
    int time_seed=time(0);
    srand(time_seed);
    trapdoor_cords[0]=rand()%size;
    trapdoor_cords[1]=size-1;
    key_cords[0]=rand()%size;
    key_cords[1]=rand()%(size-2)+1;
    entrance_cords[0]=rand()%size;
    entrance_cords[1]=0;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            enemies[i][j]="none";
            items[i][j]="none";
        }
    }
    //enemies.
    int num;
    for (int j=1; j<size-1; j++) {
        for (int i=0; i<size; i++) {
            if (rand()%5==0) {
                switch (floor_num) {
                    case 1:
                        enemies[i][j]="Small Goblin";
                    break;
                    case 2:
                        enemies[i][j]="Small Goblin";
                    break;
                    case 3:
                        enemies[i][j]="Large Goblin";
                    break;
                }
            }
        }
    }
    switch (floor_num) {
        case 1:
            enemies[trapdoor_cords[0]][trapdoor_cords[1]]="Large Goblin";
        break;
        case 2:
            enemies[trapdoor_cords[0]][trapdoor_cords[1]]="Knight";
        break;
        case 3:
            enemies[trapdoor_cords[0]][trapdoor_cords[1]]="Golem";
        break;
    }
    //items
    for (int i=1; i<size-1; i++) {
        for (int j=0; j<size; j++) {
            if (rand()%(size*2)==0) {//how likely is an item to spawn?
                num=rand()%6;
                if (num==0) {//which item?
                    if (settings.get_difficulty()=="easy") {
                        items[i][j]="Invincibility Potion";
                    }
                }else if (num==1||num==2){
                    items[i][j]="Double Damage Potion";
                }else {
                    items[i][j]="Health Potion";
                }
            }
        }
    }
}

Floor::Floor(int new_floor_num) {
    floor_num=new_floor_num;//what level?
    generate_rooms();
    int cords[]={0,0};//to pass in as an array
    for (int i=0; i<10; i++) {//loops initialise rooms
        cords[0]=i;
        for (int j=0; j<10; j++) {
            cords[1]=j;
            rooms[i][j].init_Room(cords, new_floor_num, enemies[i][j], items[i][j], (Misc_functions::arrs_are_same(cords, trapdoor_cords,2)), (Misc_functions::arrs_are_same(cords, key_cords,2)));
        }
    }
    current_cords[0]=entrance_cords[0];
    current_cords[1]=entrance_cords[1];
}
void Floor::calm() {//done when no enemies are present, either because the enemy is dead, or there never were any.
    std::string item_nums[]={"1","2","3"};//very large function due to menus.
    std::string direction_nums[]={"1","2","3","4","5"};
    std::string directions[]={"north","east","south","west"};
    std::cout<<"There is no movement. All is calm.\n";
    std::cout<<"What would you like to do next?\n";
    std::string pcvn="Please choose a valid number.\n";//easier than writing lots :)
    int state=0;
    bool abu=true;
    std::string selection="0";
    int selection_int;
    while (abu) {
        switch (state) {//main menu when interacting with rooms.
            case 0://selecting
                std::cout<<"1. Check inventory.\n2. Check stats.\n3. Enter next room.\n";
            if (rooms[current_cords[0]][current_cords[1]].get_is_trapdoor_room()) {
                std::cout<<"4. Go through trapdoor.\n";
            }
            std::cout<<"--->";
            std::cin>>selection;
            if (selection=="1") {
                state=1;
            }else if (selection=="2") {
                std::cout<<"You currently have "<<player_stats.get_health()<<" health out of "<<player_stats.get_max_health()<<".\n";
                std::cout<<"You do "<<player_stats.get_damage_multiplier()<<" damage.\n";
                if (player_has_key) {
                    std::cout<<"You have the key to the trapdoor on this floor.\n";
                }else {
                    std::cout<<"You do not have the key to the trapdoor on this floor.\n";
                }
            }else if (selection=="3") {
                state=3;
            }else if (rooms[current_cords[0]][current_cords[1]].get_is_trapdoor_room()&&(selection=="4")){
                state=4;
            }else {
                std::cout<<pcvn;
            }
            break;
            case 1://checking inventory
                std::cout<<"Your inventory. Select what you would like to use.\n";
            std::cout<<"1. Invincibility potion: "<<invincibility_potion.get_num_carried()<<".\n";
            std::cout<<"2. Health potion: "<<health_potion.get_num_carried()<<".\n";
            std::cout<<"3. Double damage potion: "<<double_damage_potion.get_num_carried()<<".\n";
            std::cout<<"4. Back.\n";
            std::cout<<"--->";
            std::cin>>selection;
            if (selection=="4") {
                state=0;
            }else if (Misc_functions::is_in(selection,item_nums,3)){
                state=2;
            }else {
                std::cout<<pcvn;
            }
            break;
            case 2://item description
                if (selection=="1") {
                    invincibility_potion.describe();
                    std::cout<<"Would you like to use it?\n1. Yes.\n2. No.\n--->";
                    std::cin>>selection;
                    if (selection=="1") {
                        invincibility_potion.apply_effect();
                    }
                }else if (selection=="2") {
                    health_potion.describe();
                    std::cout<<"Would you like to use it?\n1. Yes.\n2. No.\n--->";
                    std::cin>>selection;
                    if (selection=="1") {
                        health_potion.apply_effect();
                    }
                }else if (selection=="3") {
                    double_damage_potion.describe();
                    std::cout<<"Would you like to use it?\n1. Yes.\n2. No.\n--->";
                    std::cin>>selection;
                    if (selection=="1") {
                        double_damage_potion.apply_effect();
                    }
                }
            state=1;
            break;
            case 3:
                for (int i=0; i<4; i++) {
                    std::cout<<"The way "<<directions[i]<<" is ";
                    if (rooms[current_cords[0]][current_cords[1]].get_doors_open(i)) {
                        std::cout<<"open.\n";
                    }else {
                        std::cout<<"shut.\n";
                    }
                }
            std::cout<<"You are in room "<<current_cords[0]<<", "<<current_cords[1]<<".\n";
            std::cout<<"Which way would you like to travel?\n";
            std::cout<<"1. North.\n2. East.\n3. South.\n4. West.\n5. Back\n--->";
            std::cin>>selection;
            if (!Misc_functions::is_in(selection, direction_nums,5)) {
                std::cout<<pcvn;
            }else if (selection=="5"){
                state=0;
            }else {
                selection_int=(int) selection[0]-48;
                if (rooms[current_cords[0]][current_cords[1]].get_doors_open(selection_int-1)) {
                    std::cout<<"You go through the door to see what awaits. ";
                    switch (selection_int) {
                        case 1:
                            current_cords[1]+=1;
                        break;
                        case 2:
                            current_cords[0]+=1;
                        break;
                        case 3:
                            current_cords[1]-=1;
                        break;
                        case 4:
                            current_cords[0]-=1;
                        break;
                    }
                    //std::cout<<selection_int;
                    abu=false;
                }else {
                    std::cout<<"You cannot go that way; it is shut.\n";
                }
            }
            break;
            case 4:
                if (player_has_key) {
                    std::cout<<"Going through the trapdoor will take you to the next layer of the dungeon.\n";
                    std::cout<<"Are you sure you want to go through?\n1. Yes\n2. No.\n--->";
                    std::cin>>selection;
                    if (selection=="1") {
                        abu=false;
                        has_left_floor=true;
                    }else if (selection=="2") {
                        state=1;
                    }else {
                        std::cout<<pcvn;
                    }
                }else {
                    std::cout<<"Unfortunately you do not have the key to the trapdoor.\n";
                    state=0;
                }
            break;
        }
    }
}

void Floor::enter_room() {//called upon entering new room
    //combat
    std::cout<<"You are in room "<<current_cords[0]<<", "<<current_cords[1]<<".\n";
    if (rooms[current_cords[0]][current_cords[1]].get_has_enemy()) {
        std::string enemy_type=rooms[current_cords[0]][current_cords[1]].get_enemy_type();
        if (enemy_type=="Small Goblin") {
            Small_goblin enemy;
            Combat::static_combat(enemy);
        }else if (enemy_type=="Large Goblin") {
            Large_goblin enemy;
            Combat::static_combat(enemy);
        }else if (enemy_type=="Knight") {
            Knight enemy;
            Combat::static_combat(enemy);
        }else if (enemy_type=="Golem") {
            Golem enemy;
            Combat::static_combat(enemy);
        }else {
            std::cout<<"Error: invalid/no enemy type.\n";
        }
        if (player_stats.has_effects()) {
            player_stats.clear_effects();
        }
        if (settings.get_heal_on_leave_room()) {
            player_stats.heal(1);
            std::cout<<"You heal by 1 HP. You now have "<<player_stats.get_health()<<" health, out of "<<player_stats.get_max_health()<<"!\n";
        }
    }
    if (player_stats.is_ded()) {
        has_left_floor=true;
        std::cout<<"You have died! For you this is game over!\n";
    }else {
        rooms[current_cords[0]][current_cords[1]].kill_enemy();
        rooms[current_cords[0]][current_cords[1]].take_item();
        if (rooms[current_cords[0]][current_cords[1]].get_has_key()) {
            rooms[current_cords[0]][current_cords[1]].take_key();
            player_has_key=true;
            std::cout<<"You have found the key to the trapdoor to the next floor!\n";
        }
        calm();
    }
}


int Floor::floor_main() {//runs whole floor. int to return if the player has left or died
    std::cout<<"You have dropped into the "<<Misc_functions::st2nd3rd(floor_num)<<" floor.\n";
    while (!has_left_floor) {
        enter_room();
    }
    if (player_stats.is_ded()) {
        return 1;
    }else {
        return 0;
    }
}

