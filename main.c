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
    init_bullets();
    init_player();

    // Initialize three enemies
    init_enemies();

    move_sprite(0, player.x, player.y);  //initial position

    // This sets bullet firing rate
    uint8_t bulletFrameCounter = 0;
    const uint8_t firingRateFrames = 20;

    // Give enemies start positions
    activate_enemies();

    // Main Loop
    while (1)
    {
        
        // Player is Enemy's target
        set_enemy_target_player();

        for (uint8_t i = 0; i < MAX_ENEMIES; i++)
        {
            if(enemies[i].running_frame_counter >= enemies[i].running_speed)
            {
                enemies[i].running_frame_counter = 0;
                move_enemy(i);
            }
        }        

        // draw enemies on the screen
        draw_enemies();
        
        // check if player is actually alive
        if (player.lives < 1)
        {
            printf("Game Over");
            break;
        }

        // Draw lives and score
        draw_number(7, 0, player.score);
        draw_number(17, 0, player.lives);

        
        if (bulletFrameCounter > 0) bulletFrameCounter++;
        if (bulletFrameCounter >= firingRateFrames) bulletFrameCounter = 0;

        uint8_t joy = joypad(); // read curent dpad and button state

        //========== Player Movement ==========
        move_player(joy);

        clamp_player_location();

        // ========== Shooting ==========
        // detect if player shot
        if ((joy & J_A) && bulletFrameCounter == 0)
        {
            bulletFrameCounter++;
            // find fist inactive bullet in bullet list and have the player fire it.
            find_first_inactive_bullet(player);
        }

        
        for (uint8_t j = 0; j < 3; j++)
        {
            for (uint8_t i = 0; i < 3; i++)
            {
                if (enemies[i].active == 1 && check_collision(bullets[j].x, bullets[j].y, enemies[i].x, enemies[i].y) == 1)
                {
                    enemies[i].health--;
                    reset_bullet(j);

                    if (enemies[i].health <= 0)
                    {
                        reset_enemy(i);
                        player.score++;
                    }
                }
            }
        }
        update_and_print_bullet_location();

        update_player_location();
        
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