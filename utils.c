#include <gb/gb.h>
#include "utils.h"

static uint16_t seed = 0x1234;

void init_random(void)
{
    seed = LY_REG | ((uint16_t)LY_REG << 8);
}

uint8_t random_between(uint8_t min, uint8_t max)
{
    seed = seed * 1103515245U + 12345U;
    return min + ((seed >> 8) % (max - min + 1));
}