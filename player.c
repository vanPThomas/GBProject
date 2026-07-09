#include "player.h"

void move_player(Player *player, uint8_t joy)
{
    if ((joy & J_RIGHT) || (joy & J_LEFT) || (joy & J_UP) || (joy & J_DOWN))
    {
        player->verticalShootingDirection = 2;
        player->horizontalShootingDirection = 2;
    }

    if (joy & J_RIGHT)
    {
        player->x++;

        player->facingLeft = 0;
        player->horizontalShootingDirection = 0;
    }
    if (joy & J_LEFT)
    {
        player->x--;
        player->facingLeft = 1;
        player->horizontalShootingDirection = 1;
    }
    if (joy & J_UP)
    {
        player->y--;
        player->verticalShootingDirection = 0;
    }
    if (joy & J_DOWN)
    {
        player->y++;
        player->verticalShootingDirection = 1;
    }
}

void clamp_player_location(Player *player)
{
    // clamp player to screen
    if (player->x < 16) player->x = 16;
    if (player->x > 152) player->x = 152;
    if (player->y < 32) player->y = 32;
    if (player->y > 144) player->y = 144;
}

void update_player_location(Player player)
{
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
}
