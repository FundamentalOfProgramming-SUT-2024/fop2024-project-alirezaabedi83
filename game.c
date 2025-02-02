#include "game.h"
#include <ncurses.h>

void menu_loop(){
    int choice , choice2;
    char*username=(char*)malloc(sizeof(char)*50);
    char *choices[] = {
        "LogIn",
        "SignUp",
        "guest",
        "Exit",
    };
    char *choices2[] = {
        "New Game",
        "Continue Previous Game",
        "Scoreboard",
        "Settings",
        "Profile",
        "Back to Main Menu"
    };

    Game game;
    game.curent_level=0;

    mvprintw(1, 1, "WELCOME!");

    while (1) {
        choice=main_menu(4, choices);
        switch (choice) {
            case 0:
                //if login sucsses
                if(login()){
                    while(1){
                        choice2=main_menu(6, choices2);
                        if (choice2==5) {
                            break;
                        }
                        switch (choice2) {
                            case 0:
                                mvprintw(10, 1, "Starting a new game...");
                                refresh();
                                getch();
                                clear();
                                game.curent_level=0;
                                game_loop(&game);
                                break;
                            case 1:
                                mvprintw(10, 1, "Continuing previous game...");
                                refresh();
                                getch();
                                clear();
                                game_loop(&game);
                                break;
                            case 2:
                            display_scoreboard(user_name);
                            clear();
                            break;
                            case 3:
                            settings_menu();
                            break;
                            case 4:
                            break;
                            case 5:
                            break;
                        
                        }
                    
                    
                }}
                refresh();
                getch();
                clear();
                break;
                
            case 1: 
                //if signup sucsses
                if(sign_up()){
                    while (1) {
                        choice2=main_menu(6, choices2);
                        if (choice2==5) {
                            break;
                        }
                        switch (choice2) {
                            case 0:
                                mvprintw(10, 1, "Starting a new game...");
                                refresh();
                                getch();
                                clear();
                                game.curent_level=0;
                                game_loop(&game);
                                break;
                            case 1:
                                mvprintw(10, 1, "Continuing previous game...");
                                refresh();
                                getch();
                                clear();
                                game_loop(&game);
                                break;
                            case 2:
                            display_scoreboard(user_name);
                            clear();
                            break;
                            case 3:
                            settings_menu();
                            break;
                            case 4:
                            break;
                            case 5:
                            break;
                        
                        }
                }
                }
                refresh();
                getch();
                clear();
                break;
            case 2:
                game_loop(&game);  
                break;  
            case 3:
                save_scoreboard(user_name, scoring) ;
                getch();
                return;
                break;
        
        }
    
    }
}

Mix_Music *current_music = NULL;

int scoring=0;
char user_name[50]="guest";
int current_floor=1;
int main(){
    setlocale(LC_ALL, "");
      
    screen_setup(); 
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        mvprintw(1, 1, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        getch();
        return 1;
    }

    menu_loop();
    Mix_CloseAudio();   
    endwin();
    return 0;
}
