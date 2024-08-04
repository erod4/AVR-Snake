#ifndef LCD_H
#define LCD_H
#include <avr/io.h>
#include "play.h"
/**
 * Initializes the LCD display
 */
void LCD_init(void);

/**
 * Draws a string at the specified position on the LCD
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @param str The string to draw
 */
void LCD_draw_text(uint8_t x, uint8_t y, const char *str);

/**
 * Draw snake segments
 * @param snake The snake instance you wish to draw
 */
void LCD_draw_snake(Snake *snake, Point *food);
/**
 *
 */
void LCD_draw_score(Snake *snake);

/**
 *
 */
void LCD_draw_menu(void);

/**
 *
 */
void LCD_draw_end_game(Snake *snake);

/**
 *
 */
void LCD_draw_paused(void);

/**
 *
 */
void LCD_draw_resume(void);

#endif