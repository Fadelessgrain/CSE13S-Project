#include "io.h"

#include <stdio.h>
#include <unistd.h>

int read_bytes(int infile, uint8_t *buf, int to_read) {
    int to_read_bytes = to_read;
    int total_bytes_read = 0;
    int bytes_read = 0;

    while (total_bytes_read != to_read) {
        bytes_read = read(infile, buf + total_bytes_read, to_read_bytes);
        if (bytes_read == -1) {
            printf("welp");
        }
        to_read_bytes -= bytes_read;
        total_bytes_read += bytes_read;
    }

    return total_bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int to_write_bytes = to_write;
    int total_bytes_written = 0;
    int bytes_written = 0;

    while (total_bytes_written != to_write) {
        bytes_written = write(outfile, buf + total_bytes_written, to_write_bytes);
        if (bytes_written == -1) {
            printf("welp");
        }
        to_write_bytes -= bytes_written;
        total_bytes_written += bytes_written;
    }

    return total_bytes_written;
}
