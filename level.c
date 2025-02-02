#include "game.h"

Level* level_setup(int level){
    Level* new_level=(Level*)malloc(sizeof(Level));

    new_level->level=level;
    new_level->rooms_count=6;
    new_level->rooms=room_setup();
    create_hallway(new_level);
    new_level->tiles=save_level();

    new_level->user=player_setup();
    place_player(new_level->rooms , new_level->user);

    add_monster(new_level);
    return new_level;
}

void draw_level(Level* level){
    int x,y,i;

    for (y=0; y<MAX_HEIGHT; y++) {
        for (x=0; x<MAX_WIDTH; x++) {
            mvaddch(y, x, level->tiles[y][x]);  
        }
    
    }

    for (i=0; i<level->monsters_count; i++) {
        draw_monster(level->monsters[i]);
    
    }

    draw_player(level->user);

}

Room** room_setup() {
    int i;
    Room**rooms=(Room**)malloc(sizeof(Room)*MAX_ROOMS);
    int max_height, max_width;
    getmaxyx(stdscr, max_height, max_width);
    
    int room_count = 6;

    for(i=0;i<room_count;i++){
        rooms[i]=generate_random_room(max_height,max_width, i,4);
        draw_room(rooms[i] , i);
    }

    // path_find(&rooms[0]->door[3]->position, &rooms[1]->door[1]->position);

    // create_hallway(rooms[0]->door[1], rooms[1]->door[3]);

    return rooms;
}

// void create_hallway(Level* level){
//     int i,j;
//     int random_room,random_door, count;
//     for (i=0; i<level->rooms_count; i++) {

//         for (j=0; j<level->rooms[i]->door_count; j++) {
//             if (level->rooms[i]->door[j]->is_connected == 1) {
//                 continue;
//             }

//             count=0;

//             while (count<2) {
            
            
//                 random_room=rand() % level->rooms_count;
//                 random_door=rand() % level->rooms[random_room]->door_count;

//                 if (level->rooms[random_room]->door[random_door]->is_connected == 1 || random_room==i) {
//                     count++;
//                     continue;
                
//                 }

//                 path_find(&level->rooms[random_room]->door[random_door]->position, &level->rooms[i]->door[j]->position);

//                 level->rooms[random_room]->door[random_door]->is_connected = 1;
//                 level->rooms[i]->door[j]->is_connected = 1;
//                 break;
//             }
        
//         }
    
//     }
// }

void create_hallway(Level* level){
    path_find(&level->rooms[1]->door[1]->position, &level->rooms[0]->door[3]->position);
    path_find(&level->rooms[2]->door[1]->position, &level->rooms[1]->door[3]->position);
    path_find(&level->rooms[3]->door[0]->position, &level->rooms[0]->door[2]->position);
    path_find(&level->rooms[4]->door[1]->position, &level->rooms[3]->door[3]->position);
    path_find(&level->rooms[5]->door[1]->position, &level->rooms[4]->door[3]->position);
    path_find(&level->rooms[2]->door[2]->position, &level->rooms[5]->door[0]->position);

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

