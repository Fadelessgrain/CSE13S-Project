CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic  

all: life

life: life.o universe.o
	$(CC) -o life life.o universe.o -lncurses

life.o: life.c
	$(CC) $(CFLAGS) -c life.c

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c 

clean:
	rm -f life *.o

format: 
	clang-format -i --style=file *.[ch]

valgrind: all 
	valgrind -s --leak-check=full ./life -i lists/Hertz-oscillator.txt -s -o out
