#include "bm.h"

#include <stdio.h>

int main(void) {
	BitMatrix *a = bm_create(4, 8);

	bm_print(a);
}
