#ifndef ENEMY_H
#define ENEMY_H

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t health;
    uint8_t damage;
    uint8_t active;                    // 0 = dead/inactive, 1 = alive
    uint8_t spriteIndex;               // e.g. 5,6,7 for enemy sprites
} Enemy;

#define MAX_ENEMIES 5

extern Enemy enemies[MAX_ENEMIES];

void init_enemies(void);
void update_enemies(void);

#endif