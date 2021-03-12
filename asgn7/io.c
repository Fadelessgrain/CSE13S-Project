#include "io.h"

#include "code.h"
#include "endian.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint8_t read1_buff[BLOCK] = { 0 };
static uint8_t sym_buff[BLOCK] = { 0 };

static int Index = 0;
static int buff_index = 0;

static int conver_to_bytes(int bits) {
    int num_byte = bits % 8 == 0 ? bits / 8 : (bits / 8) + 1;
    return num_byte;
}

uint8_t bv_get_bit_16(uint8_t array[], uint16_t i) {
    return (array[i / 8] >> (i % 8)) & 1;
}

uint8_t bv_get_bit(uint8_t array[], uint8_t i) {
    return (array[i / 8] >> (i % 8)) & 1;
}

uint8_t get_bit(uint16_t code, uint8_t i) {
    return (code >> (i % 8)) & 1;
}
int read_bytes(int infile, uint8_t *buf, int to_read) {
    int total_bytes_read = 0;
    int bytes_read = 0;
    do {
        bytes_read = read(infile, buf + total_bytes_read, to_read - bytes_read);
        if (bytes_read == -1) {
            fprintf(stderr, "End of file!\n");
            exit(1);
        }
        total_bytes_read += bytes_read;
    } while (total_bytes_read != to_read && to_read != 0);

    return total_bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int total_bytes_written = 0;
    int bytes_written = 0;
    do {
        bytes_written = write(outfile, buf + total_bytes_written, to_write - bytes_written);
        if (bytes_written == -1) {
            fprintf(stderr, "End of file!\n");
            exit(1);
        }
        total_bytes_written += bytes_written;
    } while (total_bytes_written != to_write && to_write != 0);

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
        int bytes = read_bytes(infile, sym_buff, BLOCK);
        if (bytes < BLOCK) {
            check = bytes + 1;
        }
    }
    *sym = sym_buff[Index];
    Index += 1;
    if (Index == BLOCK * 8) {
        Index = 0;
    }
    if (Index == check) {
        return false;
    } else {
        return true;
    }
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    for (uint8_t i = 0; i < bitlen; i += 1) {
        // gets the bit
        //    uint8_t bit = (code >> i) & 1;
        uint8_t bit = get_bit(code, i);
        if (bit == 1) {
            // set the bit
            read1_buff[buff_index / 8] |= (1 << (buff_index % 8));
        } else {
            // clear the bit
            read1_buff[buff_index / 8] &= ~(1 << (buff_index % 8));
        }
        buff_index += 1;
        // if our indexing counter is at the end, reset the counter and read anther block
        if (buff_index == BLOCK * 8) {
            write_bytes(outfile, read1_buff, BLOCK);
            buff_index = 0;
        }
    }

    for (int i = 0; i < 8; i += 1) {
        // gets the bit
        uint8_t bit = (sym >> i) & 1;
        if (bit == 1) {
            read1_buff[buff_index / 8] |= (1 << (buff_index % 8));
        } else {
            read1_buff[buff_index / 8] &= ~(1 << (buff_index % 8));
        }
        buff_index += 1;
        if (buff_index == BLOCK * 8) {
            write_bytes(outfile, read1_buff, BLOCK);
            buff_index = 0;
        }
    }
}

void flush_pairs(int outfile) {
    if (buff_index > 0) {
        write_bytes(outfile, read1_buff, conver_to_bytes(buff_index));
    }
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    *code = 0;
    for (int i = 0; i < bitlen; i += 1) {
        // if our bit buffer is empty, read bytes
        if (buff_index == 0) {
            read_bytes(infile, read1_buff, BLOCK);
        }
        // set our bit if its 1 after gettin the bit
        if (bv_get_bit_16(read1_buff, buff_index) == 1) {
            *code |= (1 << i);
        } else {
            // otherwise clear it
            *code &= ~(1 << i);
        }
        buff_index += 1;
        //if our counter is at the end of the block, reset it
        if (buff_index == BLOCK * 8) {
            buff_index = 0;
        }
    }

    *sym = 0;
    for (int i = 0; i < 8; i += 1) {
        if (buff_index == 0) {
            read_bytes(infile, read1_buff, BLOCK);
        }
        if (bv_get_bit(read1_buff, buff_index) == 1) {
            *sym |= (1 << i);
        } else {
            *sym &= ~(1 << i);
        }
        buff_index += 1;
        if (buff_index == BLOCK * 8) {
            buff_index = 0;
        }
    }
    // returns weather we have more pair of codes to read!
    return *code == STOP_CODE;
}

void write_word(int outfile, Word *w) {
    // loop through the word
    for (uint32_t i = 0; i < w->len; i += 1) {
        // copys it
        sym_buff[Index] = w->syms[i];
        Index += 1;
        // if our couter is at the end of the bloc, reset it !
        if (Index == BLOCK * 8) {
            write_bytes(outfile, sym_buff, BLOCK);
            Index = 0;
        }
    }
    return;
}
void flush_words(int outfile) {
    if (buff_index > 0) {
        write_bytes(outfile, read1_buff, conver_to_bytes(buff_index));
    }
}
