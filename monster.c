#include "game.h"
#include <ncurses.h>
#include <stdio.h>
#include <time.h>

int add_monster(Level *level){
    int x;
    level->monsters=(Monster**)malloc(sizeof(Monster*)*6);
    level->monsters_count=0;
    for (x=0; x<level->rooms_count; x++) {
        if ((rand() % 2 ) == 0) {
            level->monsters[level->monsters_count]=select_monster(level->level);
            set_starting_pos(level->monsters[level->monsters_count] , level->rooms[x]);
            level->monsters_count= level->monsters_count +1;
        }
    
    }

    return 1;
}

Monster* select_monster(int level){
    int monster;

    switch (level) {
        case 1:
        case 2:
        case 3:
        monster= (rand() % 5) + 1;
            break;
        case 4:
        case 5:
            monster= (rand()%4)+2;
            break;
        case 6:    
        monster=3;
        break;

    }

    switch (monster) {
        case 1://deamon
            return create_monster('D',5,1,1,1,2);
        break;
        case 2://fire
            return create_monster('F',10,2,1,1,2);

        break;
        case 3://giant
            return create_monster('G',15,3,1,1,2);
        break;
        case 4://snake
            return create_monster('S',20,1,1,1,2);
        break;
        case 5://undeed
            return create_monster('U',30,2,1,1,2);

        break;
    
    }
    return NULL;
}

Monster* create_monster(char symbol,int health,int attack,int speed,int defence,int pathfinding){
    Monster* new_mon=(Monster*)malloc(sizeof(Monster));

    new_mon->symbol=symbol;
    new_mon->health=health;
    new_mon->attack=attack;
    new_mon->speed=speed;
    new_mon->defence=defence;
    new_mon->pathfinding=pathfinding;
    new_mon->is_alive=1;

    sprintf(new_mon->string,"%c",symbol);

    new_mon->position=malloc(sizeof(Position));

    return new_mon;

}

int set_starting_pos(Monster* monster , Room* room){
    monster->position->x=(rand() % (room->width - 2)) + room->position.x +1;
    monster->position->y=(rand() % (room->length - 2)) + room->position.y + 1;
}

int move_monster(Level* level){
    
    
    
    int x;
    for (x=0; x<level->monsters_count; x++) {
         

        if (level->monsters[x]->is_alive == 0) {
            continue;
        
        }
        if (can_move(level->monsters[x]->position, level->user->position, level->tiles)) {
            if (level->monsters[x]->pathfinding==1) {
                random_move(level->monsters[x]->position);
            }
            else {
                seek_move(level->monsters[x]->position , level->user->position);
            }
        }
    }


}
int seek_move(Position* origin , Position* destination){
        if ((abs((origin->x-1)-destination->x) < abs(origin->x - destination->x)) && (mvinch(origin->y, origin->x-1) =='.')) {
            origin->x = origin->x -1;
        }
        else if ((abs((origin->x+1)-destination->x) < abs(origin->x - destination->x)) && (mvinch(origin->y, origin->x+1) =='.')) {
            origin->x = origin->x +1;
        }
        else if ((abs((origin->y+1)-destination->y) < abs(origin->y - destination->y)) && (mvinch(origin->y+1, origin->x) =='.')) {
            origin->y = origin->y +1;
        }
        else if ((abs((origin->y-1)-destination->y) < abs(origin->y - destination->y)) && (mvinch(origin->y-1, origin->x) =='.')) {
            origin->y = origin->y -1;
        }
        else {
        
        }
        return 1;

}

int random_move(Position* position){
    int random;
    random=rand() % 5;
    switch (random) {
        case 0:
        if (mvinch(position->y -1, position->x) == '.') {
            position->y = position->y -1;
        }

        break;
        case 1:
        if (mvinch(position->y +1, position->x) == '.') {
            position->y = position->y +1;
        }
        break;
        case 2:
        if (mvinch(position->y, position->x - 1) == '.') {
            position->x = position->x-1;
        }
        break;
        case 3:
        if (mvinch(position->y, position->x + 1) == '.') {
            position->x = position->x +1;
        }
        break;
        case 4:
        
        break;
        default:
        break;
    
    }


    return 1;
}

Monster* get_monster(Position* position , Monster** monsters){
    int x;
    for (x=0; x<6; x++) {
        if ((position->y == monsters[x]->position->y) && (position->x == monsters[x]->position->x)) {
            return monsters[x];
        
        }
    
    }
    return NULL;

}
int kill_monster(Monster* monster){
    monster->is_alive=0;
    return 1;
}

void draw_monster(Monster* monster){
    if (monster->is_alive) {
    mvprintw(monster->position->y, monster->position->x, "%s", monster->string);
    }

}

int can_move(Position* monster_pos, Position* user_pos, char **level_map) {
   
        int start_x = (monster_pos->x < user_pos->x) ? monster_pos->x : user_pos->x;
        int end_x = (monster_pos->x > user_pos->x) ? monster_pos->x : user_pos->x;
        int start_y = (monster_pos->y < user_pos->y) ? monster_pos->y : user_pos->y;
        int end_y = (monster_pos->y > user_pos->y) ? monster_pos->y : user_pos->y;

        for (int y = start_y ; y <= end_y; y++) {
            for (int x = start_x; x <= end_x; x++) {
                if (level_map[y][x] == '|' || level_map[y][x] == '_' ||  level_map[y][x] == '+') {
                    return 0; 
                }
        }
        }
    
    
    return 1;
}
/*
Deamon
    symbol:D
    level:1-3
    health:5
    attack:1
    speed:1
    defence:1
    pathfinding:1

Fire
    symbol:F
    level:1-5
    health:10
    attack:2
    speed:1
    defence:1
    pathfinding:2 seeking
Giant
    symbol:G
    level:1-5
    health:15
    attack:3
    speed:1
    defence:1
    pathfinding:1 random

Snake
    symbol:U
    level:1-5
    health:20
    attack:2
    speed:1
    defence:1
    pathfinding:1 random    
Undeed
    symbol:U
    level:1-5
    health:30
    attack:3
    speed:1
    defence:1
    pathfinding:1 random

*/