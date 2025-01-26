# ANTLR + LLVM Examples

## Prerequsites
```
sudo apt install antlr4
sudo apt install libantlr4-runtime-dev
```

## Examples
1) Simple Expression
> 1+2*{3-4}-5/-1
```
cd Expression
antlr4 -Dlanguage=Cpp Expression.g4 -visitor
clang++ *.cpp -I /usr/include/antlr4-runtime/ -lantlr4-runtime  $(llvm-config --cppflags --ldflags --libs)
```
2) NodeLang
```
(NODE alfa 16777216)
(NODE color (x y step)
    (- (* step (*x y)) alfa)
)
(NODE app ()
    (NODE step_size 42)
    (LOOP step 0 step_size
        (LOOP y 0 SIM_Y_SIZE
            (LOOP x 0 SIM_X_SIZE
                (PUT_PIXEL x y (color x y step))
            )
        )
        (FLUSH)
    )
)
```
```
cd Expression
antlr4 -Dlanguage=Cpp Expression.g4 -visitor
clang++ *.cpp -I /usr/include/antlr4-runtime/ -lantlr4-runtime  $(llvm-config --cppflags --ldflags --libs) ../../SDL/sim.c -lSDL2
```

## Links
[ANTLR](https://github.com/antlr/antlr4)
