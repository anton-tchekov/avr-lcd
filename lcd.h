#ifndef __LCD_H__
#define __LCD_H__

#define AVR                     1

#include <stdint.h>

#define LCD_DELAY_US_ENABLE    20
#define LCD_DELAY_US_DATA      46
#define LCD_DELAY_US_COMMAND   42

#define LCD_DELAY_MS_BOOTUP    15
#define LCD_DELAY_MS_RESET_1    5
#define LCD_DELAY_MS_RESET_2    1
#define LCD_DELAY_MS_RESET_3    1
#define LCD_DELAY_MS_4BIT       5
#define LCD_DELAY_MS_HOME       2
#define LCD_DELAY_MS_CLEAR      2

/* Clear Display                00000001 */
#define LCD_CLEAR_DISPLAY       0x01

/* Cursor Home                  0000001x */
#define LCD_CURSOR_HOME         0x02

/* Set Entry Mode               000001xx */
#define LCD_SET_ENTRY           0x04

#define LCD_ENTRY_DECREASE      0x00
#define LCD_ENTRY_INCREASE      0x02
#define LCD_ENTRY_NOSHIFT       0x00
#define LCD_ENTRY_SHIFT         0x01

/* Set Display                  00001xxx */
#define LCD_SET_DISPLAY         0x08

#define LCD_DISPLAY_OFF         0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_CURSOR_ON           0x02
#define LCD_BLINKING_OFF        0x00
#define LCD_BLINKING_ON         0x01

/* Set Shift                    0001xxxx */
#define LCD_SET_SHIFT           0x10

#define LCD_CURSOR_MOVE         0x00
#define LCD_DISPLAY_SHIFT       0x08
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x04

/* Set Function                 001xxxxx */
#define LCD_SET_FUNCTION        0x20

#define LCD_FUNCTION_4BIT       0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_2LINE      0x08
#define LCD_FUNCTION_5X7        0x00
#define LCD_FUNCTION_5X10       0x04

#define LCD_SOFT_RESET          0x30

/* Set CGRAM Address            01xxxxxx (Character Generator RAM) */
#define LCD_SET_CGADR           0x40

/* Set DDRAM Address            1xxxxxxx (Display Data RAM) */
#define LCD_SET_DDADR           0x80

#define LCD_OFFSET_SECOND_ROW   0x40

#if defined(PROPELLER) && PROPELLER == 1

#include <propeller.h>

#define LCD_DELAY_MS(n)          waitcnt(CNT + (CLKFREQ / 1000) * (n))
#define LCD_DELAY_US(n)          waitcnt(CNT + (CLKFREQ / 1000000) * (n))

#define LCD_OUT                  OUTA
#define LCD_DIR                  DIRA
#define LCD_DB                  4
#define LCD_RS                  2
#define LCD_EN                  3

#elif defined(AVR) && AVR == 1

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define LCD_DELAY_US(n)          _delay_us(n)
#define LCD_DELAY_MS(n)          _delay_ms(n)

/*
LCD PORT(C)
	+--+--+--+--+--+--+
	|0 |1 |2 |3 |4 |5 |
	+--+--+--+--+--+--+
	|D4|D5|D6|D7|RS|EN|
	+--+--+--+--+--+--+
*/

#define LCD_OUT                  PORTC
#define LCD_DIR                  DDRC
#define LCD_DB                  0
#define LCD_RS                  4
#define LCD_EN                  5

void lcd_string_P(const uint8_t *s);
void lcd_custom_char_P(uint8_t addr, const uint8_t *data);

#endif

void lcd_init(void);
void lcd_data(uint8_t data);
void lcd_command(uint8_t data);
void lcd_home(void);
void lcd_clear(void);
void lcd_cursor(uint8_t x, uint8_t y);
void lcd_string(const uint8_t *s);
void lcd_custom_char(uint8_t addr, const uint8_t *data);

#endif
