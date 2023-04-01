#pragma once

typedef enum {
  UKRAINIAN,
  ENGLISH,
  GERMAN,
  FRENCH,
  UNDEFINED_LANGUAGE
} Language;

const char *Language_ToString(Language language);

typedef struct Book {
  const char *title;
  float price;
  unsigned int pages_amount;
  Language language;
  float weight;
  unsigned int year;
} Book;

void Book_Print(const Book *book);

void Book_Init(Book *self, const char *title, float price,
               unsigned int pages_amount, Language language, float weight,
               unsigned int year);
