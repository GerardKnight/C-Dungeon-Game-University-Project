#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Misc_functions.cpp"
#include "Player_stats.cpp"
#include "Enemy.cpp"
#include "Combat.cpp"
#include "Settings.cpp"
#include "Default_Potion.cpp"
#include "Room.cpp"
#include "Floor.cpp"



Settings settings;

Player_stats player_stats;

Default_Potion default_potion;
Invincibility_Potion invincibility_potion;
Health_Potion health_potion;
Double_Damage_Potion double_damage_potion;

void opening_menu() {//runs before the game proper
    bool abu=true;
    int state=0;
    std::cout<<"Welcome to Dungeon Game Supreme 2025.\n";
    std::string selection;
    std::string pcvn="Please choose a valid number.\n";
    std::string cheats_selection_nums[]={"1","2","3","4"};
    while (abu) {
        switch (state) {
            case 0://main menu
                std::cout<<"1. Begin game.\n2. Difficulty Level.\n--->";
                std::cin>>selection;
                if (selection=="1") {
                    std::cout<<"Welcome to the horror!\n";
                    abu=false;
                }else if (selection=="2") {
                    state=1;
                }else if (selection=="cheats") {//done like this to hide it
                    state=2;
                }else {
                    std::cout<<pcvn;
                }
            break;
            case 1://difficulty
                std::cout<<"Please choose your level of difficulty.\n";
                std::cout<<"Current difficulty: "<<settings.get_difficulty()<<".\n";
                std::cout<<"1. Easy.\n2. Medium.\n3. Hard.\n4. Back.\n--->";
                std::cin>>selection;
                if (selection=="1") {
                    std::cout<<"Difficulty: Easy\n";
                    settings.set_difficulty("easy");
                }else if (selection=="2") {
                    std::cout<<"Difficulty: Medium\n";
                    settings.set_difficulty("medium");
                }else if (selection=="3") {
                    std::cout<<"Difficulty: Hard\n";
                    settings.set_difficulty("hard");
                }else if (selection=="4") {
                    state=0;
                }else {
                    std::cout<<pcvn;
                }
            break;
            case 2://cheats
                std::cout<<"Note: all cheats reset on difficulty change.\n";
                std::cout<<"Cheats Menu:\n";
                std::cout<<"1. Invincibility.\n2. Double damage.\n3. Double health.\n4. Back.\n--->";
                std::cin>>selection;
                if (selection=="4") {
                    state=0;
                }else if (Misc_functions::is_in(selection,cheats_selection_nums,4)) {
                    state=3;
                }else {
                    std::cout<<pcvn;
                }
            break;
            case 3://activate cheats
                if (selection=="1") {
                    if (settings.get_perma_invincible()) {
                        std::cout<<"This cheat is currently active.\n";
                    }else {
                        std::cout<<"This cheat is not currently active.\n";
                    }
                    std::cout<<"Activate this cheat?\n1. Yes.\n2. No.\n--->";
                    std::cin>>selection;
                    if (selection=="1") {
                        settings.set_perma_invincible(true);
                        std::cout<<"You are now invincible.\n";
                    }else if (selection=="2") {
                        settings.set_perma_invincible(false);
                        std::cout<<"You are no longer invincible.\n";
                    }
                }else if (selection=="2") {
                    if (settings.get_base_damage()==2) {
                        std::cout<<"This cheat is currently active.\n";
                    }else {
                        std::cout<<"This cheat is not currently active.\n";
                    }
                    std::cout<<"Activate this cheat?\n1. Yes.\n2. No.\n--->";
                    std::cin>>selection;
                    if (selection=="1") {
                        settings.set_base_damage(2);
                        std::cout<<"You now deal double damage.\n";
                    }else if (selection=="2") {
                        settings.set_base_damage(1);
                        std::cout<<"You are no longer deal double damage.\n";
                    }
                }else if (selection=="3") {
                    if (settings.get_starting_health()==settings.health_on_current_difficulty()*2) {
                        std::cout<<"This cheat is currently active.\n";
                    }else {
                        std::cout<<"This cheat is not currently active.\n";
                    }
                    std::cout<<"Activate this cheat?\n1. Yes.\n2. No.\n--->";
                    std::cin>>selection;
                    if (selection=="1") {
                        settings.set_starting_health(settings.health_on_current_difficulty()*2);
                        std::cout<<"You now have double health.\n";
                    }else if (selection=="2") {
                        settings.set_base_damage(settings.health_on_current_difficulty());
                        std::cout<<"You are no longer have double health.\n";
                    }
                }
            state=2;
            break;
        }
    }
    player_stats.set_max_health(settings.get_starting_health());
    player_stats.replenish_health();
    player_stats.update_cheats();
}

int run_floor(int level) {//done in function to delete old objects.
    Floor floor=Floor(level);
    return floor.floor_main();
}


int main() {
    std::string name;
    std::cout<<"Please enter your name.\n--->";
    std::cin>>name;
    std::cout<<"Welcome, "<<name<<"!\n";
    settings.set_difficulty("medium");
    opening_menu();
    bool won=true;
    for (int i=1; i<4; i+=2) {
        if (run_floor(i)==1) {
            won=false;
            break;
        }else {
            player_stats.floor_reward(i);
        }
    }
    if (won) {
        std::cout<<"You have found the treasure!\n";
        std::cout<<"Congratulations on beating the game!\n";
        std::cout<<"Credits:\nEverything-Gerard\n";
    }
    return 0;
}