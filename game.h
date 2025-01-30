#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define MIN_ROOM_WIDTH 4
#define MIN_ROOM_LENGTH 4
#define MAX_ROOMS 6

// extern int  MAX_HEIGHT;
// extern int  MAX_WIDTH;

#define MAX_HEIGHT 56
#define MAX_WIDTH 188

typedef struct Level{
    int level;
    char** tiles;
    int rooms_count;
    struct Room** rooms;
    struct Monster** monsters;
    int monsters_count;
    struct Player* user;

    
} Level;

typedef struct Position{
    int y;
    int x;
} Position;
typedef struct Monster{
    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    Position *position;
    int is_alive;
    
} Monster;
typedef struct Item{
    
} Item;

typedef struct Door{
    Position position;
    int is_connected;
} Door;


typedef struct Room{
    Position position;
    int width;
    int length;
    Monster **monsters;
    Item ** items;
    struct Door **door;
    int door_count;
} Room;

typedef struct Player{
    char username[20];
    Position *position;
    int score;
    int health;
    int attack;
    Room*room;
    int max_health;
    int exprience;
} Player;
void screen_setup();
int rooms_overlap(Room room1, Room room2) ;
Room *generate_random_room(int max_height, int max_width , int grid , int door_count);
int draw_room(Room *room);
Room** room_setup();
Player*player_setup();
Position* handle_input(int choice,Player*user);
int move_player(Position* new_pos,Player*user , char** level);
int check_next(Position* new_pos,Level* level);
void create_hallway(Level* level);
char** save_level();
Level* level_setup(int level);

int add_monster(Level* level);
Monster* select_monster(int level);
Monster* create_monster(char symbol,int health,int attack,int speed,int defence,int pathfinding);
int set_starting_pos(Monster* monster , Room* room);
int seek_move(Position* origin , Position* destination);
int move_monster(Level* level);
int random_move(Position* position);
int combat(Player* player , Monster* monster , int command);
Monster* get_monster(Position* position , Monster** monsters);
int kill_monster(Monster* monster);
int print_game_info(Level* level);
int place_player(Room** rooms , Player* user);

#endif 