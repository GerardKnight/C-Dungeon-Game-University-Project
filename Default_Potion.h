//
// Created by User on 24/04/2025.
//

#ifndef DEFAULT_POTION_H
#include "Player_stats.cpp"
#define DEFAULT_POTION_H
#include <iostream>
#pragma once



class Default_Potion {
protected:
    int max_capacity=3;
    int num_carried=0;
    std::string name;
    std::string description;
    virtual void effect();//overridden by each proper potion
public:
    void apply_effect();
    void pick_up(int num_picked_up);
    int get_num_carried();
    void describe();
    Default_Potion();
};

class Invincibility_Potion: public Default_Potion {
protected:
    void effect() override;
public:
    Invincibility_Potion();
};

class Health_Potion: public Default_Potion {
protected:
    void effect() override;
public:
    Health_Potion();
};

class Double_Damage_Potion: public Default_Potion {
protected:
    void effect() override;
public:
    Double_Damage_Potion();
};
#endif //DEFAULT_POTION_H
