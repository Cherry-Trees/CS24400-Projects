#pragma once
#include <stdio.h>
#include "globals.h"

void printMaze() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            putchar(maze[i][j]);
        }
        putchar('\n');
    }
}

unsigned char isValid(const int i, const int j) {
    return i >= 0 && i < H && j >= 0 && j < W && maze[i][j] == '+';
}

unsigned char solve(const int i, const int j) {

    maze[i][j] = ' ';

    printMaze();
    printf("\x1b[H");

    if (i == END_H && j == END_W) return 1;
    if (isValid(i + 1, j)) {if (solve(i + 1, j)) return 1;}
    if (isValid(i - 1, j)) {if (solve(i - 1, j)) return 1;}
    if (isValid(i, j + 1)) {if (solve(i, j + 1)) return 1;}
    if (isValid(i, j - 1)) {if (solve(i, j - 1)) return 1;}

    maze[i][j] = 'B';

    printMaze();
    printf("\x1b[H");

    return 0;
}
