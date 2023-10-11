#include "sim.h"

void app() {
  for (int step = 0; step < 1000; ++step) {
    for (int y = 0; y < Y_SIZE; ++y)
      for (int x = 0; x < X_SIZE; ++x)
        sim_put_pixel(x, y, 0xFF000000 + x * y * step);
    sim_flush();
  }
}
