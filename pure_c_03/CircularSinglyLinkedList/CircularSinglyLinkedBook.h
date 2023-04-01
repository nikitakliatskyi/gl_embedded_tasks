#pragma once
#include "../Book/Book.h"

typedef struct Node {
  struct Node *next;
  Book *book;
} Node;

void Node_PrintAll(const Node *self);

void Node_Link(Node *self, Node *other);
