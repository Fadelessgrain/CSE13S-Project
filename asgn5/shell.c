#include "shell.h"

#include "gaps.h"
#include "statistics.h"

#include <stdint.h>
#include <stdio.h>

//uint32_t c = 0;

void shell_sort(uint32_t *A, uint32_t n) {
    for (uint32_t gap = 0; gap < *gaps; gap += 1) {
        //  		move();
        for (uint32_t i = 0; i < n; i += 1) {
            //				move();
            uint32_t j = i;
            // move();
            uint32_t temp = A[i];
            // move();
            //		  compare();

            //			compare();
            //			c += 1;

            comparison(A, temp, j - gap);

            //	y = x;
            while ((j >= gap) && (temp < A[j - gap])) {
                compare();
                //		 move();
                A[j] = A[j - gap];
                move();
                j -= gap;
                move();
            }
            //			}

            //			move();
            A[j] = temp;
            //        }
        }

        //		move();
    }
}
