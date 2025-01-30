#include "game.h"
#include <ncurses.h>
void screen_setup(){
    initscr();
    noecho();
    refresh();
    srand(time(NULL));
}

int print_game_info(Level* level){
    mvprintw(55, 0, "\tLevel: %d",level->level);
    printw("\tSCORE: %d",level->user->score);
    printw("\tHEALTH: %d(%d)",level->user->health,level->user->max_health);
    printw("\tATTACK: %d",level->user->attack);
    printw("\tEXPRIENCE: %d\t",level->user->exprience);
    return 1;

}