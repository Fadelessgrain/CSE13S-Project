#ifndef __STATS_H__
#define __STATS_H__

#include <stdint.h>

uint32_t move(void);
uint32_t compare(void);
uint32_t refresh(uint32_t m, uint32_t c);
uint32_t comparison(uint32_t *a, uint32_t temp, uint32_t x);
#endif
