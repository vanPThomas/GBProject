#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "sprites.h"

void set_background_data(void);
void fill_background(void);
void draw_number(uint8_t x, uint8_t y, uint16_t number);
void set_and_index_spriteData(void);

#endif