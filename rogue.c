#include "game.h"

void render(Game* game){
    clear();
    draw_level(game->levels[game->curent_level-1]);
    print_game_info(game->levels[game->curent_level-1]);
}
int game_loop(Game* game){
    int choice='\0';
    
    Level*level;
    Position* new_pos;
    if (game->curent_level==0) {
        game->levels[game->curent_level]=level_setup(1);
        game->curent_level++;
    }
    level=game->levels[game->curent_level-1];

    while (1) {

        if (choice=='q') {
            break;
        
        }
        if (choice=='i') {
            print_inventory(level->user);
        }
        else{
            new_pos=handle_input(choice,level->user);
            check_next(new_pos, level);
            move_monster(level);

            render(game);
                    
            if (level->user->health <=0) {
                game->curent_level=0;
                return -1;
            
            }
        }
        choice=getch();
    }
}