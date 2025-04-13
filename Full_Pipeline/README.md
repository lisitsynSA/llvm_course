## Prerequisites
* Lang FrontEnd ../Flex_Bison/a.out
* NodeLang FrontEnd ../ANTLR/Frontend/a.out
* clang with `sim` target
* llc with `sim` target
* Simulator in ../Sim/

## Full pipeline for one white point
```
./compile_sim.sh graphic.lang
./compile_sim.sh graphic.nl
./compile_sim.sh graphic.c
```
## Full pipeline for graphical application
```
./compile_sim.sh app.lang
./compile_sim.sh app.nl
./compile_sim.sh app.c
./compile_sim.sh app2.c
```