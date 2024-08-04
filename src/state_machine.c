#include "state_machine.h"
#include "buttons.h"
#include "play.h"
#include "LCD.h"
#include <avr/interrupt.h>
// FSM states
static GameState gameState;
static Point food;
static Snake snake;

void fsm_init(void)
{
    gameState = MENU;
    LCD_draw_menu();
}

void fsm_update(void)
{
    switch (gameState)
    {
    case MENU:
        if (isButtonStateSet(START_BUTTON_POS))
        {
            clearButtonStates();
            init_snake(&snake);
            place_food(&snake, &food);
            gameState = PLAY;
        }
        break;

    case PLAY:

        if (isButtonStateSet(START_BUTTON_POS))
        {
            clearButtonStates();

            gameState = PAUSE_GAME;
            break;
            // store last play state
        }
        if (isButtonStateSet(RIGHT_BUTTON_POS))
        {
            clearButtonStates();
            snake.direction = MOVING_RIGHT;
            break;
        }
        if (isButtonStateSet(LEFT_BUTTON_POS))
        {
            clearButtonStates();
            snake.direction = MOVING_LEFT;
            break;
        }
        if (isButtonStateSet(DOWN_BUTTON_POS))
        {
            clearButtonStates();
            snake.direction = MOVING_DOWN;
            break;
        }
        if (isButtonStateSet(UP_BUTTON_POS))
        {
            snake.direction = MOVING_UP;
            clearButtonStates();
            break;
        }

        break;
    case PAUSE_GAME:
        LCD_draw_paused();
        if (isButtonStateSet(START_BUTTON_POS))

        {
            clearButtonStates();

            LCD_draw_resume();
            gameState = PLAY;
        }
        if (isButtonStateSet(MENU_BUTTON_POS))
        {
            clearButtonStates();

            LCD_draw_menu();
            gameState = MENU;
        }
        break;
    case END_GAME:
        LCD_draw_end_game(&snake);

        if (isButtonStateSet(MENU_BUTTON_POS))
        {
            clearButtonStates();
            LCD_draw_menu();
            gameState = MENU;
            // reset snake
        }
        break;
    default:
        break;
    }
}

GameState getState(void)
{
    return gameState;
}

ISR(TIMER1_COMPA_vect)
{
    if (gameState == PLAY)
    {
        move_snake(&snake);
        if (hasCollided(&snake))
        {
            gameState = END_GAME;
        }
        else if (hasScored(&snake, &food))
        {
            snake.length += 2;
            snake.score += 3;
            snake.level++;
            place_food(&snake, &food);
        }
        else
        {
            LCD_draw_snake(&snake, &food);
        }
    }
}