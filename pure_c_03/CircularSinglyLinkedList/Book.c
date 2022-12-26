#include "Book.h"
#include <stdio.h>

const char *Language_ToString(Language language) {
  static const char *LanguagesNames[] = {"Ukrainian", "English", "German",
                                         "French", "Undefined"};
  return LanguagesNames[language];
}

void Book_Print(const Book *book) {
  printf("Title: %s\n"
         "Price: %f\n"
         "Number of pages: %d\n"
         "Language: %s\n"
         "Weight: %f\n"
         "Year: %d\n",
         book->title, book->price, book->pages_amount,
         Language_ToString(book->language), book->weight, book->year);
}

void Book_Init(Book *self, const char *title, float price,
               unsigned int pages_amount, Language language, float weight,
               unsigned int year) {
  self->title = title;
  self->price = price;
  self->pages_amount = pages_amount;
  self->language = language;
  self->weight = weight;
  self->year = year;
}
