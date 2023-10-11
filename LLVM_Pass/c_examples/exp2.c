#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double fact(uint64_t arg) {
  double res = 1.0;
  for (uint64_t j = 1; j <= arg; ++j) {
    res *= j;
  }
  return res;
}

double calc_exp(uint64_t len) {
  double exp = 0.0;
  for (uint64_t i = len; i > 0; --i) {
    exp += 1.0 / fact(i);
  }
  return exp + 1.0;
}

int main(int argc, char **argv) {
  uint64_t arg = 0;
  if (argc != 2 || (arg = atoi(argv[1])) > 10000 || errno != 0) {
    printf("Usage: 1 argument - exponent series len < 10000\n");
    return 1;
  }

  double exp = calc_exp(arg);
  double res = 0.0;
  for (uint64_t i = 0; i < 10000; i++) {
    res += exp;
  }
  printf("Res = %.10lf\n", res);
  return 0;
}
