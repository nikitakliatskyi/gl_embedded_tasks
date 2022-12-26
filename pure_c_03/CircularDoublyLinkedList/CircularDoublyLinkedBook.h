#pragma once
#include "Book.h"

typedef struct Node {
  struct Node *next;
  struct Node *previous;
  Book *book;
} Node;

void Node_PrintAll(const Node *self);

void Node_Link(Node *self, Node *other);
