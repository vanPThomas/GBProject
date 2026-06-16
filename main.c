#include <gb/gb.h>
#include <stdio.h>

// === PLAYER SPRITE DATA ===
unsigned char PlayerSpriteLeftFacing[] =
{
  0x00,0x00,0x1C,0x1C,0x62,0x7E,0x14,0x1C,
  0x7C,0x7C,0x08,0x08,0x14,0x14,0x22,0x22
};

unsigned char PlayerSpriteRightFacing[] =
{
  0x00,0x00,0x38,0x38,0x46,0x7E,0x28,0x38,
  0x3E,0x3E,0x10,0x10,0x28,0x28,0x44,0x44
};

// === SIMPLE WALL AND FLOOR TILES ===
unsigned char WallTile[] = {
  0xFF,0xFF,0xFF,0xC3,0xFF,0xA5,0xE7,0x99,
  0xE7,0x99,0xFF,0xA5,0xFF,0xC3,0xFF,0xFF
};

unsigned char FloorTile[] = {
  0x55,0x00,0xAA,0x00,0x55,0x00,0xAA,0x00,
  0x55,0x00,0xAA,0x00,0x55,0x00,0xAA,0x00
};

// unsigned char RocketSpriteLeft[] = {
//   0x00,0x00,0x00,0x01,0x05,0x02,0x7E,0x7D,
//   0x7E,0x7D,0x05,0x02,0x00,0x01,0x00,0x00
// };

// unsigned char RocketSpriteRight[] = {
//   0x00,0x00,0x00,0x80,0xA0,0x40,0x7E,0xBE,
//   0x7E,0xBE,0xA0,0x40,0x00,0x80,0x00,0x00,
// };

// unsigned char RocketSpriteUp[] = {
//   0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,
//   0x18,0x18,0x3C,0x18,0x18,0x24,0x24,0x5A
// };

// unsigned char RocketSpriteDown[] = {
//   0x24,0x5A,0x18,0x24,0x3C,0x18,0x18,0x18,
//   0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00
// };

unsigned char BulletSprite[] = {
  0x00,0x00,0x00,0x00,0x18,0x18,0x24,0x3C,
  0x24,0x3C,0x18,0x18,0x00,0x00,0x00,0x00
};

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t dir_horizontal;   // 0=right, 1=left, 2=none
    uint8_t dir_vertical;     // 0=up, 1=down, 2=none
    uint8_t active;
} Bullet;


//player start location
uint8_t player_x = 84;
uint8_t player_y = 88;

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

    // Fill Screen with floor tiles
    fill_bkg_rect(0, 0, 20, 18, 0);

    for (uint8_t x = 0; x < 20; x++)
    {
        set_bkg_tile_xy(x, 0, 1); // Top wall
        set_bkg_tile_xy(x, 17, 1); // Bottom Wall
        // very simple varriable: (x-coordinate on grid, y-coord, bkg tile index)
    }
    for (uint8_t y = 0; y < 18; y++)
    {
        set_bkg_tile_xy(0, y, 1); // Left Wall
        set_bkg_tile_xy(19, y, 1); // Right wall
    }

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


    move_sprite(0,player_x, player_y);  //initial position

    uint8_t facingLeft = 1;
    uint8_t verticalShootingDirection = 2; // 0 = up, 1 = down, 2 = neither
    uint8_t horizontalShootingDirection = 2; // 0 = right, 1 = left, 2 = neither

    Bullet bullet = {0, 0, 2, 2, 0};

    // Main Loop
    while (1)
    {
        uint8_t joy = joypad(); // read curent dpad and button state

        //========== Player Movement ==========

        if ((joy & J_RIGHT) || (joy & J_LEFT) || (joy & J_UP) || (joy & J_DOWN))
        {
            verticalShootingDirection = 2;
            horizontalShootingDirection = 2;
        }

        //move left
        if (joy & J_RIGHT)
        {
            player_x++;
            facingLeft = 0;
            horizontalShootingDirection = 0;
        }
        if (joy & J_LEFT)
        {
            player_x--;
            facingLeft = 1;
            horizontalShootingDirection = 1;
        }
        if (joy & J_UP)
        {
            player_y--;
            verticalShootingDirection = 0;
        }
        if (joy & J_DOWN)
        {
            player_y++;
            verticalShootingDirection = 1;
        }

        // clamp player to screen
        if (player_x < 16) player_x = 16;
        if (player_x > 152) player_x = 152;
        if (player_y < 24) player_y = 24;
        if (player_y > 144) player_y = 144;

        // ========== Shooting ==========
        // detect if player shot
        if ((joy & J_A) && bullet.active == 0)
        {
            bullet.active = 1;

            bullet.dir_horizontal = 2;
            bullet.dir_vertical = 2;

            if( horizontalShootingDirection == 0 || horizontalShootingDirection == 1 || verticalShootingDirection == 0 || verticalShootingDirection == 1)
            {
                bullet.x = player_x;
                bullet.y = player_y;
            }

            // Set bullet starting location and direction
            if(horizontalShootingDirection == 0) //shooting right
            {
                bullet.x = player_x + 5;
                bullet.dir_horizontal = 0;
            }
            if(horizontalShootingDirection == 1) //shooting left
            {
                bullet.x = player_x - 5;
                bullet.dir_horizontal = 1;
            }
            if(verticalShootingDirection == 0) //shooting up
            {
                bullet.y = player_y - 5;
                bullet.dir_vertical = 0;
            }
            if(verticalShootingDirection == 1) //shooting down
            {
                bullet.y = player_y + 5;
                bullet.dir_vertical = 1;
            }
            move_sprite (2, bullet.x, bullet.y);
        }

        // update bullet 1 location and print
        if (bullet.active)
        {
            if (bullet.dir_horizontal == 0)
            {
                bullet.x += 2;
            }
            if (bullet.dir_horizontal == 1)
            {
                bullet.x -= 2;
            }
            if (bullet.dir_vertical == 0)
            {
                bullet.y -= 2;
            }
            if (bullet.dir_vertical == 1)
            {
                bullet.y += 2;
            }
            move_sprite (2, bullet.x, bullet.y);
            
        }

        // Detect if bullet goes off screen and delete it
        if (bullet.active)
        {
            if (bullet.x < 16 || bullet.x > 152 || bullet.y < 24 || bullet.y > 144)
            {
                bullet.x = 0;
                bullet.y = 0;
                bullet.active = 0;
                bullet.dir_horizontal = 2;
                bullet.dir_vertical = 2;
                move_sprite (2, 0, 0);
            }
        }

        // update player sprite position
        if(facingLeft == 1)
        {
            move_sprite (0, player_x, player_y);
            move_sprite (1, 0, 0);
        }
        else
        {
            move_sprite (1, player_x, player_y);
            move_sprite (0, 0, 0);
        }

        wait_vbl_done(); // Wait for next frame
    }
}

// export PATH=$PATH:/opt/gbdk/bin
// lcc -o game.gb main.c

/*
resolution: 160×144 pixels
x offset: 8 (so left edge of the screen is 0 + 8)
y offset: 16 (so upper edge of the screen is 0 + 16)
*/