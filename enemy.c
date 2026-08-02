#include <gb/gb.h>
#include "enemy.h"
#include "utils.h"


Enemy enemies[MAX_ENEMIES];

void init_enemies(void)
{
    for (uint8_t i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].x = 0;
        enemies[i].y = 0;
        enemies[i].health = 3;
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

void activate_enemies(void)
{
    enemies[0].x = generate_random_number_between(20, 140);
    enemies[0].y = generate_random_number_between(20, 124);
    enemies[0].active = 1;
    enemies[1].x = generate_random_number_between(20, 140);
    enemies[1].y = generate_random_number_between(20, 124);
    enemies[1].active = 1;
    enemies[2].x = generate_random_number_between(20, 140);
    enemies[2].y = generate_random_number_between(20, 124);
    enemies[2].active = 1;
}

void draw_enemies(void)
{
    move_sprite(5, enemies[0].x, enemies[0].y);
    move_sprite(6, enemies[1].x, enemies[1].y);
    move_sprite(7, enemies[2].x, enemies[2].y);
}