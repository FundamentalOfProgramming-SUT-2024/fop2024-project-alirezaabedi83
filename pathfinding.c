#include "game.h"
#include "utils.h"

void add_position_yx(int**front,int ctr,int y,int x){
    front[ctr][0]=y;
    front[ctr][1]=x;

}

int checker(int y, int x){
    char temp = mvinch(y, x);
    if (temp=='.' || temp=='|' || temp=='_') {
        return 0;
    
    }
    else {
        return 1;
    }

}

int add_neighbor(int** front ,int ctr, int*** came_from , int y, int x){
    //up
    if (y>0 && came_from[y-1][x][0] < 0 && checker(y-1,x)) {
        add_position_yx(front, ctr, y-1,  x);
        ctr++;
        came_from[y-1][x][0]=y;
        came_from[y-1][x][1]=x;
    }
    //down
    if (y<MAX_HEIGHT-1 && came_from[y+1][x][0] < 0 && checker(y+1,x)) {
        add_position_yx(front, ctr, y+1,  x);
        ctr++;
        came_from[y+1][x][0]=y;
        came_from[y+1][x][1]=x;
    }
    //right
    if ((x<MAX_WIDTH-1) && came_from[y][x+1][0] < 0 && checker(y,x+1)) {
        add_position_yx(front, ctr, y,  x+1);
        ctr++;
        came_from[y][x+1][0]=y;
        came_from[y][x+1][1]=x;
    }
    //left
    if (x>0 && came_from[y][x-1][0] < 0 && checker(y,x-1)) {
        add_position_yx(front, ctr, y,  x-1);
        ctr++;
        came_from[y][x-1][0]=y;
        came_from[y][x-1][1]=x;
    }

    return ctr;


}
void path_find(Position* origin , Position* destination){
    int i,j , x, y , ycopy;
    int** front=(int**)malloc(sizeof(int*)*MAX_HEIGHT*MAX_WIDTH);
    int *** came_from =(int***)malloc(sizeof(int**)*MAX_HEIGHT);

    int idx=0;
    int ctr=0;

    for (i=0; i<MAX_WIDTH * MAX_HEIGHT; i++) {
        front[i]=(int*) malloc(sizeof(int)*2);
    
    }

    for (i=0; i<MAX_HEIGHT; i++) {
        came_from[i]=(int**)malloc(sizeof(int*)*MAX_WIDTH);

        for (j=0; j<MAX_WIDTH; j++) {
            came_from[i][j]=(int*)malloc(sizeof(int)*2);
            came_from[i][j][0]=-1;
            came_from[i][j][1]=-1;

        
        }
    
    }

    came_from[origin->y][origin->x][0]=-2;
    came_from[origin->y][origin->x][1]=-2;

    add_position_yx(front,ctr,origin->y,origin->x);
    ctr++;

    while (idx<ctr) {
        y=front[idx][0];
        x=front[idx][1];

        if (y==destination->y && x==destination->x) {
            break;
        
        }
        idx++;

        ctr=add_neighbor(front,ctr,came_from ,y ,x );
    
    }

    y=destination->y;
    x=destination->x;

    while (y!=origin->y || x!=origin->x) {
        ycopy=y;
        y=came_from[ycopy][x][0];
        x=came_from[ycopy][x][1];
        mvprintw(y, y,"+");
    }

}