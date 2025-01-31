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
        monster= (rand() % 2) + 1;
            break;
        case 4:
        case 5:
            monster= (rand()%2)+2;
            break;
        case 6:    
        monster=3;
        break;

    }

    switch (monster) {
        case 1://Spider
            return create_monster('S',2,1,1,1,1);
        break;
        case 2://goblin
            return create_monster('G',5,3,1,1,2);

        break;
        case 3://troll
            return create_monster('T',15,5,1,1,1);
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

        if (level->monsters[x]->pathfinding==1) {
            random_move(level->monsters[x]->position);
        }
        else {
            seek_move(level->monsters[x]->position , level->user->position);
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
/*
Spider
    symbol:S
    level:1-3
    health:2
    attack:1
    speed:1
    defence:1
    pathfinding:1

Goblin
    symbol:G
    level:1-5
    health:5
    attack:3
    speed:1
    defence:1
    pathfinding:2 seeking

Troll
    symbol:T
    level:4-6
    health:15
    attack:5
    speed:1
    defence:1
    pathfinding:1 random
*/