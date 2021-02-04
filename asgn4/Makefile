CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic  

all: gen dec err

gen: generator.c hamming.c bm.c
	$(CC) $(CFLAGS) -o gen generator.c hamming.c bm.c

dec: decoder.c hamming.c bm.c
	$(CC) $(CFLAGS) -o dec decoder.c hamming.c bm.c

err: error.c
	$(CC) $(CFLAGS) -o err error.c 

format: 
	clang-format -i --style=file *.[ch]

clean:
	rm -f vampire vampire.o


