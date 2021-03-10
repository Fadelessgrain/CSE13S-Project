#include "io.h"

#include "endian.h"

#include <stdio.h>
#include <unistd.h>

int read_bytes(int infile, uint8_t *buf, int to_read) {
    int to_read_bytes = to_read;
    int total_bytes_read = 0;
    int bytes_read = 0;
    do {

        bytes_read = read(infile, buf + total_bytes_read, to_read_bytes);
        if (bytes_read == -1) {
            printf("welp");
        }
        to_read_bytes -= bytes_read;
        total_bytes_read += bytes_read;
    } while (total_bytes_read != to_read);

    return total_bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int to_write_bytes = to_write;
    int total_bytes_written = 0;
    int bytes_written = 0;
    do {
        bytes_written = write(outfile, buf + total_bytes_written, to_write_bytes);
        if (bytes_written == -1) {
            printf("welp");
        }
        to_write_bytes -= bytes_written;
        total_bytes_written += bytes_written;
    } while (total_bytes_written != to_write);

    return total_bytes_written;
}

//void read_header(int infile, FileHeader *header);
//void write_header(int outfile, FileHeader *header);
//bool read_sym(int infile, uint8_t *sym);
//void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen);
//void flush_pairs(int outfile);
//bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen);
//void write_word(int outfile, Word *w);
//void flush_words(int outfile);
