/*
 * fonts.c
 *
 *  Created on: 23 maj 2021
 *      Author: bartool
 */

//#include "main.h"
#include "fonts.h"
#include "SSD1306_oled.h"

uint8_t font_print_str(const FONT_INFO * font, uint8_t * text, uint8_t pos_x, uint8_t pos_y, uint8_t mode)
{
	uint8_t height = font->heightPixels;

	uint8_t x = pos_x;

	uint8_t width = font_string_lenght_px(font, text);

	switch (mode) {
		case INVERSE:
			SSD1306_clear_buffer(width+2, height+2, pos_x-1, pos_y-1, WHITE);
			break;
		default:
			SSD1306_clear_buffer(width+2, height+2, pos_x-1, pos_y-1, BLACK);
			break;
	}

	while(*text)
	{
		uint8_t actual_char = *text++;
		if (actual_char < ' ' || actual_char > 126)
		{
			continue;
		}

		uint8_t char_nr = actual_char - font->startChar;
		const FONT_CHAR_INFO *charinfo =  &font->charInfo[char_nr];

		SSD1306_write_to_buffer(font->data + charinfo->offset, charinfo->widthBits, height, x, pos_y, mode);

		x += charinfo->widthBits + font->interspacePixels;
	}

	return x;
}

uint8_t font_string_lenght_px(const FONT_INFO * font, uint8_t * text)
{
	uint8_t x;
	while(*text)
	{
		uint8_t actual_char = *text++;
		uint8_t char_nr = actual_char - font->startChar;
		if (actual_char < ' ' || actual_char > 126) {
			continue;
		}
		
		x += font->charInfo[char_nr].widthBits + font->interspacePixels;
	}
	return x;
}
