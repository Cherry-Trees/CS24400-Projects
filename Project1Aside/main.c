#include <stdio.h>
#include "globals.h"
#include "functions.h"

int main() {

    printf("\x1b[H");
    printf("\x1b[2J");
    
    solve(START_H, START_W);
    printMaze();

    return 0;
}