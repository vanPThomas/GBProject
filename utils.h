#ifndef UTILS_H
#define UTILS_H

extern unsigned int seed;


// uint8_t random_between(uint8_t min, uint8_t max);
void generate_randseed(void);

uint8_t check_collision(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
uint8_t generate_random_uint8_t_number(void);

#endif