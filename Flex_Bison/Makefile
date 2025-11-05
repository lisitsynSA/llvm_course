all: 0.out 1.out 2.out 3.out 4.out 5.out 6.out 7.out 8.out 9.out 10.out 11.out 12.out FrontEnd.out

0.out: 0.lex
	flex 0.lex
	clang lex.yy.c -o 0.out

0: 0.out
	printf "Hello ,\nworld!\n" | ./0.out

1.out: 1.lex
	flex 1.lex
	clang lex.yy.c -o 1.out

1: 1.out
	printf "10---20--15; // comment\n--42;\n" | ./1.out

2.out: 2.y
	bison 2.y -v
	clang 2.tab.c -o 2.out

2: 2.out
	echo "22+3*4-5;" | ./2.out

3.out: 3.y 3.lex
	bison 3.y -d
	flex 3.lex
	clang lex.yy.c 3.tab.c -o 3.out

3: 3.out
	echo "1 - 2*3/6*7 - 8 + 9;" | ./3.out

4.out: 4.y 4.lex
	bison 4.y -d
	flex 4.lex
	clang lex.yy.c 4.tab.c -o 4.out

4: 4.out
	echo "1 - 2*3/6*7 - 8 + 9" | ./4.out

5.out: 5.y 5.lex
	bison 5.y -d
	flex 5.lex
	clang++ lex.yy.c 5.tab.c $(shell llvm-config --cppflags --ldflags --libs) -o 5.out

5: 5.out
	echo "22+ 3/4 -5;" | ./5.out

6.out: 6.y 6.lex
	bison 6.y -d
	flex 6.lex
	clang++ lex.yy.c 6.tab.c $(shell llvm-config --cppflags --ldflags --libs) -o 6.out

6: 6.out
	echo "22+ 3*5*? -5;"
	./6.out

7.out: 7.y 7.lex
	bison 7.y -d
	flex 7.lex
	clang++ lex.yy.c 7.tab.c $(shell llvm-config --cppflags --ldflags --libs) -o 7.out

7: 7.out
	echo "x + 10*y - (0 == -x) != 0;" | ./7.out

8.out: 8.y 8.lex
	bison 8.y -d
	flex 8.lex
	clang++ lex.yy.c 8.tab.c $(shell llvm-config --cppflags --ldflags --libs) -o 8.out

8: 8.out
	echo "x + 10*y[3*5 + x] - (0 == -x) != 0;" | ./8.out

9.out: 9.y 9.lex
	bison 9.y -d
	flex 9.lex
	clang++ lex.yy.c 9.tab.c $(shell llvm-config --cppflags --ldflags --libs) -o 9.out

9: 9.out
	cat 9.txt | ./9.out

10.out: 10.y 10.lex
	bison 10.y -d
	flex 10.lex
	clang++ lex.yy.c 10.tab.c $(shell llvm-config --cppflags --ldflags --libs) -o 10.out

10: 10.out
	cat 10.txt | ./10.out

11.out: 11.y 11.lex ../SDL/sim.c
	bison 11.y -d
	flex 11.lex
	clang++ lex.yy.c 11.tab.c ../SDL/sim.c $(shell llvm-config --cppflags --ldflags --libs) -lSDL2 -o 11.out

11: 11.out
	cat 11.txt | ./11.out

12.out: 12.y 12.lex ../SDL/sim.c
	bison 12.y -d
	flex 12.lex
	clang++ lex.yy.c 12.tab.c ../SDL/sim.c $(shell llvm-config --cppflags --ldflags --libs) -lSDL2 -o 12.out

12: 12.out
	cat 12.txt | ./12.out

FrontEnd.out: FrontEnd.y FrontEnd.lex ../SDL/sim.c
	bison FrontEnd.y -d
	flex FrontEnd.lex
	clang++ lex.yy.c FrontEnd.tab.c ../SDL/sim.c $(shell llvm-config --cppflags --ldflags --libs) -lSDL2 -o FrontEnd.out

FrontEnd: FrontEnd.out
	cat app.lang | ./FrontEnd.out


clean:
	rm *.yy.c *.out *.tab.c *.tab.h *.output

.PHONY: all clean 0 1 2 3 4 5 6 7 8 9 10 11 12 FrontEnd
