#include "sim.h"

#define STEPS 10

int getAbsVelocity(int v1, int v2) {
  if (v1 < 0) {
    v1 = -v1;
  }
  if (v2 < 0) {
    v2 = -v2;
  }
  return (v1 + v2)*2 & 0xFF;
}

void drawLine(int x, int y, int v_x, int v_y) {
  int x_len = v_x / 5;
  int y_len = v_y / 5;
  int v_abs = getAbsVelocity(v_x, v_y);
  for (int step = 0; step < STEPS; step++) {
    simPutPixel(x + x_len * step / STEPS, y + y_len * step / STEPS,
                0xFF0000FF + (v_abs << 16));
  }
}

void app(void) {
  int x = (simRand() % SIM_X_SIZE) / 10;
  int y = (simRand() % SIM_Y_SIZE) / 10;
  int v_x = simRand() % 10;
  int v_y = simRand() % 10;
  while (1) {
    drawLine(x, y, v_x, v_y);
    simFlush();
    x += v_x / 5;
    y += v_y / 5;
    v_x += (SIM_X_SIZE / 2 - x) * 10 / SIM_X_SIZE;
    v_y += (SIM_Y_SIZE / 2 - y) * 10 / SIM_Y_SIZE;
  }
}
