#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define MIN_ROOM_WIDTH 4
#define MIN_ROOM_LENGTH 4
#define MAX_ROOMS 6
typedef struct {
    int y;
    int x;
} Position;
typedef struct {
    
} Monster;
typedef struct {
    
} Item;
typedef struct {
    Position position;
    int width;
    int length;
    Monster **monsters;
    Item ** items;
    Position **door;
} Room;
typedef struct {
    char username[20];
    Position position;
    int score;
    int health;
    Room*room;
} Player;
Room *rooms[MAX_ROOMS];
int room_count;

int rooms_overlap(Room room1, Room room2) ;
Room *generate_random_room(int max_height, int max_width);
int draw_room(Room *room);
void room_setup();
Player*player_setup();
int handle_input(int choice,Player*user);
int move_player(int y,int x,Player*user);
int check_next(int new_y,int new_x,Player*user);
int create_hallway(Position* door1, Position* door2);
int rooms_overlap(Room room1, Room room2) {
    if (room1.position.x + room1.width <= room2.position.x || 
        room1.position.x >= room2.position.x + room2.width || 
        room1.position.y + room1.length <= room2.position.y || 
        room1.position.y >= room2.position.y + room2.length) {
        return 0;
    }
    return 1; 
}

Room *generate_random_room(int max_height, int max_width) {
    Room *room=(Room*)malloc(sizeof(Room));
    room->width = rand() % (max_width / 2) + MIN_ROOM_WIDTH; 
    room->length = rand() % (max_height / 2) + MIN_ROOM_LENGTH; 
    room->position.x = rand() % (max_width - room->width); 
    room->position.y = rand() % (max_height - room->length);

    room->door=(Position**)malloc(sizeof(Position*)*4);

    room->door[0]=(Position*)malloc(sizeof(Position));
    room->door[0]->x=rand()%(room->width-2) + room->position.x + 1;
    room->door[0]->y=room->position.y;

    room->door[1]=(Position*)malloc(sizeof(Position));
    room->door[1]->y=rand()%(room->length-2) + room->position.y + 1;
    room->door[1]->x=room->position.x;

    room->door[2]=(Position*)malloc(sizeof(Position));
    room->door[2]->x=rand()%(room->width-2) + room->position.x + 1;
    room->door[2]->y=room->position.y + room->length -1;

    room->door[3]=(Position*)malloc(sizeof(Position));
    room->door[3]->y=rand()%(room->length -2)+ room->position.y+1;
    room->door[3]->x=room->position.x + room->width - 1;

    return room;
}

int draw_room(Room* room) {
    for (int i = 0; i < room->length; i++) {
        for (int j = 0; j < room->width; j++) {
            if (i == 0 || i == room->length - 1) {
                mvaddch(room->position.y + i, room->position.x + j, '_');
            } else if (j == 0 || j == room->width - 1) {
                mvaddch(room->position.y + i, room->position.x + j, '|');
            } else {
                mvaddch(room->position.y + i, room->position.x + j, '.');
            }
        }
    }
    int door_count= sizeof(room->door)/sizeof(Position*);
    for (int i=0; i<4; i++) {
        mvprintw(room->door[i]->y, room->door[i]->x,"+");  
    }
    return 1;
    // create_hallway(rooms[0]->door[0], rooms[1]->door[3]);
}

void room_setup() {
    int max_height, max_width;
    getmaxyx(stdscr, max_height, max_width);
    
    room_count = 0;
    
    while (room_count < MAX_ROOMS) {
        Room *new_room;
        new_room = generate_random_room(max_height, max_width);
        
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

    for(int i=0;i<room_count;i++){
        draw_room(rooms[i]);
    }

    create_hallway(rooms[0]->door[1], rooms[1]->door[3]);


}

int create_hallway(Position* door1, Position* door2){
    Position temp;
    Position prvs;
    int cnt=0;
    temp.x=door1->x;
    temp.y=door1->y;

    prvs=temp;

    while (1) {
        if ((abs((temp.x-1)-door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x-1) ==' ')) {
            prvs.x=temp.x;
            temp.x = temp.x -1;
        }
        else if ((abs((temp.x+1)-door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x+1) ==' ')) {
            prvs.x=temp.x;
            temp.x = temp.x +1;
        }
        else if ((abs((temp.y+1)-door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y+1, temp.x) ==' ')) {
            prvs.y=temp.y;
            temp.y = temp.y +1;
        }
        else if ((abs((temp.y-1)-door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y-1, temp.x) ==' ')) {
            prvs.y=temp.y;
            temp.y = temp.y -1;
        }
        else {
            if (cnt==0) {
                temp=prvs;
                cnt++;
                continue;
            }
            else{
            return 0;
            }
        }   
        mvprintw(temp.y, temp.x, "#");

        getch();
    
    }


    return 1;
}


Player*player_setup(){
    Player *new_player;
    new_player=malloc(sizeof(Player));
    new_player->position.y=rooms[0]->position.y+2;
    new_player->position.x=rooms[0]->position.x+2;
    new_player->health=100;
    new_player->score=0;
    move_player(new_player->position.y,new_player->position.x,new_player);
    
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
        new_y=user->position.y-1;
        new_x=user->position.x;
        break;
        case 'k'://DOWN
        new_y=user->position.y+1;
        new_x=user->position.x;
        break;
        case 'l'://RIGHT
        new_y=user->position.y;
        new_x=user->position.x+1;
        break;
        case 'h'://LEFT
        new_y=user->position.y;
        new_x=user->position.x-1;
        break;
        case 'y'://UPLEFT
        new_y=user->position.y-1;
        new_x=user->position.x-1;
        break;
        case 'u'://UPRIGHT
        new_y=user->position.y-1;
        new_x=user->position.x+1;
        break;
        case 'b'://DOWNLEFT
        new_y=user->position.y+1;
        new_x=user->position.x-1;
        break;
        case 'n'://DOWNRIGHT
        new_y=user->position.y+1;
        new_x=user->position.x+1;
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
        case '#':
        case '+':
        move_player(new_y, new_x,user);
        break;
        default:
        move(user->position.y,user->position.x);
        break;  
    
    }
}
int move_player(int ypos,int xpos,Player*user){
    mvprintw(user->position.y, user->position.x, ".");
    user->position.x=xpos;
    user->position.y=ypos;
    mvprintw(user->position.y, user->position.x, "&");
    move(user->position.y, user->position.x);
    return 1;
}

int main(){
    srand(time(NULL));
    Player*user;
    int choice;
    screen_setup();
    room_setup();
    user=player_setup();
    while ((choice=getch())!='q') {
        handle_input(choice,user);
    
    }
    
    endwin();
}
