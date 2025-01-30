#include "game.h"

int combat(Player* player , Monster* monster , int command){
    if (command==1) {
        monster->health = monster->health - player->attack;
        if (monster->health > 0) {
            player->health= player->health - monster->attack;
        
        }
        else {
            kill_monster(monster);
            player->exprience++;
        }
    }
    else {
        player->health = player->health - monster->attack;
        if (player->health > 0) {
            monster->health= monster->health - player->attack;
        
        }
    
    }
    return 1;
}