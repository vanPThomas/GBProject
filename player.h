#ifndef PLAYER_H
#define PLAYER_H

#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "sprites.h"

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t facingLeft;
    uint8_t score;
    uint8_t lives;
    uint8_t bulletsFired;
    uint8_t verticalShootingDirection;
    uint8_t horizontalShootingDirection;
} Player;

void move_player(Player *player, uint8_t joy);
void clamp_player_location(Player *player);
void update_player_location(Player player);

#endif