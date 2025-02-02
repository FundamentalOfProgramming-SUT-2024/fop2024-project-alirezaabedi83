#include "game.h"
#include <ncurses.h>
#include <stdlib.h>

Room *generate_random_room(int max_height, int max_width , int grid, int door_count) {
    Room *room=(Room*)malloc(sizeof(Room));
    room->door_count=door_count;
    room->width = rand() % ((max_width-49) / 3) + MIN_ROOM_WIDTH; 
    room->length = rand() % ((max_height-16) / 2) + MIN_ROOM_LENGTH; 

    switch (grid) {
        case 0:
        room->position.x = rand() % (50 - room->width) + 3; 
        room->position.y = rand() % (24 - room->length) + 3;
        break;

        case 1:
        room->position.x = rand() % (50 - room->width) + 63; 
        room->position.y = rand() % (24 - room->length) + 3;
        break;

        case 2:
        room->position.x = rand() % (50 - room->width) + 123; 
        room->position.y = rand() % (24 - room->length) + 3;
        break;

        case 3:
        room->position.x = rand() % (50 - room->width) + 3; 
        room->position.y = rand() % (24 - room->length) + 27;
        break;

        case 4:
        room->position.x = rand() % (50 - room->width) + 63; 
        room->position.y = rand() % (24 - room->length) + 27;
        break;

        case 5:
        room->position.x = rand() % (50 - room->width) + 123; 
        room->position.y = rand() % (24 - room->length) + 27;
        break;
    
    }
    

    room->door=(Door**)malloc(sizeof(Door*)*door_count);

    for (int i=0; i<door_count; i++) {
        room->door[i]=(Door*)malloc(sizeof(Door));
        room->door[i]->is_connected=0;
    }

    room->door[0]->position.x=rand()%(room->width-2) + room->position.x + 1;
    room->door[0]->position.y=room->position.y;

    room->door[1]->position.y=rand()%(room->length-2) + room->position.y + 1;
    room->door[1]->position.x=room->position.x;

    room->door[2]->position.x=rand()%(room->width-2) + room->position.x + 1;
    room->door[2]->position.y=room->position.y + room->length -1;

    room->door[3]->position.y=rand()%(room->length -2)+ room->position.y+1;
    room->door[3]->position.x=room->position.x + room->width - 1;

    return room;
}

int draw_room(Room* room , int num_of_room) {
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

    mvaddch(room->position.y + rand()%(room->length-1)+1,room->position.x + rand()%(room->width-1)+1, 'o');

    if (num_of_room==3) {
        if (current_floor==4) {
            mvaddch(room->position.y + rand()%(room->length-2)+1,room->position.x + rand()%(room->width-2)+1, '*');
        }
        else{
            mvaddch(room->position.y + rand()%(room->length-2)+1,room->position.x + rand()%(room->width-2)+1, '>');
        }
    
    }

    if ((rand()%2)==1) {
         mvaddch(room->position.y + rand()%(room->length-2)+1,room->position.x + rand()%(room->width-2)+1, '^');
    
    }

    if ((rand()%2)==1) {
         mvaddch(room->position.y + rand()%(room->length-2)+1,room->position.x + rand()%(room->width-2)+1, '$');
    
    }
    // int door_count= sizeof(room->door)/sizeof(Position*);
    for (int i=0; i<4; i++) {
        mvprintw(room->door[i]->position.y, room->door[i]->position.x,"+");  
    }
    return 1;
}
