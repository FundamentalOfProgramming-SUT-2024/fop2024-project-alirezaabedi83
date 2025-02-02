#include "game.h"
#include <ncurses.h>
#include <stdlib.h>

Player*player_setup(){
    Player *new_player;
    new_player=(Player*)malloc(sizeof(Player));
    new_player->position=(Position*)malloc(sizeof(Position));
    new_player->items=(Item**)malloc(sizeof(Item*));

    new_player->attack=5;
    new_player->exprience=0;
    new_player->item_count=0;
    new_player->max_health=100;
    // scoring=0;

    new_player->items[new_player->item_count]=create_mace(5,4);
    new_player->item_count++;

    
    
    return new_player;
}

int place_player(Room** rooms , Player* user){
    user->position->x = rooms[0]->position.x + 1;
    user->position->y = rooms[0]->position.y + 1;
}


Position* handle_input(int choice,Player*user){
    Position* new_pos=(Position*)malloc(sizeof(Position));
    switch (choice) {
        case 'j'://UP
        new_pos->y=user->position->y-1;
        new_pos->x=user->position->x;
        break;
        case 'k'://DOWN
        new_pos->y=user->position->y+1;
        new_pos->x=user->position->x;
        break;
        case 'l'://RIGHT
        new_pos->y=user->position->y;
        new_pos->x=user->position->x+1;
        break;
        case 'h'://LEFT
        new_pos->y=user->position->y;
        new_pos->x=user->position->x-1;
        break;
        case 'y'://UPLEFT
        new_pos->y=user->position->y-1;
        new_pos->x=user->position->x-1;
        break;
        case 'u'://UPRIGHT
        new_pos->y=user->position->y-1;
        new_pos->x=user->position->x+1;
        break;
        case 'b'://DOWNLEFT
        new_pos->y=user->position->y+1;
        new_pos->x=user->position->x-1;
        break;
        case 'n'://DOWNRIGHT
        new_pos->y=user->position->y+1;
        new_pos->x=user->position->x+1;
        break;
        default:
        break;
    
    }
    return new_pos;

}
int check_next(Position* new_pos,Level* level){
    Player* user=level->user;
    int space;
    switch (mvinch(new_pos->y, new_pos->x)) {
        case '.':
        case '#':
        case '+':
        move_player(new_pos,user,level->tiles);
        break;
        case 'D':
        case 'G':
        case 'S':
        case 'F':
        case 'U':

            combat(user, get_monster(new_pos, level->monsters),1);
            break;
        case '^':
            health--; 
            move_player(new_pos,user,level->tiles);
            break;

        case '$':{
            int random_score=rand()%5 + 1;
            gold+=random_score ; 
            score+=random_score;
            level->tiles[new_pos->y][new_pos->x]='.';
            move_player(new_pos,user,level->tiles);
            mvprintw(0, 0, "you get %d gold.",random_score);
            getch();
            break;    
        }
        
        case 'Z':
        break;

        case 'X':
        break;

        case 'P':
            
        break;

        case 'A':
            mvprintw(0, 0,"do you want it?(y/n)");
            if (getch()=='y') {
                user->items[user->item_count]=create_arrow(5,20); 
                user->item_count++;
                level->tiles[new_pos->y][new_pos->x]='.';
                move_player(new_pos,user,level->tiles);         
            }
        break;
        case 'W':
            mvprintw(0, 0,"do you want it?(y/n)");
            if (getch()=='y') {
                user->items[user->item_count]=create_wand(15,8);
                user->item_count++;
                level->tiles[new_pos->y][new_pos->x]='.';
                move_player(new_pos,user,level->tiles);
            }
        break;
        case 'R':
            mvprintw(0, 0,"do you want it?(y/n)");
            if (getch()=='y') {
                user->items[user->item_count]=create_sword(10,20);
                user->item_count++;
                level->tiles[new_pos->y][new_pos->x]='.';
                move_player(new_pos,user,level->tiles);
            }
        break;
        case 'E':
            mvprintw(0, 0,"do you want it?(y/n)");
            if (getch()=='y') {
                user->items[user->item_count]=create_dagger(12,10);
                user->item_count++;
                level->tiles[new_pos->y][new_pos->x]='.';
                move_player(new_pos,user,level->tiles);
            }
        break;
        //black gold
        case '@':{
            int random_score=rand()%5 + 5;
            gold+=random_score ; 
            score+=random_score;
            level->tiles[new_pos->y][new_pos->x]='.';
            move_player(new_pos,user,level->tiles);
            mvprintw(0, 0, "you eat black gold and get %d gold.",random_score);
            getch();
            break;    
        }


        case '>':{
            score+=3;
            current_floor++;
            Game game;
            game.curent_level=0;
            clear();

            game_loop(&game);
        break;
        }
        case '*':
        {
            clear();
            char *you_win[] = {
            " Y   Y  OOO  U   U      W   W  I  N   N ",
            " Y   Y O   O U   U      W   W  I  NN  N ",
            "  Y Y  O   O U   U      W W W  I  N N N ",
            "   Y   O   O U   U      W W W  I  N  NN ",
            "   Y    OOO   UUU        W W   I  N   N "
            };
            for (int i = 0; i < 5; ++i) {
                mvprintw(23+i, 70, "%s\n", you_win[i]);
            }
            score+=10;
            gold+=10;
            mvprintw(30, 70, "Y O U G O T %d S C O R E .",score);
            getch();
            
            save_scoreboard(user_name, score , gold);
            endwin();
            exit(0);
            


            break;
        }
        default:
        break;  
    
    }
    return 1;
}


int move_player(Position* new_pos,Player*user , char** level){

    user->position->x=new_pos->x;
    user->position->y=new_pos->y;
}

void draw_player(Player*player){
    mvprintw(player->position->y, player->position->x, "&");
    move(player->position->y, player->position->x);

}