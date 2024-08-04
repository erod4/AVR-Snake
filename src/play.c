#include <stdbool.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "play.h"
#include "state_machine.h"
#include "LCD.h"
void init_snake(Snake *snake)
{
    snake->direction = MOVING_RIGHT;
    snake->length = STARTING_SNAKE_LENGTH;
    snake->level = STARTING_SNAKE_LEVEL;
    snake->score = STARTING_SNAKE_SCORE;
    for (uint8_t i = 0; i < snake->length; i++)
    {
        snake->segments[i] = (Point){STARTING_SNAKE_LENGTH - 1 - i, 1}; // Initializes snake segments from right to left
    }
}

bool hasCollided(Snake *snake)
{
    // Check boundary collisions
    if (snake->segments[0].x < 0 || snake->segments[0].x > 128 ||
        snake->segments[0].y < 0 || snake->segments[0].y > 58)
    {
        LCD_draw_text(0, 0, "Collided in boundaery");

        return true;
    }

    // Check self-collisions
    for (uint8_t i = 1; i < snake->length; i++)
    {
        if (snake->segments[0].x == snake->segments[i].x &&
            snake->segments[0].y == snake->segments[i].y)
        {
            LCD_draw_text(0, 0, "Collided in for");

            return true;
        }
    }

    return false;
}
void timer_init(void)
{
    // Configure Timer1 with CTC mode and a suitable prescaler
    TCCR1B |= (1 << WGM12); // CTC mode
    TCCR1B |= (1 << CS12);  // Prescaler 256

    // Calculate and set OCR1A for a 200ms interval (assuming 16MHz clock)
    OCR1A = 8000;

    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}
void move_snake(Snake *snake)
{
    // Shift the segments
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->segments[i] = snake->segments[i - 1];
    }

    // Update the head based on the current direction
    switch (snake->direction)
    {
    case MOVING_UP:
        snake->segments[0].y--;
        break;
    case MOVING_DOWN:
        snake->segments[0].y++;
        break;
    case MOVING_LEFT:
        snake->segments[0].x--;
        break;
    case MOVING_RIGHT:
        snake->segments[0].x++;
        break;
    }
}
void place_food(Snake *snake, Point *food)
{
    bool isValidPosition = false;

    while (!isValidPosition)
    {
        food->x = rand() % 129;
        food->y = rand() % 60;
        isValidPosition = true;
        for (uint8_t i = 0; i < snake->length; i++)
        {
            if (snake->segments[i].x == food->x && snake->segments[i].y == food->y)
            {
                isValidPosition = false;
                break;
            }
        }
    }
}

bool hasScored(Snake *snake, Point *food)
{
    return snake->segments[0].x == food->x && snake->segments[0].y == food->y;
}
void update_speed(uint8_t level)
{
    uint16_t base_interval = 8000; // 200ms
    uint16_t min_interval = 3000;  // Minimum interval to prevent too fast speed

    uint16_t new_interval = base_interval - (level * base_interval / 10);
    if (new_interval < min_interval)
    {
        new_interval = min_interval;
    }
}