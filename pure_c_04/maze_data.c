#include "maze_lib.h"

#define ROWS 11
#define COLS 11
#define MAZE_START_ROW 0
#define MAZE_START_COL 5

m_elem maze[ROWS][COLS] = {
    "|---| |---|", "|     |   |", "|---| |-| |", "|   |     |",
    "| | |---| |", "| |       |", "|-| |-| | |", "|   |   | |",
    "| |-|-|-| |", "|     |   |", "|---| |---|",
};
