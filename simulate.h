#ifndef SIMULATE_H
#define SIMULATE_H

#include <ncurses.h>
#include <stdlib.h>

void iterate_generation(int **board, int **next, int h, int w);

void draw(WINDOW * stdscr, int **grid, int h, int w);

#endif