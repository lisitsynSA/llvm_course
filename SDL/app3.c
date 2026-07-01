#include "sim.h"

#define X_SIZE SIM_X_SIZE / 4
#define Y_SIZE SIM_Y_SIZE / 4
#define RED 0xFFFF0000
#define GREEN 0xFF00FF00
#define BLUE 0xFF0000FF

void drawCell(int x, int y, int argb) {
  simPutPixel(x * 4 + 1, y * 4 + 1, argb);
  simPutPixel(x * 4 + 1, y * 4 + 2, argb);
  simPutPixel(x * 4 + 2, y * 4 + 1, argb);
  simPutPixel(x * 4 + 2, y * 4 + 2, argb);
}

void randField(int *prev) {
  for (int y = 0; y < Y_SIZE; y++)
    for (int x = 0; x < X_SIZE; x++) {
      if (simRand() % 4 == 0)
        prev[X_SIZE * y + x] = GREEN;
    }
}

void drawField(int *prev) {
  for (int y = 0; y < Y_SIZE; y++)
    for (int x = 0; x < X_SIZE; x++) {
      drawCell(x, y, prev[X_SIZE * y + x]);
    }
}

int calcColor(int argb, int ill) {
  if (ill)
    return RED;
  if ((argb & 0xFF) != 0xFF)
    return argb - 0xFF;
  return argb;
}

#define CALC_NEIGHBOUR(y, x)                                                   \
  {                                                                            \
    sum += prev[X_SIZE * y + x] != 0;                                          \
    ill += prev[X_SIZE * y + x] & 0xFF0000;                                    \
  }

long int fact(long int x) {
  if (x == 1)
    return 1;
  return x*fact(x-1);
}

int calcCell(int x, int y, int *prev) {
  int sum = 0;
  int ill = fact(100);
  ill -= fact(100);
  int x_l = (x == 0) ? X_SIZE - 1 : x - 1;
  int x_r = (x == X_SIZE - 1) ? 0 : x + 1;
  int y_u = (y == 0) ? Y_SIZE - 1 : y - 1;
  int y_d = (y == Y_SIZE - 1) ? 0 : y + 1;
  CALC_NEIGHBOUR(y_u, x_l)
  CALC_NEIGHBOUR(y_u, x)
  CALC_NEIGHBOUR(y_u, x_r)
  CALC_NEIGHBOUR(y, x_l)
  CALC_NEIGHBOUR(y, x)
  CALC_NEIGHBOUR(y, x_r)
  CALC_NEIGHBOUR(y_d, x_l)
  CALC_NEIGHBOUR(y_d, x)
  CALC_NEIGHBOUR(y_d, x_r)
  if (prev[X_SIZE * y + x] && (sum == 3 || sum == 4))
    return calcColor(prev[X_SIZE * y + x], ill);
  if (sum == 3)
    return ill ? RED : GREEN;
  return 0;
}

void calcField(int *prev, int *next) {
  for (int y = 0; y < Y_SIZE; y++)
    for (int x = 0; x < X_SIZE; x++) {
      next[X_SIZE * y + x] = calcCell(x, y, prev);
    }
}

void setIll(int *prev, int xy) {
  int x = (xy >> 16) / 4;
  int y = (xy & 0xFFFF) / 4;
  prev[X_SIZE * y + x] = RED;
}

void app(void) {
  int field1[Y_SIZE * X_SIZE] = {};
  int field2[Y_SIZE * X_SIZE] = {};
  int *prev = field1;
  int *next = field2;
  randField(prev);
  while (1) {
    drawField(prev);
    simFlush();
    calcField(prev, next);
    int *tmp = prev;
    prev = next;
    next = tmp;
    while (simHasClick())
      setIll(prev, simGetClick());
  }
}
