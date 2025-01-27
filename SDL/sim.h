#ifndef SIM_H
#define SIM_H

#define SIM_X_SIZE 512
#define SIM_Y_SIZE 256

#ifndef _sim_
void simFlush(void);
void simPutPixel(int x, int y, int argb);
int simRand(void);
#endif

extern void simInit(void);
extern void app(void);
extern void simExit(void);

#endif // SIM_H
