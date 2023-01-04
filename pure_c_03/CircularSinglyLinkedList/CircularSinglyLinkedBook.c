#include "CircularSinglyLinkedBook.h"
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
  Node *others_last_node = other;
  while (others_last_node->next != other && others_last_node->next != NULL) {
    others_last_node = others_last_node->next;
  }
  others_last_node->next = self->next;
  self->next = other;
}
