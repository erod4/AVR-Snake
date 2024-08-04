#ifndef PLAY_H
#define PLAY_H

#include <stdbool.h>
#include <avr/io.h>
#include "state_machine.h"

#define MAX_SNAKE_LENGTH 100
#define STARTING_SNAKE_LENGTH 5
#define STARTING_SNAKE_LEVEL 1
#define STARTING_SNAKE_SPEED 1
#define STARTING_SNAKE_SCORE 0
#define BOARD_WIDTH 16
#define BOARD_HEIGHT 2

typedef struct
{
    uint8_t x;
    uint8_t y;
} Point;

typedef struct
{
    Point segments[MAX_SNAKE_LENGTH];
    uint8_t length;
    PlayState direction;
    uint8_t level;
    uint16_t score;
    uint8_t speed;
} Snake;

/**
 * Initialize snake
 * @param snake, snake object to initialize
 */
void init_snake(Snake *snake);

/**
 * Checks for collision
 * @param  snake, snake object to check for collision
 * @return true if collision has occured, otherwise retur false
 */
bool hasCollided(Snake *snake);

/**
 * Timer 1 moves snake every 200ms
 */
void timer_init(void);

/**
 *
 */
void move_snake(Snake *snake);

/**
 *
 */
void place_food(Snake *snake, Point *food);

/**
 *
 */
bool hasScored(Snake *snake, Point *food);

/**
 *
 */
void update_speed(uint8_t speed);
#endif
