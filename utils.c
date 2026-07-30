#include <gb/gb.h>
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <gbdk/console.h>
#include <rand.h>

unsigned int seed = 0;

// Returns 1 if the two sprites are overlapping, 0 otherwise
uint8_t check_collision(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    // Sprites are 8x8
    // We check if the rectangles overlap
    if (x1 < x2 + 8 &&
        x1 + 8 > x2 &&
        y1 < y2 + 8 &&
        y1 + 8 > y2)
    {
        return 1;   // Collision!
    }
    return 0;       // No collision
}

void generate_randseed(void)
{
    gotoxy(0,10);
    printf("Press any key !");
    gotoxy(0,0);

    while(!joypad()){seed++; if(seed>=255)seed=1;}
    waitpadup();
    initrand(seed);
}