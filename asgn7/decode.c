#include "code.h"
#include "endian.h"
#include "io.h"
#include "math.h"
#include "word.h"

#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "i:o:"

// helper function to converts bits to bytes
uint64_t conver_to_bytes_(uint64_t bits) {
    uint64_t num_byte = bits % 8 == 0 ? bits / 8 : (bits / 8) + 1;
    return num_byte;
}

// helper function that calc the bits needed to represent a number
int len_of_bits(uint16_t x) {
    int y = 0;
    while (x > 0) {
        y += 1;
        x >>= 1;
    }
    return y;
}

int main(int argc, char **argv) {
    int opt = 0;
    //set the standard file
    int infile = STDIN_FILENO;
    //set the standard file to print to
    int outfile = STDOUT_FILENO;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            //sets the input file
            infile = open(optarg, O_RDONLY);
            //if the input file is invalid, return an error
            if (infile == -1) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;
        case 'o':
            //sets the outfile
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            //if the outfile is invalid, return an error
            if (outfile == -1) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;
        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }
    

    //struct used to get header file info
    FileHeader h = { 0, 0 };
    // reader file header + permission
    read_header(infile, &h);
    // checks to make sure we have the correct magic number
    if (h.magic != MAGIC) {
        fprintf(stderr, "Not a valid magic number!\n");
        exit(1);
    }

    // reader file header + permission
    // creates a word table
    WordTable *wt = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;
    // read pair of code and sym
    while (read_pair(infile, &curr_code, &curr_sym, len_of_bits(next_code))) {
        wt[next_code] = word_append_sym(wt[curr_code], curr_sym);
        // writes words to decode them
        write_word(outfile, wt[next_code]);
        next_code += 1;
        // when our code is the max cose, reset the counters
        if (next_code == MAX_CODE) {
            wt_reset(wt);
            next_code = START_CODE;
        }
    }
    // flush to the outfile
    flush_words(outfile);
    // closes files + frees memory
    close(infile);
    close(outfile);
    wt_delete(wt);
}
