CFLAGS=-g -Wall -Wextra -std=c99 -pedantic
main: main.o 
	cc main.o -o main
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
