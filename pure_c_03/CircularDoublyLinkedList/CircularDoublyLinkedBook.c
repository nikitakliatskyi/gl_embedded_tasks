#include "CircularDoublyLinkedBook.h"
#include <stdlib.h>

void Node_PrintAll(const Node *node) {
  const Node *current_node = node;
  if (current_node == NULL) {
    return;
  }
  do {
    Book_Print(current_node->book);
    current_node = current_node->next;
  } while (current_node != node && current_node != NULL);
}

void Node_Link(Node *self, Node *other) {
  if (other->previous != NULL) {
    other->previous->next = self->next;
  }
  if (self->next != NULL) {
    self->next->previous = other->previous;
  }
  self->next = other;
  other->previous = self;
}
