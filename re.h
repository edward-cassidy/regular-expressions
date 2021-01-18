#ifndef RE_H
#define RE_H 1
#include <stdbool.h>


//data structure used to represent a regular expression
typedef struct re Regexp;
enum re_tag { CHR, SEQ, ALT };
struct re {
  enum re_tag type;
  union data {
    char chr;
    struct { Regexp *fst; Regexp *snd; } pair;
  } data;
};



//Define an arena type for allocating pointers to Regexp structures
typedef struct arena *arena_t;
struct arena {
  int size;
  int current;
  Regexp *reg;
};
arena_t create_arena(int size);


//Given an arena a, the re_alloc function allocates a new Regexp and return a pointer to it.
//If the arena lacks room to allocate a new Regexp, it should return NULL.
Regexp *re_alloc(arena_t a);

//Given an arena a, the arena_free function deallocates the arena and its associated storage.
void arena_free(arena_t a);

Regexp *re_chr(arena_t a, char c);
//Allocate a regexp matching the character c, allocating from the arena a. Return NULL if no memory
//is available.

Regexp *re_alt(arena_t a, Regexp *r1, Regexp *r2);
//Allocate a regexp representing the alternative of r1 and r2 from the arena a. Return NULL if no
//memory is available.

Regexp *re_seq(arena_t a, Regexp *r1, Regexp *r2);
//Allocate a regexp representing the sequencing of r1 and r2 from the arena a. Return NULL if no
//memory is available.



int re_match(Regexp *r, char *s, int i);
//Given a regular expression r, a string s, and a valid index into the string i, this function
//returns an integer. If the function returns a nonnegative j, then the regular expression should match
//the substring running from i to j, including i but not j. (So if the re_match(r, s, 5) returns 8, then
//the subrange s[5], s[6], s[7] matches the regexp r.)

void re_print(Regexp *r);
//This function prints out the regular expression given to it.

#endif
