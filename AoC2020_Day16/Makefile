CFLAGS=-g -Wall -Wextra -std=c99 -pedantic -march=native -pg
LIBAOC_OBJ=aoc2020.o
main: main.o libaoc2020.a
	cc main.o -o main -L. -laoc2020
clean: 
	rm *.o main
test: main 
	./main ./testinput.txt
solution: main 
	./main ./input.txt
main2: main2.o
	cc main2.o -o main2 -L. -laoc2020
test2: main2
	./main2 ./testinput2.txt
solution2: main2
	./main2 ./input.txt
main2_s: main2_s.o
	cc main2_s.o -o main2_s -L. -laoc2020
test2_s: main2_s
	./main2_s ./testinput2.txt
solution2_s: main2_s
	./main2_s ./input.txt
debug: main2
	~/Downloads/gdbgui_0.14.0.1 ./main2
hash: main2_hash.o
	cc main2_hash.o -o hash -L. -laoc2020 -pg
libaoc2020.a: $(LIBAOC_OBJ)
	ar -rcs libaoc2020.a $(LIBAOC_OBJ)
