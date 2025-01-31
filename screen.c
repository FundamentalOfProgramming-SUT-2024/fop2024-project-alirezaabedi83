#include "game.h"
#include <ncurses.h>
void screen_setup(){
    // int MAX_WIDTH=188;
    // int MAX_HEIGHT=56;
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    srand(time(NULL));
}

int print_game_info(Level* level){
    mvprintw(55, 0, "    Level: %d",level->level);
    printw("    SCORE: %d",level->user->score);
    printw("    HEALTH: %d(%d)",level->user->health,level->user->max_health);
    printw("    ATTACK: %d",level->user->attack);
    printw("    EXPRIENCE: %d\t",level->user->exprience);
    return 1;

}

void print_inventory(Player*player){
        mvprintw(54, 0, "    Inventory: ");
        for (int i=0; i<player->item_count; i++) {
            printw("%s", player->items[i]->string);
        
        }



}