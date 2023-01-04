#pragma once

#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef char m_elem;

#define EMPTY ' '
#define STEP '#'
#define CHECKED '.'
#define HORIZONTAL_WALL '-'
#define VERTICAL_WALL '|'

int is_empty(m_elem character);

int is_border(size_t current_row, size_t current_col, size_t rows_amount,
              size_t cols_amount);

int solve_maze(size_t rows_amount, size_t cols_amount,
               m_elem maze[rows_amount][cols_amount], size_t row, size_t col);

void print_maze(size_t rows_amount, size_t cols_amount,
                m_elem maze[rows_amount][cols_amount]);

void iterate_maze(size_t rows_amount, size_t cols_amount,
                  m_elem maze[rows_amount][cols_amount],
                  void (*function)(m_elem *));

void clear_elem(m_elem *element);
