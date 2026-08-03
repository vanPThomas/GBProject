#ifndef BULLET_H
#define BULLET_H

#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "sprites.h"
#include "player.h"

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t dir_horizontal;   // 0=right, 1=left, 2=none
    uint8_t dir_vertical;     // 0=up, 1=down, 2=none
    uint8_t active;
    uint8_t spriteIndex;
} Bullet;

#define MAX_BULLETS 3

extern Bullet bullets[MAX_BULLETS];   // Creates 3 bullets

void update_and_print_bullet_location(void);
void find_first_inactive_bullet(Player player);
void init_bullets(void);

#endif