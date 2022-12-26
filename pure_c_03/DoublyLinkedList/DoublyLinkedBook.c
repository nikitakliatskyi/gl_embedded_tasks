#include "DoublyLinkedBook.h"
#include <stdlib.h>

void Node_PrintAll(const Node *node) {
  for (; node != NULL; node = node->next) {
    Book_Print(node->book);
  }
}

void Node_Link(Node *self, Node *other) {
  self->next = other;
  other->previous = self;
}
