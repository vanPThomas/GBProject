#include <gb/gb.h>
#include "enemy.h"
#include "utils.h"
#include "player.h"


Enemy enemies[MAX_ENEMIES];

// Initialize the list of enemies
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
        enemies[i].target_x = 0;
        enemies[i].target_y = 0;
        enemies[i].running_speed = 3;
        enemies[i].running_frame_counter = 0;
    }
}

// Udate each enemy
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

// Spawn all enemies at random locations
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

// Draw enemy
void draw_enemies(void)
{
    move_sprite(5, enemies[0].x, enemies[0].y);
    move_sprite(6, enemies[1].x, enemies[1].y);
    move_sprite(7, enemies[2].x, enemies[2].y);
}

// Reset enemy location to off screen and put it on non active
void reset_enemy(uint8_t i)
{
    enemies[i].x = 0;
    enemies[i].y = 0;
    enemies[i].active = 0;
}

// Increment enemy x and y location
void move_enemy(uint8_t j)
{

    if(enemies[j].x < enemies[j].target_x)
    {
        enemies[j].x++;
    }
    else
    {
        enemies[j].x--;
    }
    if (enemies[j].y < enemies[j].target_y)
    {
        enemies[j].y++;
    }
    else
    {
        enemies[j].y--;
    }
}

// Set Enemy target as player and increment Running counter
void set_enemy_target_player(void)
{
    for (uint8_t i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i].target_x = player.x;
        enemies[i].target_y = player.y;
        enemies[i].running_frame_counter++;
    }
}

// For each enemy, check if the running counter is triggered, if yes, move the enemy location
void check_if_enemy_should_move_and_move_it(void)
{
    for (uint8_t i = 0; i < MAX_ENEMIES; i++)
    {
        if(enemies[i].running_frame_counter >= enemies[i].running_speed)
        {
            enemies[i].running_frame_counter = 0;
            move_enemy(i);
        }
    }
}