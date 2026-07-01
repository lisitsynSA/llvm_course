#include <cstdint>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t fact(uint64_t arg) {
  if (arg < 2) {
    return 1;
  } else {
    return arg * fact(arg - 1);
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: 1 argument - factorial len\n");
    return 1;
  }
  uint64_t arg = atoi(argv[1]);
  if (errno == 0) {
    printf("Fact(%lu) = %lu\n", arg, fact(arg));
  }
  return 0;
}
