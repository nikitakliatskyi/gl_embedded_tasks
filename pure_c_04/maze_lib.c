#include "maze_lib.h"

int is_empty(m_elem character) { return character == EMPTY; }

int is_border(size_t current_row, size_t current_col, size_t rows_amount,
              size_t cols_amount) {
  return ((current_row == (rows_amount - 1)) || (current_row == 0) ||
          (current_col == (cols_amount - 1)) || (current_col == 0));
}

int solve_maze(size_t rows_amount, size_t cols_amount,
               m_elem maze[rows_amount][cols_amount], size_t row, size_t col) {
  maze[row][col] = STEP;
  if ((col - 1 >= 0) && is_empty(maze[row][col - 1])) {
    if (is_border(row, col - 1, rows_amount, cols_amount)) {
      maze[row][col - 1] = STEP;
      return TRUE;
    } else if (solve_maze(rows_amount, cols_amount, maze, row, col - 1)) {
      maze[row][col - 1] = STEP;
      return TRUE;
    }
    maze[row][col - 1] = CHECKED;
  }
  if ((col + 1 < cols_amount) && is_empty(maze[row][col + 1])) {
    if (is_border(row, col + 1, rows_amount, cols_amount)) {
      maze[row][col + 1] = STEP;
      return TRUE;
    } else if (solve_maze(rows_amount, cols_amount, maze, row, col + 1)) {
      maze[row][col + 1] = STEP;
      return TRUE;
    }
    maze[row][col + 1] = CHECKED;
  }
  if ((row - 1 >= 0) && is_empty(maze[row - 1][col])) {
    if (is_border(row - 1, col, rows_amount, cols_amount)) {
      maze[row - 1][col] = STEP;
      return TRUE;
    } else if (solve_maze(rows_amount, cols_amount, maze, row - 1, col)) {
      maze[row - 1][col] = STEP;
      return TRUE;
    }
    maze[row - 1][col] = CHECKED;
  }
  if ((row + 1 < rows_amount) && is_empty(maze[row + 1][col])) {
    if (is_border(row + 1, col, rows_amount, cols_amount)) {
      maze[row + 1][col] = STEP;
      return TRUE;
    } else if (solve_maze(rows_amount, cols_amount, maze, row + 1, col)) {
      maze[row + 1][col] = STEP;
      return TRUE;
    }
    maze[row + 1][col] = CHECKED;
  }
  maze[row][col] = CHECKED;
  return FALSE;
}

void print_maze(size_t rows_amount, size_t cols_amount,
                m_elem maze[rows_amount][cols_amount]) {
  for (int i = 0; i < rows_amount; i++) {
    for (int j = 0; j < cols_amount; j++) {
      printf("%c", maze[i][j]);
    }
    printf("%c", '\n');
  }
}

void iterate_maze(size_t rows_amount, size_t cols_amount,
                  m_elem maze[rows_amount][cols_amount],
                  void (*function)(m_elem *)) {
  for (int i = 0; i < rows_amount; i++) {
    for (int j = 0; j < cols_amount; j++) {
      function(&maze[i][j]);
    }
  }
}

void clear_elem(m_elem *element) {
  if (*element == CHECKED) {
    *element = EMPTY;
  }
}
