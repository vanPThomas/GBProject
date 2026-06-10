#include <gb/gb.h>
#include <stdio.h>

unsigned char SimpleSprite[] =
{
  0x3C,0x3C,0x3C,0x66,0xFF,0xFF,0xFF,0xBD,
  0xFF,0xBD,0xFF,0xFF,0x3C,0x66,0x3C,0x3C
};

//player start location
uint8_t player_x = 84;
uint8_t player_y = 88;

void main (void)
{
    // set up graphics
    DISPLAY_ON;
    SHOW_SPRITES;

    set_sprite_data(0,1,SimpleSprite);  // load sprite into vram
    set_sprite_tile(0,0);               // sprite 0 uses tile 0

    move_sprite(0,player_x, player_y);  //initial position

    while (1)
    {
        uint8_t joy = joypad(); // read curent dpad and button state

        //move left
        if (joy & J_RIGHT)
            player_x++;
        if (joy & J_LEFT)
            player_x--;
        if (joy & J_DOWN)
            player_y++;
        if (joy & J_UP)
            player_y--;

        // clamp player to screen
        if (player_x < 8) player_x = 8;
        if (player_x > 160) player_x = 160;
        if (player_y < 16) player_y = 16;
        if (player_y > 152) player_y = 152;

        // update sprite position
        move_sprite (0, player_x, player_y);

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