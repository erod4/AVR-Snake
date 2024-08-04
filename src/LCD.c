#include <avr/io.h>
#include <u8x8_avr.h>
#include <u8g2.h>
#include <stdio.h>
#include "LCD.h"
#include "play.h"

#define SSD1309_ADDR 0x78
u8g2_t u8g2;

void LCD_init(void)
{
    u8g2_Setup_ssd1309_i2c_128x64_noname0_f(&u8g2, U8G2_R0, u8x8_byte_avr_hw_i2c, u8x8_avr_delay);
    u8g2_SetI2CAddress(&u8g2, SSD1309_ADDR);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);
}

void LCD_draw_text(uint8_t x, uint8_t y, const char *str)
{
    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_5x8_mf);
    u8g2_SetFontRefHeightText(&u8g2);
    u8g2_SetFontPosTop(&u8g2);
    u8g2_DrawStr(&u8g2, x, y, str);
    u8g2_SendBuffer(&u8g2);
}
void LCD_draw_snake(Snake *snake, Point *food)
{
    u8g2_ClearBuffer(&u8g2);
    for (uint8_t i = 0; i < snake->length; i++)
    {
        u8g2_DrawBox(&u8g2, snake->segments[i].x * 1, snake->segments[i].y * 1, 1, 1); // Each segment is 8x8 pixels
    }
    u8g2_DrawBox(&u8g2, food->x, food->y, 1, 1);
    LCD_draw_score(snake);
    u8g2_SendBuffer(&u8g2);
}
void LCD_draw_score(Snake *snake)
{
    char score_str[16];
    snprintf(score_str, sizeof(score_str), "Score: %u", snake->score);
    char lvl_str[16];
    snprintf(lvl_str, sizeof(lvl_str), "Level: %u", snake->level);
    u8g2_DrawBox(&u8g2, 0, 58, 128, 1);
    u8g2_SetFont(&u8g2, u8g2_font_u8glib_4_tf);
    u8g2_SetFontRefHeightText(&u8g2);
    u8g2_SetFontPosTop(&u8g2);
    u8g2_DrawStr(&u8g2, 0, 59, score_str);
    u8g2_DrawStr(&u8g2, 100, 59, lvl_str);
}
void LCD_draw_menu(void)
{
    u8g2_ClearBuffer(&u8g2);

    u8g2_DrawFrame(&u8g2, 0, 0, 128, 64);
    u8g2_SetFont(&u8g2, u8g2_font_5x8_mf);
    u8g2_SetFontRefHeightText(&u8g2);
    u8g2_SetFontPosTop(&u8g2);

    const char *title = "Snake Game Menu";
    uint8_t title_width = u8g2_GetStrWidth(&u8g2, title);
    u8g2_DrawStr(&u8g2, (128 - title_width) / 2, 15, title);

    const char *subtitle = "Press START to begin";
    uint8_t subtitle_width = u8g2_GetStrWidth(&u8g2, subtitle);
    u8g2_DrawStr(&u8g2, (128 - subtitle_width) / 2, 35, subtitle);

    u8g2_SendBuffer(&u8g2);
}

void LCD_draw_end_game(Snake *snake)
{
    u8g2_ClearBuffer(&u8g2);

    u8g2_DrawFrame(&u8g2, 0, 0, 128, 64);
    u8g2_SetFont(&u8g2, u8g2_font_5x8_mf);
    u8g2_SetFontRefHeightText(&u8g2);
    u8g2_SetFontPosTop(&u8g2);

    const char *game_over = "Game Over";
    uint8_t game_over_width = u8g2_GetStrWidth(&u8g2, game_over);
    u8g2_DrawStr(&u8g2, (128 - game_over_width) / 2, 15, game_over);
    char score_str[16];
    snprintf(score_str, sizeof(score_str), "Score: %u", snake->score);
    uint8_t score_width = u8g2_GetStrWidth(&u8g2, score_str);
    u8g2_DrawStr(&u8g2, (128 - score_width) / 2, 35, score_str);

    const char *credits = "Credits: Enrique R";
    uint8_t credits_width = u8g2_GetStrWidth(&u8g2, credits);
    u8g2_DrawStr(&u8g2, (128 - credits_width) / 2, 50, credits);

    u8g2_SendBuffer(&u8g2);
}

void LCD_draw_paused(void)
{
    u8g2_ClearBuffer(&u8g2);

    u8g2_DrawFrame(&u8g2, 0, 0, 128, 64);
    u8g2_SetFont(&u8g2, u8g2_font_5x8_mf);
    u8g2_SetFontRefHeightText(&u8g2);
    u8g2_SetFontPosTop(&u8g2);

    const char *paused = "Game Paused";
    uint8_t paused_width = u8g2_GetStrWidth(&u8g2, paused);
    u8g2_DrawStr(&u8g2, (128 - paused_width) / 2, 15, paused);

    const char *resume = "Press START to resume";
    uint8_t resume_width = u8g2_GetStrWidth(&u8g2, resume);
    u8g2_DrawStr(&u8g2, (128 - resume_width) / 2, 35, resume);

    u8g2_SendBuffer(&u8g2);
}

void LCD_draw_resume(void)
{
    u8g2_ClearBuffer(&u8g2);

    u8g2_DrawFrame(&u8g2, 0, 0, 128, 64);
    u8g2_SetFont(&u8g2, u8g2_font_5x8_mf);
    u8g2_SetFontRefHeightText(&u8g2);
    u8g2_SetFontPosTop(&u8g2);

    const char *resuming = "Resuming Game...";
    uint8_t resuming_width = u8g2_GetStrWidth(&u8g2, resuming);
    u8g2_DrawStr(&u8g2, (128 - resuming_width) / 2, 32, resuming);

    u8g2_SendBuffer(&u8g2);
}