#include <gb/gb.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "sprites.h"
#include "background.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "utils.h"
#include <rand.h>

void main (void)
{
    
    generate_randseed();

    // set up graphics
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;

    // Prepare background
    set_background_data();    
    fill_background();


    // Prepare sprites
    set_and_index_spriteData();

    // Ready the actual player and bullet varriables
    Bullet bullet1 = {0, 0, 2, 2, 0, 2};
    Bullet bullet2 = {0, 0, 2, 2, 0, 3};
    Bullet bullet3 = {0, 0, 2, 2, 0, 4}; // x, y, horizontal direction, vertical direction, is bullet active, sprite index
    Player player = {84, 84, 1, 0, 3, 0, 2, 2}; // x, y, facing left, score, lives, bullets fired, verical shooting direction, horizontal shooting direction

    // Initialize three enemies
    init_enemies();

    move_sprite(0, player.x, player.y);  //initial position

    Bullet bullets[3] = {bullet1, bullet2, bullet3};   // Creates 3 bullets

    // This sets bullet firing rate
    uint8_t bulletFrameCounter = 0;
    const uint8_t firingRateFrames = 20;

    // Give enemies start positions
    enemies[0].x = generate_random_number_between(20, 140);
    enemies[0].y = generate_random_number_between(20, 124);
    enemies[0].active = 1;
    enemies[1].x = generate_random_number_between(20, 140);
    enemies[1].y = generate_random_number_between(20, 124);
    enemies[1].active = 1;
    enemies[2].x = generate_random_number_between(20, 140);
    enemies[2].y = generate_random_number_between(20, 124);
    enemies[2].active = 1;


    // Main Loop
    while (1)
    {
       
        // draw enemies on the screen
        move_sprite(5, enemies[0].x, enemies[0].y);
        move_sprite(6, enemies[1].x, enemies[1].y);
        move_sprite(7, enemies[2].x, enemies[2].y);
        
        // check if player is actually alive
        if (player.lives < 1)
        {
            printf("Game Over");
            break;
        }

        // Draw lives and score
        player.score = 0;
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

        
        for (uint8_t j = 0; j < 3; j++)
        {
            for (uint8_t i = 0; i < 3; i++)
            {
                if (enemies[i].active == 1 && check_collision(bullets[j].x, bullets[j].y, enemies[i].x, enemies[i].y) == 1)
                {
                    enemies[i].health--;
                    bullets[j].x = 0;
                    bullets[j].y = 0;
                    bullets[j].active = 0;
                    move_sprite (bullets[j].spriteIndex, 0, 0);

                    if (enemies[i].health <= 0)
                    {
                        enemies[i].x = 0;
                        enemies[i].y = 0;
                        enemies[i].active = 0;
                        player.score++;
                    }
                }
            }
        }
        update_and_print_bullet_location(bullets);

        update_player_location(player);
        
        wait_vbl_done(); // Wait for next frame
    }
}


// export PATH=$PATH:/opt/gbdk/bin
// lcc -o game.gb main.c sprites.c background.c player.c bullet.c enemy.c utils.c

/*
resolution: 160×144 pixels
x offset: 8 (so left edge of the screen is 0 + 8)
y offset: 16 (so upper edge of the screen is 0 + 16)
*/