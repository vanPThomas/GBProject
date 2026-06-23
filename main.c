#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "sprites.h"

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t dir_horizontal;   // 0=right, 1=left, 2=none
    uint8_t dir_vertical;     // 0=up, 1=down, 2=none
    uint8_t active;
    uint8_t spriteIndex;
} Bullet;

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

void main (void)
{
    // Set up background data
    set_bkg_data(0, 1, FloorTile); // Tile 0 = floor
    // Parameters explained:
    //   0  = Start loading at background tile index #0 in VRAM
    //   1  = Load 1 tile (we're only loading one floor tile)
    //   FloorTile = Pointer to the raw pixel data (16 bytes)
    set_bkg_data(1, 1, WallTile); // Tile 1 = wall
    //   1  = Start loading at background tile index #1 in VRAM
    //   1  = Load 1 tile
    //   WallTile = The wall graphic data
    // Second number is to reduce the lines of code but less readable. 1 is fine.
    set_bkg_data(2, 1, S_char);
    set_bkg_data(3, 1, C_char);
    set_bkg_data(4, 1, O_char);
    set_bkg_data(5, 1, R_char);
    set_bkg_data(6, 1, E_char);
    set_bkg_data(7, 1, colon_char);

    set_bkg_data (8, 1, L_char);
    set_bkg_data (9, 1, I_char);
    set_bkg_data (10, 1, V_char);

    // Fill Screen with floor tiles
    fill_bkg_rect(0, 0, 20, 18, 0);

    for (uint8_t x = 0; x < 20; x++)
    {
        set_bkg_tile_xy(x, 1, 1); // Top wall
        set_bkg_tile_xy(x, 17, 1); // Bottom Wall
        // very simple varriable: (x-coordinate on grid, y-coord, bkg tile index)
    }
    for (uint8_t y = 1; y < 18; y++)
    {
        set_bkg_tile_xy(0, y, 1); // Left Wall
        set_bkg_tile_xy(19, y, 1); // Right wall
    }
    set_bkg_tile_xy(0, 0, 2); // S
    set_bkg_tile_xy(1, 0, 3); // C
    set_bkg_tile_xy(2, 0, 4); // O
    set_bkg_tile_xy(3, 0, 5); // R
    set_bkg_tile_xy(4, 0, 6); // E
    set_bkg_tile_xy(5, 0, 7); // :

    set_bkg_tile_xy(11, 0, 8); // L
    set_bkg_tile_xy(12, 0, 9); // I
    set_bkg_tile_xy(13, 0, 10); // V
    set_bkg_tile_xy(14, 0, 6); // E
    set_bkg_tile_xy(15, 0, 2); // S
    set_bkg_tile_xy(16, 0, 7); // :

    // set up graphics
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;

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
    
    Bullet bullet1 = {0, 0, 2, 2, 0, 2};
    Bullet bullet2 = {0, 0, 2, 2, 0, 3};
    Bullet bullet3 = {0, 0, 2, 2, 0, 4};
    Player player = {84, 84, 1, 0, 3, 0, 2, 2};
    
    move_sprite(0,player.x, player.y);  //initial position

    Bullet bullets[3] = {bullet1, bullet2, bullet3};   // Creates 3 bullets
    uint8_t bulletFrameCounter = 0;
    const uint8_t firingRateFrames = 20;

    // Main Loop
    while (1)
    {
        if (bulletFrameCounter > 0) bulletFrameCounter++;
        if (bulletFrameCounter >= firingRateFrames) bulletFrameCounter = 0;

        uint8_t joy = joypad(); // read curent dpad and button state

        //========== Player Movement ==========
        if ((joy & J_RIGHT) || (joy & J_LEFT) || (joy & J_UP) || (joy & J_DOWN))
        {
            player.verticalShootingDirection = 2;
            player.horizontalShootingDirection = 2;
        }

        //move left
        if (joy & J_RIGHT)
        {
            player.x++;
            player.facingLeft = 0;
            player.horizontalShootingDirection = 0;
        }
        if (joy & J_LEFT)
        {
            player.x--;
            player.facingLeft = 1;
            player.horizontalShootingDirection = 1;
        }
        if (joy & J_UP)
        {
            player.y--;
            player.verticalShootingDirection = 0;
        }
        if (joy & J_DOWN)
        {
            player.y++;
            player.verticalShootingDirection = 1;
        }

        // clamp player to screen
        if (player.x < 16) player.x = 16;
        if (player.x > 152) player.x = 152;
        if (player.y < 32) player.y = 32;
        if (player.y > 144) player.y = 144;

        // ========== Shooting ==========
        // detect if player shot
        if ((joy & J_A) && bulletFrameCounter == 0)
        {
            bulletFrameCounter++;
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

        // update player sprite position
        if(player.facingLeft == 1)
        {
            move_sprite (0, player.x, player.y);
            move_sprite (1, 0, 0);
        }
        else
        {
            move_sprite (1, player.x, player.y);
            move_sprite (0, 0, 0);
        }

        wait_vbl_done(); // Wait for next frame
    }
}

// export PATH=$PATH:/opt/gbdk/bin
// lcc -o game.gb main.c sprites.c

/*
resolution: 160×144 pixels
x offset: 8 (so left edge of the screen is 0 + 8)
y offset: 16 (so upper edge of the screen is 0 + 16)
*/