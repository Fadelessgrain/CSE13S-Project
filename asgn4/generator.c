#include "bm.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:"

//Returns the lower nibble of val
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}
// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}
// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}
//struct stat buf;
int main(int argc, char **argv) {
    int opt = 0;
    //set the standard file
    FILE *infile = stdin;
    //set the standard file to print to
    FILE *outfile = stdout;
    struct stat buf;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            //sets the input file
            infile = fopen(optarg, "r");
            //if the input file is invalid, return an error
            if (infile == NULL) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;
        case 'o':
            //sets the outfile
            outfile = fopen(optarg, "w");
            //if the outfile is invalid, return an error
            if (outfile == NULL) {
                fprintf(stderr, "Error with the file");
                exit(1);
            }
            break;
        //		   fstat(fileno(infile), &buf);
        //		   fchmod(fileno(outfile), buf .st_mode);
        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }
    ham_init();
    fstat(fileno(infile), &buf);
    fchmod(fileno(outfile), buf.st_mode);

    while (fgetc(infile) != EOF) {
        uint8_t code = fgetc(infile);
        uint8_t low_code = lower_nibble(code);
        uint8_t high_code = upper_nibble(code);
        uint8_t low_nibble;
        ham_encode(low_code, &low_nibble);
        uint8_t high_nibble;
        ham_encode(high_code, &high_nibble);

        fputc(low_nibble, outfile);
        fputc(high_code, outfile);
    }

    ham_destroy();
    fclose(infile);
    fclose(outfile);
}
