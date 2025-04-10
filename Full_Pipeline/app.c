#define SIM_X_SIZE 512
#define SIM_Y_SIZE 256

void app() {
  for (int step = 0; step < 1000; ++step) {
    for (int y = 0; y < SIM_Y_SIZE; ++y)
      for (int x = 0; x < SIM_X_SIZE; ++x)
        simPutPixel(x, y, 0xFF000000 + x * y * step);
    simFlush();
  }
}
