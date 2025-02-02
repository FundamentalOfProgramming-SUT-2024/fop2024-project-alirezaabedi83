#include "game.h"
#include <ncurses.h>
#include <string.h>

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
            mvprintw(0, 0, "wich one do you want to use?");
            char str[10];
            getstr(str);
            int apply_time=0;
            if (strcmp(str, "sword")==0) {
                delete_item(level->user, "sword");
                level->user->attack=10;
                apply_time=0;
            }
            else if (strcmp(str, "dagger")==0) {
                delete_item(level->user, "dagger");
                level->user->attack=12;
                apply_time=1;
            }
            else if (strcmp(str, "arrow")==0) {
                delete_item(level->user, "arrow");
                level->user->attack=6;
                apply_time=1;
            }
            else if (strcmp(str, "wand")==0) {
                delete_item(level->user, "wand");
                level->user->attack=15;
                apply_time=1;
            }
            else {
                level->user->attack=5;
            }
            if (apply_time==1) {
                pthread_t reset_thread;
                pthread_create(&reset_thread, NULL, reset_attack, (void*)level->user);
                pthread_detach(reset_thread);
            }
            

        }
        else{
            new_pos=handle_input(choice,level->user);
            check_next(new_pos, level);
            
            move_monster(level);

            render(game);
                    
            if (health <=0) {
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
                save_scoreboard(user_name, score , gold);
                endwin();
                exit(0);
                return -1;
            
            }
        }
        choice=getch();
    }
}