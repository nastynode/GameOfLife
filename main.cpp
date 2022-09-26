//cross platform wait
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "simulate.h"

using namespace std;

//pass by reference
bool start_ncurses(int &h, int &w){
    initscr();
    noecho();
    cbreak();
    getmaxyx(stdscr, h, w);
    if(!has_colors()){
        printw("Terminal does not support color");
        getch();
        return false;
    }
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    keypad(stdscr, TRUE);
    return true;
}

WINDOW * start_window(int h, int w){
    int h_third = h/3;
    int w_third = w/3;
    return newwin(h_third, w_third, h_third, w_third);
}


int main(int argc, char ** argv){
    
    int h, w, z;
    int c;
    if(!start_ncurses(h, w)){
        return 0;
    }

    WINDOW * win = start_window(h, w);
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "Conway's Game of Life");
    wrefresh(win);
    //prints a string(const char *) to a window
    mvprintw(h/2, w/2 - 11, "Pres any key to begin");
    mvprintw(h-3, 1, "Use the arrow keys to move. Press \"Space\" to place/remove a cell.");
    mvprintw(h-2, 1, "Press \"Enter\" to run simulation or \"Esc\" to exit.");
    mvprintw(h-1, 1, "Press \"ctrl + c\" to end simulation.");
    getch();
    clear();
    refresh();
    char t;
    int posx = w/2, posy = h/2;

    mvprintw(h-1, w-20, "Window: %d by %d", h, w);

    move(posy, posx);

    //virtual representation of board
    int ** board = (int **) calloc(h-1, sizeof(int *)); //dont include last row, thats diagnostic
    for(z = 0; z < h; z++){
        board[z] = (int *) calloc(w, sizeof(int));
    }
    //virtual representation of next frame
    int ** next = (int **) calloc(h-1, sizeof(int *)); 
    for(z = 0; z < h; z++){
        next[z] = (int *) calloc(w, sizeof(int));
    }

    while(c != '\n'){
        c = getch();
        switch(c){
            case KEY_UP:
                //printw("up");
                posy == 0 ? posy = h - 2 : posy--;
                break;
            case KEY_DOWN:
                //printw("down");
                posy == h - 2 ? posy = 0 : posy++;
                break;
            case KEY_LEFT:
                //printw("left");
                posx == 0 ? posx = w - 1 : posx--;
                break;
            case KEY_RIGHT:
                //printw("right");
                posx == w - 1 ? posx = 0 : posx++;
                break;
            case ' ':
                t = mvinch(posy, posx);
                t == 'O' ? printw(" ") : printw("O"); 
                t == 'O' ? board[posy][posx] = 0 : board[posy][posx] = 1;
                break;
            case '\n':
                //printw("enter");
                //hide cursor?
                move(0, 0);
                break;
            default:
                //probably do nothing
                //printw("default");
                break;
        }
        move(posy, posx);
    }

    draw(stdscr, board, h, w);
    //mvprintw(h-1, 0, "Press enter to go to next generation");
    //getch();
    
    int count = 0;
    while(c != 'q'){
        //iterate
        iterate_generation(board, next, h, w);
        //copy next frame onto current
        memcpy(*board, *next, (w * (h-1) * sizeof(int)));
        //draw
        draw(stdscr, board, h, w);
        mvprintw(h-1, 0, "Generation %d", count);
        
        
        c = getch(); //need to stall between frames, say .5 seconds? (500ms)
        count++;
    }

    endwin();

    return 0;
}

/*
    Useful ncurses functions

    mvinch(y, x) check char at screen position!
    noecho() stops user input from echoing in window
    echo() enabled by default but can be used to run on
    refresh() refreshes the screen to match whats in memory
    wrefresh(win) refreshes the passed window
    clear() clears screen (duh)
    printw() just like printf but prints at current curses location
    move(y, x) moves cursor to coordinate
    mvprintw(y, x, "%d", var) executes move to y,x then does printw
    box(window, int/char, int/char) where the 2nd param is character for top/bottom border and 3rd param is l/r border 
    getyx(<window>, y, x) 

    WINDOW pointer var with constructor newwin(h, w, start_y, start_x)

    *attributes*
    attron(int) attroff(int) often use ncurses enums:
        A_<attribute>


    
*/
