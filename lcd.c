#include "lcd.h"

static void lcd_enable(void)
{
	LCD_OUT |= (1 << LCD_EN);
	LCD_DELAY_US(LCD_DELAY_US_ENABLE);
	LCD_OUT &= ~(1 << LCD_EN);
}

static void lcd_out(uint8_t data)
{
	data &= 0xF0;
	LCD_OUT &= ~(0xF0 >> (4 - LCD_DB));
	LCD_OUT |= (data >> (4 - LCD_DB));
	lcd_enable();
}

void lcd_init(void)
{
	uint8_t pins = (0x0F << LCD_DB) | (1 << LCD_RS) | (1 << LCD_EN);
	LCD_DIR |= pins;
	LCD_OUT &= ~pins;
	LCD_DELAY_MS(LCD_DELAY_MS_BOOTUP);
	lcd_out(LCD_SOFT_RESET);
	LCD_DELAY_MS(LCD_DELAY_MS_RESET_1);
	lcd_enable();
	LCD_DELAY_MS(LCD_DELAY_MS_RESET_2);
	lcd_enable();
	LCD_DELAY_MS(LCD_DELAY_MS_RESET_3);
	lcd_out(LCD_SET_FUNCTION | LCD_FUNCTION_4BIT);
	LCD_DELAY_MS(LCD_DELAY_MS_4BIT);
	lcd_command(LCD_SET_FUNCTION | LCD_FUNCTION_4BIT |
		LCD_FUNCTION_2LINE | LCD_FUNCTION_5X7);
	lcd_command(LCD_SET_DISPLAY | LCD_DISPLAY_ON |
		LCD_CURSOR_OFF | LCD_BLINKING_OFF);
	lcd_command(LCD_SET_ENTRY | LCD_ENTRY_INCREASE |
		LCD_ENTRY_NOSHIFT);
	lcd_clear();
}

void lcd_data(uint8_t data)
{
	LCD_OUT |= (1 << LCD_RS);
	lcd_out(data);
	lcd_out(data << 4);
	LCD_DELAY_US(LCD_DELAY_US_DATA);
}

void lcd_command(uint8_t data)
{
	LCD_OUT &= ~(1 << LCD_RS);
	lcd_out(data);
	lcd_out(data << 4);
	LCD_DELAY_US(LCD_DELAY_US_COMMAND);
}

void lcd_home(void)
{
	lcd_command(LCD_CURSOR_HOME);
	LCD_DELAY_MS(LCD_DELAY_MS_HOME);
}

void lcd_clear(void)
{
	lcd_command(LCD_CLEAR_DISPLAY);
	LCD_DELAY_MS(LCD_DELAY_MS_CLEAR);
}

void lcd_cursor(uint8_t x, uint8_t y)
{
	uint8_t pos = LCD_SET_DDADR + x;
	if(y == 1) { pos += LCD_OFFSET_SECOND_ROW; }
	lcd_command(pos);
}

void lcd_string(const uint8_t *s)
{
	char c;
	for(; (c = *s); ++s) { lcd_data(c); }
}

void lcd_custom_char(uint8_t addr, const uint8_t *data)
{
	uint8_t i;
	lcd_command(LCD_SET_CGADR | (addr << 0x03));
	for(i = 0; i < 8; ++i) { lcd_data(data[i]); }
	lcd_command(LCD_SET_DDADR);
}

#if defined(AVR) && AVR == 1

void lcd_string_P(const uint8_t *s)
{
	char c;
	for(; (c = pgm_read_byte(s)); ++s) { lcd_data(c); }
}

void lcd_custom_char_P(uint8_t addr, const uint8_t *data)
{
	uint8_t i;
	lcd_command(LCD_SET_CGADR | (addr << 0x03));
	for(i = 0; i < 8; ++i) { lcd_data(pgm_read_byte(data + i)); }
	lcd_command(LCD_SET_DDADR);
}

#endif /* AVR */


