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

            //     case 'v': v = true; break;

        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }
    // creates the stuct to get correct file protections
    struct stat buf;
    fstat(infile, &buf);
    FileHeader h = { 0, 0 };
    h.magic = MAGIC;
    h.protection = buf.st_mode;
    fchmod(outfile, h.protection);
    // write out to the outfile
    write_header(outfile, &h);
    // creates a trie node and copies of it
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    uint8_t curr_sym = 0;
    uint16_t prev_sym = 0;
    uint16_t next_code = START_CODE;
    // as long as there are syms to read, keep looping
    while (read_sym(infile, &curr_sym)) {
        // check if the sym is in the trie node, then store it
        TrieNode *next_node = trie_step(curr_node, curr_sym);
        // as long as the next node is not empty, update the poistions of our temp nodes
        if (next_node != NULL) {
            prev_node = curr_node;
            curr_node = next_node;

            // otherwise write a pair (encode it) and increment the next code
        } else {
            write_pair(outfile, curr_node->code, curr_sym, len_of_bits(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code += 1;
        }
        // if our next code is equals to the max code reset the counters
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        // update position of our prev sym read
        prev_sym = curr_sym;
        // as long as our current node is not the read write a pair
        if (curr_node != root) {
            write_pair(outfile, prev_node->code, prev_sym, len_of_bits(next_code));
            next_code += 1;
            next_code = next_code % MAX_CODE;
        }
    }
    // write the pair at the end + close the files and free memory
    write_pair(outfile, STOP_CODE, 0, len_of_bits(next_code));
    flush_pairs(outfile);
    close(infile);
    close(outfile);
    trie_delete(root);
}
