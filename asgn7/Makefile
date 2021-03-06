CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic  

all: encode decode  


encode: encode.c trie.c 
	$(CC) $(CFLAGS) -o encode encode.c trie.c

decode: decode.c word.c 
	$(CC) $(CFLAGS) -o decode decode.c word.c

format: 
	clang-format -i --style=file *.[ch]

#valgrind: all 
#	valgrind --leak-check=full --show-leak-kinds=all -s ./gen ./gen -i frankenstein.txt

clean:
	rm -f encode decode *.o
debug: CFLAGS += -g
debug: clean all

