//
// Created by User on 19/04/2025.
//

#include <iostream>
#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
protected:
    int health;
    std::string combos[8];//max number of combos. will work with fewer, but not more. 8 is the num for the final boss
    int combo_num;
    std::string intro_message;
    bool was_interrupted;//if true, leaves enemy open to a free hit.
    bool was_interrupted_before;//implemented because otherwise a single hit would result in a permanent stun-lock.
    std::string name;
    bool interrupt_on_hit;//enemy ends its combo and presents vulnerability if damaged
    bool interrupt_on_parry;//ditto, but for parrying
public:
    void interrupt();
    void hit(int damage);
    int get_health();
    void print_intro_message();
    std::string get_name();
    bool get_interrupt_on_hit();
    bool get_interrupt_on_parry();
    std::string get_combo();
    Enemy();
    ~Enemy();
};

class Small_goblin: public Enemy {
public:
    Small_goblin();
};

class Large_goblin: public Enemy {
public:
    Large_goblin();
};

class Knight: public Enemy {
public:
    Knight();
};

class Golem: public Enemy {
public:
    Golem();
};

#endif //ENEMY_H
