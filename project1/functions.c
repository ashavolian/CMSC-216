#include "functions.h"

/* Write your implementations of the functions in this source file.
 * Skeleton versions of the functions already appear below.
 */

int has366(int y) {
  if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
    return 1;
  else
    return 0;
}

long sopd(int num, int n) {
  int i, exp = 0;
  long sum = 0, exp_result;
  
  for (i = 1; i <= num; i++) {
    if (num % i == 0){
      exp = n;
      exp_result = 1;
      while(exp != 0) {
	exp_result *= i;
	--exp;
      }
      sum += exp_result;
    }
  }
  return sum;
}


