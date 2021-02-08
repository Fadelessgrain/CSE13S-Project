#include "bm.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "i:o:"

//Returns the lower nibble of val
uint8_t lower_nibble(uint8_t val) {
    return val & (0xF);
}
// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}
// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    int opt = 0;
    //set the standard file
    FILE *infile = stdin;
    //set the standard file to print to
    FILE *outfile = stdout;
    //struct used to gte the correct permisions
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
            //gets the correct permisioons for the input and output file
            fstat(fileno(infile), &buf);
            fchmod(fileno(outfile), buf.st_mode);
        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }
    //init G and H_T matrices
    ham_init();
    //read the files
    //get a byte from the file and loop until -1
    int code;
    while ((code = fgetc(infile)) != EOF) {
        //		printf("%d\t", code);
        //get the lowe nibble from the byte
        uint8_t low_code = lower_nibble(code);
        //get the upper nibble from the byte
        //		printf("%u\n\t", low_code);
        uint8_t high_code = upper_nibble(code);
        //       printf("%u\n\t", low_code);
        //stores the encoded data
        uint8_t low_nibble = 0;
        //passes the pointer to encode function
        uint8_t *result = &low_nibble;
        //calls the ecnode function
        ham_encode(low_code, result);
        //stores upper nibble's encoded data
        uint8_t high_nibble = 0;
        //passes the pointer to the encode function
        uint8_t *result2 = &high_nibble;
        //calls the encode function
        ham_encode(high_code, result2);
        //prints out the lower nibble
        fputc(low_nibble, outfile);
        //prints out the upper nibble
        fputc(high_nibble, outfile);
    }
    //frees the memory
    ham_destroy();
    fclose(infile);
    fclose(outfile);
}
