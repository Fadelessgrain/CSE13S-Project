
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
        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }
    //init G and H_T matrices
    ham_init();
    //gets the correct permisioons for the input and output file
    fstat(fileno(infile), &buf);
    fchmod(fileno(outfile), buf.st_mode);

    //read the files
    //get a byte from the file and loop until -1
    while ((fgetc(infile)) != EOF) {

        //get the lowe nibble from the byte
        uint8_t low_code = fgetc(infile);
        //get the upper nibble from the byte
        uint8_t high_code = fgetc(infile);
        //stores the encoded data
        uint8_t low_nibble;
        //passes the pointer to encode function
        //calls the ecnode function
        ham_decode(low_code, &low_nibble);
        //stores upper nibble's encoded data
        uint8_t high_nibble;
        //passes the pointer to the encode function
        //calls the encode function
        ham_decode(high_code, &high_nibble);
        //turns the two nibbles into one byte
        //prints out the lower nibble
        uint8_t byte = pack_byte(low_nibble, high_nibble);
        //prints out the upper nibble
        fputc(byte, outfile);
    }
    //frees the memory
    ham_destroy();
    fclose(infile);
    fclose(outfile);
}
