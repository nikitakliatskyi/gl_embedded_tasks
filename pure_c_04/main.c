#include "maze_data.c"
#include "maze_lib.h"

int main() {
  printf("uncompleted maze:\n");
  print_maze(ROWS, COLS, maze);

  solve_maze(ROWS, COLS, maze, MAZE_START_ROW, MAZE_START_COL);

  iterate_maze(ROWS, COLS, maze, clear_elem);

  printf("completed maze:\n");
  print_maze(ROWS, COLS, maze);

  return 0;
}
