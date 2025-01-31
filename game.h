#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include <regex.h>
#include <menu.h>


#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_EMAIL_LEN 100
#define USER_FILE "users.txt"

#define MIN_ROOM_WIDTH 4
#define MIN_ROOM_LENGTH 4
#define MAX_ROOMS 6

#define MAX_ITEMS 25
// extern int  MAX_HEIGHT;
// extern int  MAX_WIDTH;

#define MAX_HEIGHT 56
#define MAX_WIDTH 188

typedef struct Game{
    struct Level* levels[10];
    int curent_level;
    
} Game;

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

typedef enum{SWORD_TYPE,SPEAR_TYPE} WeaponType;

typedef struct Weapon{
    WeaponType type;
    int attack;
    int health;

}Weapon;
typedef enum {WEAPON_TYPE, POTION}ItemType;
typedef struct Item{
    ItemType type;
    Position* position;

    union {
        Weapon * weapon;
        // Potion* potion;
    } item;

    char string[256];
} Item;


typedef struct Room{
    Position position;
    int width;
    int length;
    Monster **monsters;
    Item ** items;
    struct Door **door;
    int door_count;
} Room;

typedef struct Door{
    Position position;
    int is_connected;
} Door;

typedef struct Player{
    char username[20];
    Position *position;
    int score;
    int health;
    int attack;
    Room*room;
    int max_health;
    int exprience;
    Item** items;
    int item_count;
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
void draw_monster(Monster* monster);
void draw_player(Player*player);
void draw_level(Level* level);
int game_loop(Game* game);

Item* create_sword(int attack, int health);
void print_inventory(Player*player);


//menu functions
enum{START_GAME, QUIT_GAME};

int game_menu();
int main_menu(int number_items , char* choices[]);
int check_password(char pass[]);
int check_email(char email[]);
int username_exist(const char username[]);
int add_user_to_file(char username[], char password[], char email[]);
int search_for_user(char username[], char password[]);
void generate_random_password(char *password, int length);
int sign_up();
int check_email_for_username(char username[], char email[]);
int login();
int first_menu();

#endif 