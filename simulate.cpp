#include <ncurses.h>
#include <stdlib.h>

//draw next frame over the current
void draw(WINDOW * stdscr, int **grid, int h, int w){
    //clear stdscr and draw current board
    clear();
    int r, c;
    for(r=0; r<h-1; r++){
        for(c=0;c<w;c++){
            if(grid[r][c] == 1){
                mvprintw(r, c, "O");
            }
        }
    }

}


/*
Rules:
    1) Each cell with  <= 1 neighbors dies
    2) each cell with >= 4 neighbors dies
      - therefore, each cell with 2 or 3 neighbors survives
    3) each cell with 3 neighbors becomes alive

Algo:
    for each cell in stdscr
        check each of 8 neighbors, counting live neighbs
            when checking neighbors, make sure you don't go out of bounds, last row for diagnostic info so out of bounds
        evaluate rules, make life or dead accordingly

*/


void iterate_generation(int **board, int **next, int h, int w){
    int i, j, live;
    for(i=0;i<h-1;i++){
        for(j=0;j<w;j++){
            live = 0;
            //count live neighbors starting with top left going clockwise
            //i know theres a way to organize these if statements better, perhaps revise later
            //top left
            if(i-1>=0 && j-1>=0 && board[i-1][j-1]==1){
                live++;
            }
            //top mid
            if(i-1>=0 && board[i-1][j]==1){
                live++;
            }
            //top right
            if(i-1>=0 && j+1<w && board[i-1][j+1]==1){
                live++;
            }
            //mid right
            if(j+1<w && board[i][j+1]==1){
                live++;
            }
            //bottom right
            if(i+1<h-1 && j+1<w && board[i+1][j+1]==1){
                live++;
            }
            //bottom mid
            if(i+1<h-1 && board[i+1][j]==1){
                live++;
            }
            //bottom left
            if(i+1<h-1 && j-1>=0 && board[i+1][j-1]==1){
                live++;
            }
            //mid left
            if(j-1>=0 && board[i][j-1]==1){
                live++;
            }


            //evaluate rules
            if(live <= 1 || live >= 4){
                next[i][j] = 0;
            }
            else if(live == 3){
                next[i][j] = 1;
            }
            else if(live == 2 && board[i][j] == 1){
                next[i][j] = 1;
            }
            else{ //2 neighbors for a dead cell
                next[i][j] = 0;
            }

            //mvprintw(h-1, 0, "%d, %d: %d live neighbors", i, j, live);
            //getch();
        }
    }
}