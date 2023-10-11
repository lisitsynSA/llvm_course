#include "sim.h"

#define STEPS 10

void draw_line(int x, int y, int x_len, int y_len, int v_abs) {
  for (int step = 0; step < STEPS; step++) {
    sim_put_pixel(x + x_len * step / STEPS, y + y_len * step / STEPS,
                  0xFF0000FF + (v_abs << 16));
  }
}

int get_abs_velocity(int v1, int v2) {
  if (v1 < 0) {
    v1 = -v1;
  }
  if (v2 < 0) {
    v2 = -v2;
  }
  return (v1 + v2) & 0xFF;
}

void app() {
  int x = (sim_rand() % X_SIZE) / 10;
  int y = (sim_rand() % Y_SIZE) / 10;
  int v_x = sim_rand() % 10;
  int v_y = sim_rand() % 10;
  while (1) {
    draw_line(x, y, v_x / 5, v_y / 5, get_abs_velocity(v_x, v_y));
    sim_flush();
    x += v_x / 5;
    y += v_y / 5;
    v_x += (X_SIZE / 2 - x) * 10 / X_SIZE;
    v_y += (Y_SIZE / 2 - y) * 10 / Y_SIZE;
  }
}
