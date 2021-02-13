#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "absqhrn"
int main(int argc, char **argv) {
    int opt = 0;
    Set S = set_empty();
    while ((opt = getopt(argc, argv, OPTIONs)) != 1) {
        switch (opt) {
        case 'a':
            s = set_insert(s, bubbles);
            s = set_insert(s, shell);
            s = set_insert(s, quick);
            s = set_insert(s, quick);
        }
    }
}
