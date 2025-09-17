//
// Created by User on 24/04/2025.
//

#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
private:
    bool perma_invincible=false;//cheat
    int base_damage=1;//cheat: double damage
    int starting_health=5;//cheat
    std::string difficulty="medium";
    bool heal_on_leave_room=true;
    int enemy_damage=1;
public:
    bool get_perma_invincible();
    void set_perma_invincible(bool setto);

    int get_base_damage();
    void set_base_damage(int setto);

    int get_starting_health();
    void set_starting_health(int setto);

    bool get_heal_on_leave_room();
    int get_enemy_damage();

    void set_difficulty(std::string setto);
    std::string get_difficulty();

    int health_on_current_difficulty();
};



#endif //SETTINGS_H
