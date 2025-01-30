#include "game.h"
#include <ncurses.h>
#include <stdio.h>
Player*player_setup(){
    Player *new_player;
    new_player=(Player*)malloc(sizeof(Player));
    new_player->position=(Position*)malloc(sizeof(Position));

    new_player->health=100;
    new_player->score=0;
    new_player->attack=1;
    new_player->exprience=0;
    new_player->max_health=100;
    
    
    return new_player;
}

int place_player(Room** rooms , Player* user){
    user->position->x = rooms[0]->position.x + 1;
    user->position->y = rooms[0]->position.y + 1;

    mvprintw(user->position->y,user->position->x,"&");
    move(user->position->y,user->position->x);

    return 1;


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
        case 'S':
        case 'G':
        case 'T':
            combat(user, get_monster(new_pos, level->monsters),1);
        default:
        move(user->position->y,user->position->x);
        break;  
    
    }
    return 1;
}


int move_player(Position* new_pos,Player*user , char** level){
    char buffer[8];
    sprintf(buffer,"%c", level[user->position->y][user->position->x]);

    mvprintw(user->position->y, user->position->x, "%s", buffer);
    user->position->x=new_pos->x;
    user->position->y=new_pos->y;
    mvprintw(user->position->y, user->position->x, "&");
    move(user->position->y, user->position->x);
    return 1;
}