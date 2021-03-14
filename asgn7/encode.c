#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"

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
        //		do {
        y += 1;
        x >>= 1;
    } //while (x > 0);
    return y;
}

int main(int argc, char **argv) {
    //int main(void) {

    int opt = 0;
    //set the standard file
    int infile = STDIN_FILENO;
    //set the standard file to print to
    int outfile = STDOUT_FILENO;
    //struct used to gte the correct permisions
    //   bool v = false;
    struct stat buf;
    fstat(infile, &buf);
    //   fchmod(outfile, buf.st_mode);
    FileHeader h = { 0, 0 };
    h.magic = MAGIC;
    h.protection = buf.st_mode;
    //     fchmod(outfile, h.protection);
    //   write_header(outfile, &h);

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
    }
    //struct used to get the correct permisions
    // struct stat buf;
    // fstat(infile, &buf);
    //   fchmod(outfile, buf.st_mode);
    // FileHeader h = { 0, 0 };
    // h.magic = MAGIC;
    // h.protection = buf.st_mode;
    fchmod(outfile, h.protection);
    write_header(outfile, &h);

    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = START_CODE;
    while (read_sym(infile, &curr_sym)) {
        TrieNode *next_node = trie_step(curr_node, curr_sym);

        if (next_node != NULL) {

            prev_node = curr_node;
            curr_node = next_node;

        } else {
            write_pair(outfile, curr_node->code, curr_sym, len_of_bits(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code += 1;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
        if (curr_node != root) {
            write_pair(outfile, prev_node->code, prev_sym, len_of_bits(next_code));
            next_code += 1;
            next_code = next_code % MAX_CODE;
        }
    }
    write_pair(outfile, STOP_CODE, 0, len_of_bits(next_code));
    flush_pairs(outfile);
    close(infile);
    close(outfile);
    trie_delete(root);
}
