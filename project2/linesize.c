#include <stdio.h>

int main (void) {
  int line_count = 0;
  int long_lines = 0;
  char curr_char;
  int i;
  while ((curr_char = getchar()) != EOF) {
    int line_size = 0;
    int line_length = 0;
    char newline[999];
    while (curr_char != '\n') {
      newline[line_size] = curr_char;
      if(curr_char == '\t'){
        line_length += 8 - (line_size % 8);
      } else{
        line_length++;
      }
      line_size++;
      curr_char = getchar();
    }    
    newline[line_size] = '\n';
    if (line_length > 80) {
      long_lines++;
      printf("X%5d> ", line_length);
    } else{
      printf("%6d> ", line_length);
    }
    for (i = 0; i <= line_size; i++) {
	    printf("%c", newline[i]);
    }
    line_count += 1;
  }
  printf("%d %d\n", line_count, long_lines);
  return 0;
}
