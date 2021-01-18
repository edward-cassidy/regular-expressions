#include <stdlib.h>
#include <stdio.h>
#include "re.h"

arena_t create_arena(int size) {
  arena_t arena = malloc(sizeof(struct arena));
  arena->size = size;
  arena->current = 0;
  arena->reg = malloc(size*sizeof(Regexp));
  return arena;
}

void arena_free(arena_t a) {
  free(a->reg);
  free(a);
}

Regexp *re_alloc(arena_t a) {
  if(a->current<a->size){
     Regexp *exp = a->reg + a->current;
     a->current += 1;
     return exp;
  }else{
    return NULL;
  }
}

Regexp *re_chr(arena_t a, char c) {
  Regexp *exp = re_alloc(a);
  if(exp != NULL){
    exp->type = CHR;
    exp->data.chr = c;
    return exp;
  }else{
    return NULL;
  }
}

Regexp *re_alt(arena_t a, Regexp *r1, Regexp *r2) {
  Regexp *exp = re_alloc(a);
  if(exp != NULL){
    exp->type = ALT;
    exp->data.pair.fst = r1;
    exp->data.pair.snd = r2;
    return exp;
  }else{
    return NULL;
  }
}

Regexp *re_seq(arena_t a, Regexp *r1, Regexp *r2) {
  Regexp *exp = re_alloc(a);
  if(exp != NULL){
    exp->type = SEQ;
    exp->data.pair.fst = r1;
    exp->data.pair.snd = r2;
    return exp;
  }else{
    return NULL;
  }
}


int re_match_helper(Regexp *r, char *s, int i) {


  if(s[i]=='\0'){
    return i;
  }else if(r->type == CHR){
    if(s[i]==r->data.chr){
      i++;
      return i;
    }else{
      return i;
    }
  }else if(r->type == SEQ){
    int temp = re_match_helper(r->data.pair.fst, s, i);
    if(temp>i){
      return re_match_helper(r->data.pair.snd, s, temp);
    }else{
      return i;
    }
  }else if(r->type == ALT){
    int temp = re_match_helper(r->data.pair.fst, s, i);
    if(temp>i){
      return temp;
    }else{
      return re_match_helper(r->data.pair.snd, s, i);
    }
  }

  return i;

}


int re_match(Regexp *r, char *s, int i) {
  int result = re_match_helper(r, s, i);
  if(result>i){
    return result;
  }else{
    return -1;
  }
}





void re_print(Regexp *r) {
  if (r != NULL) {
    switch (r->type) {
    case CHR:
      printf("%c", r->data.chr);
      break;
    case SEQ:
      if (r->data.pair.fst->type == ALT) {
	       printf("(");
	       re_print(r->data.pair.fst);
	       printf(")");
      } else {
	       re_print(r->data.pair.fst);
      }
      if (r->data.pair.snd->type == ALT) {
	       printf("(");
	       re_print(r->data.pair.snd);
	       printf(")");
      } else {
         re_print(r->data.pair.snd);
      }
      break;
    case ALT:
      re_print(r->data.pair.fst);
      printf("+");
      re_print(r->data.pair.snd);
      break;
    }
  } else {
    printf("NULL");
  }
}
