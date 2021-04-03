#include "lcd.h"

uint8_t chrdata0[8] =
{
	0b00000000,
	0b00000000,
	0b00001010, /*  X X  */
	0b00011111, /* XXXXX */
	0b00001110, /*  XXX  */
	0b00010100, /*   X   */
	0b00000000,
	0b00000000
};

int main(void)
{
	lcd_init();
	lcd_custom_char(0, chrdata0);

	lcd_data('T');
	lcd_data('e');
	lcd_data('s');
	lcd_data('t');

	lcd_cursor(0, 1);
	lcd_string((uint8_t *)"Hello World!");

	lcd_cursor(15, 1);
	lcd_data(0);

	while(1)
	{
		
	}

	return 0;
}
