#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum
{
    MENU,
    PLAY,
    PAUSE_GAME,
    END_GAME
} GameState;
typedef enum
{
    MOVING_UP,
    MOVING_DOWN,
    MOVING_LEFT,
    MOVING_RIGHT
} PlayState;

/**
 * Init state machine logic
 */
void fsm_init(void);

/**
 * update state
 */
void fsm_update(void);

/**
 * Returns current state
 */
GameState getState(void);
#endif