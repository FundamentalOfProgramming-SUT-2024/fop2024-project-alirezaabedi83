#include <stdlib.h>
#include <ncurses.h>

#define MIN_ROOM_WIDTH 4
#define MIN_ROOM_LENGTH 4
#define MAX_ROOMS 6

typedef struct {
    char username[20];
    int y;
    int x;
    int score;
    int health;
} Player;

typedef struct {
    int y;
    int x;
    int width;
    int length;
} Room;
Room *rooms[MAX_ROOMS];
int room_count;

int rooms_overlap(Room room1, Room room2) ;
Room generate_random_room(int max_height, int max_width);
void draw_room(Room room);
void room_setup();
Player*player_setup();
int handle_input(int choice,Player*user);
int move_player(int y,int x,Player*user);
int check_next(int new_y,int new_x,Player*user);
int rooms_overlap(Room room1, Room room2) {
    if (room1.x + room1.width <= room2.x || 
        room1.x >= room2.x + room2.width || 
        room1.y + room1.length <= room2.y || 
        room1.y >= room2.y + room2.length) {
        return 0;
    }
    return 1; 
}

Room generate_random_room(int max_height, int max_width) {
    Room room;
    room.width = rand() % (max_width / 2) + MIN_ROOM_WIDTH; 
    room.length = rand() % (max_height / 2) + MIN_ROOM_LENGTH; 
    room.x = rand() % (max_width - room.width); 
    room.y = rand() % (max_height - room.length);
    
    return room;
}

void draw_room(Room room) {
    for (int i = 0; i < room.length; i++) {
        for (int j = 0; j < room.width; j++) {
            if (i == 0 || i == room.length - 1) {
                mvaddch(room.y + i, room.x + j, '_');
            } else if (j == 0 || j == room.width - 1) {
                mvaddch(room.y + i, room.x + j, '|');
            } else {
                mvaddch(room.y + i, room.x + j, '.');
            }
        }
    }
}

void room_setup() {
    int max_height, max_width;
    getmaxyx(stdscr, max_height, max_width);
    
    room_count = 0;
    
    while (room_count < MAX_ROOMS) {
        Room *new_room = (Room *)malloc(sizeof(Room));
        *new_room = generate_random_room(max_height, max_width);
        
        int overlap = 0;
        for (int i = 0; i < room_count; i++) {
            if (rooms_overlap(*new_room, *rooms[i])) {
                overlap = 1;
                break;
            }
        }
        
        if (!overlap) {
            rooms[room_count] = new_room;
            room_count++;
        } else {
            free(new_room);
        }
    }
}

Player*player_setup(){
    Player *new_player;
    new_player=malloc(sizeof(Player));
    new_player->y=rooms[0]->y+2;
    new_player->x=rooms[0]->x+2;
    new_player->health=100;
    new_player->score=0;
    move_player(new_player->y,new_player->x,new_player);
    
    return new_player;
}
void screen_setup(){
    initscr();
    noecho();
    refresh();
}
int handle_input(int choice,Player*user){
    int new_y,new_x;
    switch (choice) {
        case 'j'://UP
        new_y=user->y-1;
        new_x=user->x;
        break;
        case 'k'://DOWN
        new_y=user->y+1;
        new_x=user->x;
        break;
        case 'l'://RIGHT
        new_y=user->y;
        new_x=user->x+1;
        break;
        case 'h'://LEFT
        new_y=user->y;
        new_x=user->x-1;
        break;
        case 'y'://UPLEFT
        new_y=user->y-1;
        new_x=user->x-1;
        break;
        case 'u'://UPRIGHT
        new_y=user->y-1;
        new_x=user->x+1;
        break;
        case 'b'://DOWNLEFT
        new_y=user->y+1;
        new_x=user->x-1;
        break;
        case 'n'://DOWNRIGHT
        new_y=user->y+1;
        new_x=user->x+1;
        break;
        default:
        break;
    
    }
    check_next(new_y,new_x, user);

}
int check_next(int new_y,int new_x,Player*user){
    int space;
    switch (mvinch(new_y, new_x)) {
        case '.':
        move_player(new_y, new_x,user);
        break;
        default:
        move(user->y,user->x);
        break;  
    
    }
}
int move_player(int ypos,int xpos,Player*user){
    mvprintw(user->y, user->x, ".");
    user->x=xpos;
    user->y=ypos;
    mvprintw(user->y, user->x, "&");
    move(user->y, user->x);
    return 1;
}

int main(){
    Player*user;
    int choice;
    screen_setup();
    room_setup();
    for(int i=0;i<room_count;i++){
        draw_room(*rooms[i]);
    }
    user=player_setup();
    while ((choice=getch())!='q') {
        handle_input(choice,user);
    
    }
    
    endwin();
}
