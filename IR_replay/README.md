# IR scenario reproducer


```
./trace.sh examples/fact.c
./a.out 4
./trace.sh ../SDL/app.c ../SDL/start.c ../SDL/sim.c -lSDL2
./a.out
```