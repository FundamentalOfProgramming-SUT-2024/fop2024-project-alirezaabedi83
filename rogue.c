#include "game.h"
#include <stdlib.h>

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
            print_weopon(level->user);
            mvprintw(0, 0, "wich one do you want to use?");
            char str[10];
            getstr(str);
            int apply_time=0;
            if (strcmp(str, "sword")==0) {
                delete_weopon(level->user, "sword");
                level->user->attack=10;
                apply_time=0;
            }
            else if (strcmp(str, "dagger")==0) {
                delete_weopon(level->user, "dagger");
                level->user->attack=12;
                apply_time=1;
            }
            else if (strcmp(str, "arrow")==0) {
                delete_weopon(level->user, "arrow");
                level->user->attack=6;
                apply_time=1;
            }
            else if (strcmp(str, "wand")==0) {
                delete_weopon(level->user, "wand");
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

        if (choice=='o') {
            print_potion(level->user);
            mvprintw(0, 0, "wich one do you want to use?");
            int attorhealth=0;
            char str[10];
            getstr(str);
            if (strcmp(str, "health")==0) {
                delete_potion(level->user, "health");
                attorhealth=1;
                health+=5;
            }
            else if (strcmp(str, "attack")==0) {
                delete_potion(level->user, "attack");
                level->user->attack*=2;
                attorhealth=0;
            }
            else if (strcmp(str, "speed")==0) {
                delete_potion(level->user, "speed");
                level->user->attack=6;
            }
            else {
                
            }
            if (attorhealth==0) {
                pthread_t reset_thread;
                pthread_create(&reset_thread, NULL, reset_attack, (void*)level->user);
                pthread_detach(reset_thread);
            }
            else {
                pthread_t reset_thread;
                pthread_create(&reset_thread, NULL, reset_health, (void*)level->user);
                pthread_detach(reset_thread);
            
            }
                
            
            

        }

        if (choice=='f') {
            print_food(level->user);
            mvprintw(0, 0, "wich one do you want to use?");
            char str[10];
            getstr(str);
            if (strcmp(str, "normal")==0) {
                delete_food(level->user, "normal");
                if (rand()%2==0) {
                    //good
                    health+=5;
                    //fassed
                }else {
                    health-=5;
                }
                
            }
            else if (strcmp(str, "magic")==0) {
                delete_potion(level->user, "magic");
                level->user->attack+=2;
                health+=3;
            }
            else if (strcmp(str, "aala")==0) {
                delete_potion(level->user, "aala");
                level->user->attack+=3;
            }
            else {
                
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