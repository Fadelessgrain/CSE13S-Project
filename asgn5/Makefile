CC = clang

CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: sorting

sorting: sorting.c bubble.c  shell.c quick.c set.c heap.c stack.c statistics.c
	$(CC) $(CFLAGS) -o sorting sorting.c bubble.c shell.c quick.c set.c heap.c stack.c statistics.c

format:
	clang-format -i --style=file *.[ch]

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all -s ./sorting -a -n 100

clean:
	rm -f sorting *.o

debug: CFLAGS += -g
debug: clean all

