#include <stdio.h>
#include <assert.h>
#include "functions.h"

/* CMSC 216, Fall 2020, Project #1
 * Public test 1 (public1.c)
 *
 * Tests calling has366(2019).
 *
 * (c) Larry Herman, 2020.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  assert(has366(2019) == 0);
  printf("\nTest passed!\n");

  return 0;
}
