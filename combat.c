#include "game.h"
#include <ncurses.h>

int combat(Player* player , Monster* monster , int command){
    if (command==1) {
        mvprintw(0, 0,"you hit the %c %d.",monster->symbol,player->attack );
        getch();
        
        monster->health = monster->health - player->attack;
        if (monster->health > 0) {
            mvprintw(0, 0,"monster %c hits you %d.",monster->symbol,monster->attack );
            getch();
            player->health= player->health - monster->attack;
        
        }
        else {
            mvprintw(0, 0,"you killed the %c and get wxprienced.",monster->symbol );
            getch();
            kill_monster(monster);
            player->exprience++;
        }
    }
    else {
        mvprintw(0, 0,"monster %c hits you %d.",monster->symbol,monster->attack );
        getch();
        player->health = player->health - monster->attack;
        
        if (player->health > 0) {
            mvprintw(0, 0,"you hit the %c %d.",monster->symbol,player->attack );
            getch();
            monster->health= monster->health - player->attack;
            
        
        }
    
    }
    return 1;
}