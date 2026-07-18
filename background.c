#include "background.h"

void set_background_data(void)
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

    set_bkg_data (20, 1, char0);
    set_bkg_data (21, 1, char1);
    set_bkg_data (22, 1, char2);
    set_bkg_data (23, 1, char3);
    set_bkg_data (24, 1, char4);
    set_bkg_data (25, 1, char5);
    set_bkg_data (26, 1, char6);
    set_bkg_data (27, 1, char7);
    set_bkg_data (28, 1, char8);
    set_bkg_data (29, 1, char9);
}

void fill_background(void)
{
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

    set_sprite_data (3, 1, EnemySprite);
    set_sprite_tile (5, 3);
    set_sprite_tile (6, 3);
    set_sprite_tile (7, 3);
    
}