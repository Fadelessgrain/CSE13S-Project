#include "code.h"
#include "endian.h"
#include "io.h"
#include "math.h"
#include "word.h"

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    //    uint8_t x = 13;
    //  Word *w = word_create(&x, 1);
    //  WordTable *y = wt_create();
    // y[0] = word_append_sym(w, 3);
    //  y[1] = word_append_sym(w, 3);
    //  y[2] = word_append_sym(w, 3);
    //  wt_reset(y);
    //  word_delete(w);
    // wt_delete(y);

    uint8_t sym = 0;
    int infile = open("test.txt", O_RDONLY);
    int outfile = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    do {
        write_bytes(outfile, &sym, 1);
    } while (read_sym(infile, &sym) == true);
    return 0;
}
