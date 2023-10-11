#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int func(int arg1, int arg2) { return arg1 + arg2 * 2; }

int main() {
  printf("%d\n", func(func(3, 4), func(5, 6)) + func(3, 4));
  return 0;
}