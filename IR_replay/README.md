# IR scenario reproducer

make
./uni.sh examples/fact.c
./uni.sh ../SDL/app.c ../SDL/start.c ../SDL/sim.c -lSDL2
./SDL_uni.sh

```
./trace.sh examples/fact.c

./trace.sh ../SDL/app.c ../SDL/start.c ../SDL/sim.c -lSDL2
```