CFLAGS=-g -Wall -Wextra -std=c99 -pedantic
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
	cc main2.o -o main2
test2: main2
	./main2 ./testinput.txt
solution2: main2
	./main2 ./input.txt
debug: main2
	~/Downloads/gdbgui_0.14.0.1 ./main2
libaoc2020.a: $(LIBAOC_OBJ)
	ar -rcs libaoc2020.a $(LIBAOC_OBJ)
