#include "bullet.h"

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

// Find the first useable bullet in the list of fireable bullets
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
