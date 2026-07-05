#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "sprites.h"
#include "background.h"
#include "player.h"

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t dir_horizontal;   // 0=right, 1=left, 2=none
    uint8_t dir_vertical;     // 0=up, 1=down, 2=none
    uint8_t active;
    uint8_t spriteIndex;
} Bullet;

void draw_number(uint8_t x, uint8_t y, uint16_t number);

void set_and_index_spriteData(void);
void update_and_print_bullet_location(Bullet bullets[]);
void find_first_inactive_bullet(Bullet bullets[], Player player);

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

void draw_number(uint8_t x, uint8_t y, uint16_t number)
{
    set_bkg_tile_xy(x+2, y, 20 + (number % 10));        // units
    number /= 10;
    set_bkg_tile_xy(x+1, y, 20 + (number % 10));        // tens
    number /= 10;
    set_bkg_tile_xy(x,   y, 20 + (number % 10));        // hundreds
}


void set_and_index_spriteData(void)
{
    set_sprite_data(0,1,PlayerSpriteLeftFacing);  // index 0, load sprite into vram, same parameter concept as in the set_bkg_data
    set_sprite_data(1,1,PlayerSpriteRightFacing);
    set_sprite_tile(0,0);               // sprite 0 uses tile 0
    set_sprite_tile(1,1);
    /*
    Important explanation: set_sprite_data loads the sprite into vram at a certyain index.
    set_sprite_tile puts it in the list of 40 sprites that can be used. To boil it down:
    set_sprite_data(0, 1, BulletSprite);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 0);
    set_sprite_tile(2, 0);
    This could be done when the player shot 3 times. here you say that this one sprite needs three spots in the list of 40 sprites.
    Now it can be printed to screen 3 times:
    move_sprite(0, bullet1_x, bullet1_y);   // Move first bullet
    move_sprite(1, bullet2_x, bullet2_y);   // Move second bullet
    move_sprite(2, bullet3_x, bullet3_y);   // Move third bullet
    */

    set_sprite_data (2, 1, BulletSprite);
    set_sprite_tile (2, 2); // bullet index 2
    set_sprite_tile (3, 2); // bullet index 3
    set_sprite_tile (4, 2); // bullet index 4
    
}

// Note: Bullet bullets[] is automatically treated as Bullet *bullets in C
// (array decay to pointer). That's why we can modify the original array.
void update_and_print_bullet_location(Bullet bullets[])
{
    // update all bullets location and print
    for (uint8_t i = 0; i < 3; i++)
    {
        if (bullets[i].active)
        {
            if (bullets[i].dir_horizontal == 0)
            {
                bullets[i].x += 2;
            }
            if (bullets[i].dir_horizontal == 1)
            {
                bullets[i].x -= 2;
            }
            if (bullets[i].dir_vertical == 0)
            {
                bullets[i].y -= 2;
            }
            if (bullets[i].dir_vertical == 1)
            {
                bullets[i].y += 2;
            }
            move_sprite (bullets[i].spriteIndex, bullets[i].x, bullets[i].y);
            
        }

        // Detect if bullet goes off screen and delete it
        if (bullets[i].active)
        {
            if (bullets[i].x < 16 || bullets[i].x > 152 || bullets[i].y < 32 || bullets[i].y > 144)
            {
                bullets[i].x = 0;
                bullets[i].y = 0;
                bullets[i].active = 0;
                bullets[i].dir_horizontal = 2;
                bullets[i].dir_vertical = 2;
                move_sprite (bullets[i].spriteIndex, 0, 0);
            }
        }
    }
}

void find_first_inactive_bullet(Bullet bullets[], Player player)
{
    // Find first inactive bullet
    for (uint8_t i = 0; i < 3; i++)
    {
        if(bullets[i].active == 0)
        {
            bullets[i].active = 1;

            bullets[i].dir_horizontal = 2;
            bullets[i].dir_vertical = 2;

            if( player.horizontalShootingDirection == 0 || player.horizontalShootingDirection == 1 || player.verticalShootingDirection == 0 || player.verticalShootingDirection == 1)
            {
                bullets[i].x = player.x;
                bullets[i].y = player.y;
            }

            // Set bullet starting location and direction
            if(player.horizontalShootingDirection == 0) //shooting right
            {
                bullets[i].x = player.x + 5;
                bullets[i].dir_horizontal = 0;
            }
            if(player.horizontalShootingDirection == 1) //shooting left
            {
                bullets[i].x = player.x - 5;
                bullets[i].dir_horizontal = 1;
            }
            if(player.verticalShootingDirection == 0) //shooting up
            {
                bullets[i].y = player.y - 5;
                bullets[i].dir_vertical = 0;
            }
            if(player.verticalShootingDirection == 1) //shooting down
            {
                bullets[i].y = player.y + 5;
                bullets[i].dir_vertical = 1;
            }
            move_sprite (bullets[i].spriteIndex, bullets[i].x, bullets[i].y);
            break;
        }
    }
}


// export PATH=$PATH:/opt/gbdk/bin
// lcc -o game.gb main.c sprites.c background.c

/*
resolution: 160×144 pixels
x offset: 8 (so left edge of the screen is 0 + 8)
y offset: 16 (so upper edge of the screen is 0 + 16)
*/