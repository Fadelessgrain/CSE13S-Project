#include "code.h"
#include "endian.h"
#include "io.h"
#include "math.h"
#include "word.h"

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// uint8_t sym = 0;
//  int infile = open("test.txt", O_RDONLY);
//  int outfile = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
//  while (read_sym(infile, &sym)) {
//    write_bytes(outfile, &sym, 1);
//  printf("%c\n", sym);

//}
// write pair, flush, pair, close file, read pair)
//	int code = 1;
//	read_sym(infile, &sym);
//	printf("%c\n", sym);
//	write_pair(outfile, code, sym, sizeof(code));
//	flush_pairs(outfile);
//	close(outfile);
//	read_pair(infile, &code, &sym, sizeof(code));
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "i:o:"

int len_of_bits(uint16_t x) {
    uint16_t y = 0;
    while (x > 0) {
        //      do {
        y += 1;
        x >>= 1;
    } //while (x > 0);
    return y;
}

int main(int argc, char **argv) {
    int opt = 0;
    //set the standard file
    int infile = STDIN_FILENO;
    //set the standard file to print to
    int outfile = STDOUT_FILENO;
    //struct used to gte the correct permisions
    //   bool v = false;
    //      struct stat buf;
    //    fstat(infile, &buf);
    //   fchmod(outfile, buf.st_mode);
    //    FileHeader h = { 0, 0 };
    //  h.magic = MAGIC;
    // h.protection = buf.st_mode;
    struct stat buf;
    fstat(infile, &buf);
    //        fchmod(outfile, buf.st_mode);
    FileHeader h = { 0, 0 };
    h.magic = MAGIC;
    if (h.magic != MAGIC) {
        fprintf(stderr, "Not a valid magic number!\n");
        exit(1);
    }
    h.protection = buf.st_mode;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            //sets the input file
            // infile = open(optarg, "r");
            infile = open(optarg, O_RDONLY);
            //if the input file is invalid, return an error
            if (infile == -1) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;
        case 'o':
            //sets the outfile
            //   outfile = fopen(optarg, "w");
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            //if the outfile is invalid, return an error
            if (outfile == -1) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;

            //     case 'v': v = true; break;

        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    } // struct used to get the correct permisions
    /*
	struct stat buf;
    fstat(infile, &buf);
    //        fchmod(outfile, buf.st_mode);
    FileHeader h = { 0, 0 };
    h.magic = MAGIC;
	if (h.magic != MAGIC) {
	fprintf(stderr, "Not a valid magic number!\n");
	exit(1);
	}
    h.protection = buf.st_mode;
 */

    fchmod(outfile, h.protection);
    read_header(outfile, &h);
    WordTable *wt = wt_create();

    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;
    while (read_pair(infile, &curr_code, &curr_sym, len_of_bits(next_code))) {
        wt[next_code] = word_append_sym(wt[curr_code], curr_sym);

        write_word(outfile, wt[next_code]);
        next_code += 1;
        if (next_code == MAX_CODE) {
            wt_reset(wt);
            next_code = START_CODE;
        }
    }

    flush_words(outfile);
    close(infile);
    close(outfile);
    wt_delete(wt);
}
