#include <gb/gb.h>
#include <stdlib.h>
#include <time.h>

void init_random(void)
{
    srand(12345);
}

uint8_t random_range(uint8_t min, uint8_t max)
{
    return min + (rand() % (max - min + 1));
}