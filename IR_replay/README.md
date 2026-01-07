# IR scenario reproducer


```
./trace.sh examples/fact.c
./TraceDump ./app.func.trace ./app.trace

./trace.sh ../SDL/app.c ../SDL/start.c ../SDL/sim.c -lSDL2
./TraceDump ./app.func.trace ./app.trace
```