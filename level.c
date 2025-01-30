#include "game.h"
#include "utils.h"
#include <ncurses.h>
Level* level_setup(int level){
    Level* new_level=(Level*)malloc(sizeof(Level));

    new_level->level=level;
    new_level->rooms_count=6;
    new_level->rooms=room_setup();
    new_level->tiles=save_level();

    new_level->user=player_setup();
    place_player(new_level->rooms , new_level->user);

    add_monster(new_level);
    return new_level;
}
Room** room_setup() {
    int i;
    Room**rooms=(Room**)malloc(sizeof(Room)*MAX_ROOMS);
    int max_height, max_width;
    getmaxyx(stdscr, max_height, max_width);
    
    int room_count = 6;

    for(i=0;i<room_count;i++){
        rooms[i]=generate_random_room(max_height,max_width, i,4);
        draw_room(rooms[i]);
    }

    path_find(&rooms[0]->door[1]->position, &rooms[1]->door[3]->position);

    // create_hallway(rooms[0]->door[1], rooms[1]->door[3]);

    return rooms;
}

void create_hallway(Level* level){
    
}

char** save_level(){
    int x,y;
    char**level=(char**)malloc(sizeof(char*)*MAX_HEIGHT);

    for (y=0; y<MAX_HEIGHT; y++) {
        level[y]=(char*)malloc(sizeof(char)*MAX_WIDTH);
        for (x=0; x<MAX_WIDTH; x++) {
            level[y][x]=mvinch(y, x);
        
        }
    
    }

    return level;

}
