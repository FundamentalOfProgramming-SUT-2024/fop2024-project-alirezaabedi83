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
                clear();
                const char *game_over[] = {
                " GGG   AAAAA  M   M  EEEEE    OOO   V   V  EEEEE  RRRR  ",
                "G   G  A   A  MM MM  E       O   O  V   V  E      R   R ",
                "G      AAAAA  M M M  EEEE    O   O  V   V  EEEE   RRRR  ",
                "G   G  A   A  M   M  E       O   O  V   V  E      R  R  ",
                " GGG   A   A  M   M  EEEEE    OOO    VVV   EEEEE  R   R "
                };

                for(int i = 0; i < 5; i++) {
                    mvprintw(25+i,70,"%s\n", game_over[i]);
                }

                refresh();
                getch();
                clear();
                save_scoreboard(user_name, scoring);
                endwin();
                exit(0);
                return -1;
            
            }
        }
        choice=getch();
    }
}