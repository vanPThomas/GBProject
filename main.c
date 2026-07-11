#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "sprites.h"
#include "background.h"
#include "player.h"
#include "bullet.h"

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t health;
    uint8_t damage;
    uint8_t bulletsFired;
    uint8_t verticalShootingDirection;
    uint8_t horizontalShootingDirection;
} enemy;

void main (void)
{

    // Prepare background
    set_background_data();    
    fill_background();

    // set up graphics
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;

    // Prepare sprites
    set_and_index_spriteData();

    // Ready the actual player and bullet varriables
    Bullet bullet1 = {0, 0, 2, 2, 0, 2};
    Bullet bullet2 = {0, 0, 2, 2, 0, 3};
    Bullet bullet3 = {0, 0, 2, 2, 0, 4}; // x, y, horizontal direction, vertical direction, is bullet active, sprite index
    Player player = {84, 84, 1, 0, 3, 0, 2, 2}; // x, y, facing left, score, lives, bullets fired, verical shooting direction, horizontal shooting direction
    
    move_sprite(0,player.x, player.y);  //initial position

    Bullet bullets[3] = {bullet1, bullet2, bullet3};   // Creates 3 bullets

    // This sets bullet firing rate
    uint8_t bulletFrameCounter = 0;
    const uint8_t firingRateFrames = 20;

    // Main Loop
    while (1)
    {
        // check if player is actually alive
        if (player.lives < 1)
        {
            printf("Game Over");
            break;
        }

        // Draw lives and score
        draw_number(7, 0, player.score);
        draw_number(17, 0, player.lives);

        
        if (bulletFrameCounter > 0) bulletFrameCounter++;
        if (bulletFrameCounter >= firingRateFrames) bulletFrameCounter = 0;

        uint8_t joy = joypad(); // read curent dpad and button state

        //========== Player Movement ==========
        move_player(&player, joy);

        clamp_player_location(&player);

        // ========== Shooting ==========
        // detect if player shot
        if ((joy & J_A) && bulletFrameCounter == 0)
        {
            bulletFrameCounter++;
            // find fist inactive bullet in bullet list and have the player fire it.
            find_first_inactive_bullet(bullets, player);
        }

        update_and_print_bullet_location(bullets);

        update_player_location(player);

        wait_vbl_done(); // Wait for next frame
    }
}


// export PATH=$PATH:/opt/gbdk/bin
// lcc -o game.gb main.c sprites.c background.c player.c bullet.c

/*
resolution: 160×144 pixels
x offset: 8 (so left edge of the screen is 0 + 8)
y offset: 16 (so upper edge of the screen is 0 + 16)
*/