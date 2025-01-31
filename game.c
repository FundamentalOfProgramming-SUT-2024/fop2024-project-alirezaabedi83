#include "game.h"

void menu_loop(){
    int choice;
    char*choices[]={"start game","end game"};

    Game game;
    game.curent_level=0;

    while (1) {
        choice=main_menu(2, choices);
        switch (choice) {
            case START_GAME:
            game_loop(&game);
            clear();
            break;
            case QUIT_GAME:
            return;
            break;
        
        }
    
    }
}

int main(){
      
    screen_setup(); 
    menu_loop();   
    endwin();
    return 0;
}
