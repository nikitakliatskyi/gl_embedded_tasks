#include "SinglyLinkedBook.h"
#include "stdio.h"

int main() {
  Book book1, book2, book3, book4, book5;

  Book_Init(&book1, "Harry Potter and the Sorcerer's Stone", 45.6f, 256,
            ENGLISH, 3.35f, 1997);
  Book_Init(&book2, "Harry Potter and the Chamber of Secrets", 24.19f, 272,
            ENGLISH, 3.5f, 1998);
  Book_Init(&book3, "Harry Potter and the Prisoner of Azkaban", 28.17f, 336,
            ENGLISH, 4.2f, 1999);
  Book_Init(&book4, "Harry Potter and the Goblet of Fire", 14.63f, 464, ENGLISH,
            4.6f, 2000);
  Book_Init(&book5, "Harry Potter and the Order of the Phoenix", 29.28f, 576,
            ENGLISH, 5.7f, 2003);

  Node node1 = {.book = &book1}, node2 = {.book = &book2},
       node3 = {.book = &book3}, node4 = {.book = &book4},
       node5 = {.book = &book5};

  Node_Link(&node1, &node2);
  Node_Link(&node3, &node4);
  Node_Link(&node4, &node5);

  puts("\nfirst linked list:");
  Node_PrintAll(&node1);
  puts("\nsecond linked list:");
  Node_PrintAll(&node3);

  Node_Link(&node2, &node3);
  puts("\nlists after linking:");
  Node_PrintAll(&node1);

  return 0;
}
