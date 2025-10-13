#include "sim.h"

#define SPEED 20
#define PARTICLES 2000

int getAbsVelocity(int v1, int v2) {
  if (v1 < 0) {
    v1 = -v1;
  }
  if (v2 < 0) {
    v2 = -v2;
  }
  return (v1 + v2) * 1 & 0xFF;
}

void drawLine(int x, int y, int v_x, int v_y, int color_base) {
  int x_len = 2 * v_x / SPEED;
  int y_len = 2 * v_y / SPEED;
  int v_abs = getAbsVelocity(v_x, v_y);
  int color = 0xFF000000 + color_base;
  if (color_base)
    color += (v_abs << 16);
  for (int step = 0; step < SPEED; step++) {
    simPutPixel(x + x_len * step / SPEED, y + y_len * step / SPEED, color);
  }
}

void app(void) {
  int x[PARTICLES] = {};
  int y[PARTICLES] = {};
  int v_x[PARTICLES] = {};
  int v_y[PARTICLES] = {};
  for (int i = 0; i < PARTICLES; i++) {
    x[i] = SPEED + (simRand() % (SIM_X_SIZE - 2 * SPEED));
    y[i] = SPEED + (simRand() % (SIM_Y_SIZE - 2 * SPEED));
    v_x[i] = simRand() % SPEED;
    v_y[i] = simRand() % SPEED;
  }
  int color_base = simRand() & 0xFFFF;
  int invert = simRand() & 0x1;
  while (1) {
    for (int i = 0; i < PARTICLES; i++) {
      drawLine(x[i], y[i], v_x[i], v_y[i], invert ? color_base : 0);
      x[i] += 2 * v_x[i] / SPEED;
      y[i] += 2 * v_y[i] / SPEED;
      v_x[i] += (SIM_X_SIZE / 2 - x[i]) * SPEED / SIM_X_SIZE;
      v_y[i] += (SIM_Y_SIZE / 2 - y[i]) * SPEED / SIM_Y_SIZE;
      drawLine(x[i], y[i], v_x[i], v_y[i], invert ? 0 : color_base);
    }
    simFlush();
  }
}
