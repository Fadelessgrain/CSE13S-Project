#include "io.h"

#include "endian.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint8_t read1_buff[BLOCK] = { 0 };
static uint8_t sym_buff[BLOCK] = { 0 };

static int Index = 0;
static int sym_index = 0;
static int conver_to_bytes(int bits) {
    int num_byte = bits % 8 == 0 ? bits / 8 : (bits / 8) + 1;
    return num_byte;
}

int read_bytes(int infile, uint8_t *buf, int to_read) {
    int to_read_bytes = to_read;
    int total_bytes_read = 0;
    int bytes_read = 0;
    do {
        bytes_read = read(infile, buf + total_bytes_read, to_read_bytes);
        if (bytes_read == -1) {
            fprintf(stderr, "End of file!\n");
            exit(1);
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
            fprintf(stderr, "End of file!\n");
            exit(1);
        }
        to_write_bytes -= bytes_written;
        total_bytes_written += bytes_written;
    } while (total_bytes_written != to_write);

    return total_bytes_written;
}

void read_header(int infile, FileHeader *header) {
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    if (big_endian() == true) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    return;
}

void write_header(int outfile, FileHeader *header) {
    if (big_endian() == true) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
    return;
}

bool read_sym(int infile, uint8_t *sym) {
    int check = -1;
    if (Index == 0) {
        int bytes = read_bytes(infile, read1_buff, BLOCK);
        if (bytes < BLOCK) {
            check = bytes + 1;
        }
    }
    *sym = read1_buff[Index];
    Index += 1;
    if (Index == BLOCK) {
        Index = 0;
    }
    if (Index == check) {
        return false;
    } else {
        return true;
    }
}

//void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {

//
//}

void flush_pairs(int outfile) {
    if (Index > 0) {
        write_bytes(outfile, read1_buff, conver_to_bytes(Index));
    }
}
//bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen);

//void write_word(int outfile, Word *w) {

//}
void flush_words(int outfile) {
    if (sym_index > 0) {
        write_bytes(outfile, sym_buff, conver_to_bytes(sym_index));
    }
}
