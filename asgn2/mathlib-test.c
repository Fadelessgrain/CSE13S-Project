#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

//code below inspired by Eugene's lab
#define OPTIONS "asctel"

int main(int argc, char **argv) {
    int opt = 0;
    bool return_sin, return_cos, return_tan, return_exp, return_log;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            return_sin = true;
            return_cos = true;
            return_tan = true;
            return_exp = true;
            return_log = true;
            break;
        case 's': return_sin = true; break;
        case 'c': return_cos = true; break;
        case 't': return_tan = true; break;
        case 'e': return_exp = true; break;
        case 'l': return_log = true; break;
        default: fprintf(stderr, "Not a valid option. Use %s -[asctel]\n", argv[0]);
        }
    }
    //code above inspired by Eugene's lab
    if (return_sin == true) {
        printf("  x           Cos              Library        Difference\n");
        printf("  -           ---               -------        ---------\n");
        for (double x = -2 * M_PI; x < 2 * M_PI; x += 0.1) {
            double my_sin = Sin(x);
            double library_sin = sin(x);
            double diff = my_sin - library_sin;
            printf("%7.4f % 16.8f % 16.8f % 16.10f\n", x, my_sin, library_sin, diff);
        }
    }

    if (return_cos == true) {
        printf("  x           Cos              Library        Difference\n");
        printf("  -           ---    	       -------        ---------\n");
        for (double x = -2 * M_PI; x < 2 * M_PI; x += 0.1) {
            double my_cos = Cos(x);
            double library_cos = cos(x);
            double diffe = my_cos - library_cos;
            printf("%7.4f % 16.8f % 16.8f % 16.10f\n", x, my_cos, library_cos, diffe);
        }
    }

    if (return_tan == true) {
        printf("  x           Tan              Library        Difference\n");
        printf("  -           ---               -------        ---------\n");
        for (double x = -1 * (M_PI / 3); x < (M_PI / 3); x += 0.1) {
            double my_tan = Tan(x);
            double library_tan = tan(x);
            double diffe = my_tan - library_tan;
            printf("%7.4f % 16.8f % 16.8f % 16.10f\n", x, my_tan, library_tan, diffe);
        }
    }

    if (return_exp == true) {
        printf("  x           Exp              Library        Difference\n");
        printf("  -           ---               -------        ---------\n");
        for (double x = 1; x <= 10; x += 0.1) {
            double my_exp = Exp(x);
            double library_exp = exp(x);
            double diffe = my_exp - library_exp;
            printf("%7.4f % 16.8f % 16.8f % 16.10f\n", x, my_exp, library_exp, diffe);
        }
    }

    if (return_log == true) {
        printf("  x           Log              Library        Difference\n");
        printf("  -           ---               -------        ---------\n");
        for (double x = 1; x <= 10; x += 0.1) {
            double my_log = Log(x);
            double library_log = log(x);
            double diffe = my_log - library_log;
            printf("%7.4f % 16.8f % 16.8f % 16.10f\n", x, my_log, library_log, diffe);
        }
    }

    return 0;
}
