/* 
 * eval.c
 * Copyright 1999 Brian Goetz
 * 
 * An example program for the poker hand evaluation library.
 * All it does is evaluate the hand given on the command line
 * and print out the value. 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include "poker_defs.h"
#include "inlines/eval.h"

int gNCards;
StdDeck_CardMask gCards;

static void
parseArgs(int argc, char **argv) {
  int i;
  StdDeck_CardMask c;

  for (i = 1; i < argc; ++i) {
    if (StdDeck_stringToMask(argv[i], &c) != 1)
      goto error;
    StdDeck_CardMask_OR(gCards, gCards, c);
    ++gNCards;
  }
  
  return;

 error:
  fprintf(stderr, "Usage: eval cards \n");
  exit(0);
}


int 
main(int argc, char **argv) {
  StdRules_HandVal handval;

  gNCards = 0;
  StdDeck_CardMask_RESET(gCards);
  parseArgs(argc, argv);

  handval = StdRules_HANDEVAL(gCards, gNCards);

  Deck_printMask(gCards);
  printf(": ");                                 
  Rules_printHandval(handval);                  
  printf("\n");                                 

  return 0;
}