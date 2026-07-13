#include <gb/gb.h>
#include "enemy.h"

Enemy enemies[MAX_ENEMIES];

void init_enemies(void)
{
    for (uint8_t i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].x = 0;
        enemies[i].y = 0;
        enemies[i].health = 2;           // example
        enemies[i].damage = 1;
        enemies[i].active = 0;
        enemies[i].spriteIndex = 5 + i;  // use sprite slots 5,6,7,...
    }
}

void update_enemies(void)
{
    for (uint8_t i = 0; i < MAX_ENEMIES; i++)
    {
        if (enemies[i].active)
        {
            // TODO: move enemy, shoot, etc.
            move_sprite(enemies[i].spriteIndex, enemies[i].x, enemies[i].y);
        }
    }
}