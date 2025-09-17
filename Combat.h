//
// Created by User on 19/04/2025.
//

#ifndef COMBAT_H
#define COMBAT_H
#pragma once
#include <iostream>



class Combat {
private:
    static int combat_char_to_int(char in);
    static int static_combat_combo_selection();
    template <typename Enemy_Type>
    static void static_combat_draw(Enemy_Type& enemy);
    template <typename Enemy_Type>
    static void static_combat_hit(Enemy_Type& enemy);
    template <typename Enemy_Type>
    static void static_combat_damage(Enemy_Type& enemy, int damage_type=0);
    template <typename Enemy_Type>
    static void static_combat_nothing(Enemy_Type& enemy, bool is_parry=false);
    template <typename Enemy_Type>
    static bool combat_outcome(int enemy_action, int player_action, Enemy_Type& enemy);
    template <typename Enemy_Type>
    static void static_combat_combo(std::string combo, Enemy_Type& enemy);
public:
    template <typename Enemy_Type>
    static void static_combat(Enemy_Type& enemy);
};



#endif //COMBAT_H
