#include "io.h"

#include "code.h"
#include "endian.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// keeps trac of buffers for syms and reading
static uint8_t read1_buff[BLOCK] = { 0 };
static uint8_t sym_buff[BLOCK] = { 0 };

// keeps tract of the index for both buffers
static int Index = 0;
static int buff_index = 0;

// checks how many bytes needed for a bits
static int conver_to_bytes(int bits) {
    int num_byte = bits % 8 == 0 ? bits / 8 : (bits / 8) + 1;
    return num_byte;
}

// code below inspired by Gabe's session
// reads bytes from a file
int read_bytes(int infile, uint8_t *buf, int to_read) {
    // increments the total amount of bytes read
    int total_bytes_read = 0;
    // keeps tract of how many bytes we have read
    int bytes_read = 0;
    do {
        bytes_read = read(infile, buf, to_read);
        // increment the total bytes we have read
        total_bytes_read += bytes_read;
        // increments the buff
        buf += bytes_read;
        // decrements how many bytes we still have to read
        to_read -= bytes_read;
        // loop until we have no bytes to read
    } while (bytes_read > 0 && to_read != 0);
    // returns the total amount of bytes read
    return total_bytes_read;
}
// code above from Gabe's session

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    // increments the total amount of bytes written
    int total_bytes_written = 0;
    // keeps tract of how many bytes we have written
    int bytes_written = 0;
    do {
        bytes_written = write(outfile, buf, to_write);
        // increment the total bytes we have written
        total_bytes_written += bytes_written;
        // increments the buff
        buf += bytes_written;
        // decrements how many bytes we still have to write
        to_write -= bytes_written;
        // loop until we have no bytes to write
    } while (bytes_written > 0 && to_write != 0);
    // returns the total amount of bytes written
    return total_bytes_written;
}

// reads from a file
void read_header(int infile, FileHeader *header) {
    // reads bytes from a file
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    if (big_endian() == true) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    return;
}

// writes to a file
void write_header(int outfile, FileHeader *header) {
    if (big_endian() == true) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    // writes bytes to a file
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
    return;
}

// code below from Eugene's session
bool read_sym(int infile, uint8_t *sym) {
    // keeps tract of the end of buffer
    static int check = -1;
    // checks if our index is at 0, read bytes from a file
    if (Index == 0) {
        int bytes = read_bytes(infile, sym_buff, BLOCK);
        // as long as our bytes read is less then the block, increment the index
        // for end of buffer
        if (bytes < BLOCK) {
            check = bytes;
        }
    }
    // passes back our buffer at the current index
    *sym = sym_buff[Index];
    Index += 1;
    // if the index is at the end of the block, reset the index
    if (Index == BLOCK) {
        Index = 0;
    }
    // if index is equal to the tracker for end of block
    if (Index == check) {
        return false;
    } else {
        return true;
    }
}
// code below from Eugene's session

// Code below from Eugene's session
void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    // loop to find the bits in code
    for (int i = 0; i < bitlen; i += 1) {
        // check if index i of code is 1, then set the bit
        if (((code >> i) & 1) == 1) {
            read1_buff[buff_index / 8] |= (1 << (buff_index % 8));
        } else {
            // clear the bit
            read1_buff[buff_index / 8] &= ~(1 << (buff_index % 8));
        }
        buff_index += 1;
        // if our indexing counter is at the end, reset the counter and
        // read anther block
        if (buff_index == BLOCK * 8) {
            write_bytes(outfile, read1_buff, BLOCK);
            buff_index = 0;
        }
    }
    // loop to find the bits in sym
    for (int i = 0; i < 8; i += 1) {
        // check if index i of code is 1, then set the bit
        if (((sym >> i) & 1) == 1) {
            read1_buff[buff_index / 8] |= (1 << (buff_index % 8));
            // clear the bit
        } else {
            read1_buff[buff_index / 8] &= ~(1 << (buff_index % 8));
        }
        buff_index += 1;
        // if our indexing counter is at the end, reset the counter and                    // read anther block
        if (buff_index == BLOCK * 8) {
            write_bytes(outfile, read1_buff, BLOCK);
            buff_index = 0;
        }
    }
}
// code above from Eugene's session

// flushes a pair to the file
void flush_pairs(int outfile) {
    if (buff_index > 0) {
        // writes the bytes to a file
        write_bytes(outfile, read1_buff, conver_to_bytes(buff_index));
    }
}

// code below from Eugene's session
bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    // clears our our code
    *code = 0;
    // loops through the bits in code
    for (int i = 0; i < bitlen; i += 1) {
        // if our bit buffer index is empty, read bytes
        if (buff_index == 0) {
            read_bytes(infile, read1_buff, BLOCK);
        }
        // get the bit of code at index i, and set it if it == 1
        if (read1_buff[buff_index / 8] >> ((i % 16) & 1) == 1) {
            *code |= (1 << i);
        } else {
            // otherwise clear it
            *code &= ~(1 << i);
        }
        buff_index += 1;
        //if our counter is at the end of the block, reset it
        if (buff_index == BLOCK * 8) {
            //            flush_pairs(infile);
            buff_index = 0;
        }
    }
    // clears out sym
    *sym = 0;
    // loops through the bits in sym
    for (int i = 0; i < 8; i += 1) {
        // if our index is 0, read a new set of bytes
        if (buff_index == 0) {
            read_bytes(infile, read1_buff, BLOCK);
        }
        // get the bit of sym at index i, and set it if it == 1
        if (read1_buff[buff_index / 8] >> ((i % 8) & 1) == 1) {
            *sym |= (1 << i);
            // otherwise clear the bit
        } else {
            *sym &= ~(1 << i);
        }
        buff_index += 1;
        // check if we are at the end of a block
        if (buff_index == BLOCK * 8) {
            buff_index = 0;
        }
    }
    // returns weather we have more pair of codes to read!
    if (*code == STOP_CODE) {
        return false;
    } else {
        return true;
    }
}
// code above from Eugene's session

// writes words into a file
void write_word(int outfile, Word *w) {
    // loop through the len of thw word
    for (uint32_t i = 0; i < w->len; i += 1) {
        // copys it
        sym_buff[Index] = w->syms[i];
        Index += 1;
        // if our couter is at the end of the bloc, reset it !
        if (Index == BLOCK) {
            write_bytes(outfile, sym_buff, BLOCK);
            Index = 0;
        }
    }
    return;
}
// flushes words to a file
void flush_words(int outfile) {
    if (buff_index > 0) {
        write_bytes(outfile, read1_buff, conver_to_bytes(buff_index));
    }
}
