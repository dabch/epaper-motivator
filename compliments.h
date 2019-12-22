#ifndef COMPLIMENT_H
#define COMPLIMENT_H

typedef struct compliment {
  int8_t count;
  char **lines;
} compliment_t;

// compliments themselves are stored in the program flash, with some access data structures 
// being stored in the SRAM. 
// To access the compliments, there is an array of compliment_t structs. These store
// information about one compliment: The number of lines and a pointer to an array of char
// pointers to the actual lines. 
// This allows line-by-line access to each compliment when drawing it. The python script's
// output can just be piped into bare_compliments.h which is then included here.
#include "bare_compliments.h"

#endif
