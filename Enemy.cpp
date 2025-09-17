//
// Created by User on 19/04/2025.
//

#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#pragma once

Enemy::Enemy(){
    health=2;
    std::string new_combos[5]={"tsgr","gssr","sgtr","gsTr","gtsr"};
    for (int i=0; i<5; i++){
    	combos[i]=new_combos[i];
    }
    combo_num=5;//number of combos.
    intro_message="A wild enemy appears!\n";
    was_interrupted=false;//if true, leaves enemy open to a free hit.
    was_interrupted_before=false;//implemented because otherwise a single hit would result in a permanent stun-lock.
    name="Enemy";
    interrupt_on_hit=true;
    interrupt_on_parry=true;
}

void Enemy::interrupt(){
    was_interrupted=true;
    std::cout<<"You stunned the enemy!\n";
}

void Enemy::hit(int damage) {
    health-=damage;
    if (health<0) {
        health=0;
    }
    if (interrupt_on_hit&&!was_interrupted_before) {
        interrupt();
    }
}

int Enemy::get_health(){
	return health;
}

void Enemy::print_intro_message(){
	std::cout<<intro_message;
}

bool Enemy::get_interrupt_on_hit(){
    return interrupt_on_hit;
}

bool Enemy::get_interrupt_on_parry(){
    return interrupt_on_parry;
}

std::string Enemy::get_combo(){
    int x=time(0);
    srand(x);
    std::string out;
    if (was_interrupted) {
        out="r";
        was_interrupted=false;
        was_interrupted_before=true;
    }else{//randomly selects a combo
        out=combos[std::rand()%combo_num];
        was_interrupted_before=false;
    }
    return out;
}

std::string Enemy::get_name() {
    return name;
}

Enemy::~Enemy(){}

Small_goblin::Small_goblin() {
    intro_message="You hear a sound. The creaking of rock on rock, and a mischievous laugh. A small goblin attacks you!\n";
    name="Small Goblin";
    std::string new_combos[5]={"tsgr","gssr","sgtr","gsTr","gtsr"};
    for (int i=0; i<5; i++){
        combos[i]=new_combos[i];
    }
}


Large_goblin::Large_goblin() {
    intro_message="\"Har har! You've fallen into my trap!\" A large goblin prepares to attack!\n";
    name="Large Goblin";
    health=4;
    std::string new_combos[5]={"Tstgr","tTgsr","sSttr","gsTtr","gTsgr"};
    for (int i=0; i<5; i++){
        combos[i]=new_combos[i];
    }
}


Knight::Knight() {
    name="Knight";
    intro_message="\"You may go no further.\" a calm voice says. A Knight in shining armour moves to attack you.\n";
    health=8;
    std::string new_combos[]={"TTstgr","TStTsr","SStsgr","StSTgr","TTTsSr"};
    for (int i=0; i<5; i++){
        combos[i]=new_combos[i];
    }
    interrupt_on_hit=false;
}

Golem::Golem() {//final boss
    name="Golem";
    intro_message="For a moment nothing moves. Then, a statue comes to life.\nIt's a Golem! This is a powerful foe. Be careful!\n";
    health=20;
    std::string new_combos[]={"sstTsgr","ttsgstr","stsTSgr","tstgTgr","sttStgr","tsstgTr","ssstTsr","tttSSgr"};
    combo_num=5;
    for (int i=0; i<8; i++){
        combos[i]=new_combos[i];
    }
    interrupt_on_hit=false;
    interrupt_on_parry=false;
}