#include <stdio.h>
#include <assert.h>
#include "functions.h"

/* CMSC 216, Fall 2020, Project #1
 * Public test 8 (public8.c)
 *
 * Tests calling sopd(6, 2).
 *
 * (c) Larry Herman, 2020.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  assert(sopd(6, 2) == 50);
  printf("\nTest passed!\n");

  return 0;
}
