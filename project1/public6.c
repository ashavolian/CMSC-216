#include <stdio.h>
#include <assert.h>
#include "functions.h"

/* CMSC 216, Fall 2020, Project #1
 * Public test 6 (public6.c)
 *
 * Tests calling sopd(0, 216).
 *
 * (c) Larry Herman, 2020.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  assert(sopd(2, 16) == 65537);
  printf("\nTest passed!\n");

  return 0;
}
