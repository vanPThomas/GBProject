#include "bullet.h"

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
