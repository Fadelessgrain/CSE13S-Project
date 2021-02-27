CC = clang

CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: banhammer

banhammer: banhammer.c bf.c  bv.c hash.c ll.c node.c parser.c speck.c
	$(CC) $(CFLAGS) -o banhammer banhammer.c bf.c  bv.c hash.c ll.c node.c parser.c speck.c

format:
	clang-format -i --style=file *.[ch]

valgrind: all
	cat ./badspeak.txt ./newspeak.txt | valgrind --leak-check=full --show-leak-kinds=all -s ./banhammer
#	valgrind --leak-check=full --show-leak-kinds=all -s ./banhammer
clean:
	rm -f banhammer *.o

debug: CFLAGS += -g
debug: clean all

