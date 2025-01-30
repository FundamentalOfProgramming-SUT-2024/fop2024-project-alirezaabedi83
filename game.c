#include "game.h"
#include <ncurses.h>

int main(){
    
    int choice;
    // int MAX_WIDTH=188;
    // int MAX_HEIGHT=56;
    
    Level*level;
    Position* new_pos;
    screen_setup();
    level=level_setup(1);

    print_game_info(level);

    while ((choice=getch())!='q') {
        print_game_info(level);
        new_pos=handle_input(choice,level->user);
        check_next(new_pos, level);
        move_monster(level);
        move(level->user->position->y, level->user->position->x);
        
    }
    
    endwin();
    return 0;
}
