CC = clang

CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: banhammer

banhammer: banhammer.c bf.c  bv.c hash.c ll.c node.c parser.c speck.c
	$(CC) $(CFLAGS) -o banhammer banhammer.c bf.c  bv.c hash.c ll.c node.c parser.c speck.c

format:
	clang-format -i --style=file *.[ch]

#valgrind: all
#	valgrind --leak-check=full --show-leak-kinds=all -s ./sorting -a -n 100 -p 0
clean:
	rm -f banhammer *.o

debug: CFLAGS += -g
debug: clean all

