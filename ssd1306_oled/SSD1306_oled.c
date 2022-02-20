/*
 * SSD1306_oled.c
 *
 *  Created on: Apr 5, 2021
 *      Author: bartool
 */

// #include "main.h"
#include "SSD1306_oled.h"
#include "string.h"

I2C_HandleTypeDef *oled_i2c;

#ifdef TEST
uint8_t buffer_oled[SSD1306_BUF_SIZE];
#else
static uint8_t buffer_oled[SSD1306_BUF_SIZE];
#endif

static void SSD1306_SendCommand(uint8_t cmd)
{
	HAL_I2C_Mem_Write(oled_i2c, SSD1306_ADDRESS<<1, 0x00, 1, &cmd, 1, SSD1306_TIMEOUT);
}

static void SSD1306_SendData(uint8_t *data, uint16_t size)
{
	HAL_I2C_Mem_Write(oled_i2c, SSD1306_ADDRESS<<1, 0x40, 1, data, size, SSD1306_TIMEOUT);
}

void SSD1306_clear(uint8_t color)
{
	switch(color)
	{
	case WHITE:
		memset(buffer_oled, 0xFF, SSD1306_BUF_SIZE);
		break;
	case BLACK:
		memset(buffer_oled, 0x00, SSD1306_BUF_SIZE);
		break;
	}
}

void SSD1306_display_all(void)
{
	SSD1306_SendCommand(SSD1306_PAGEADDR);
	SSD1306_SendCommand(0);
	SSD1306_SendCommand(0xFF);
	SSD1306_SendCommand(SSD1306_COLUMNADDR);
	SSD1306_SendCommand(0);
	SSD1306_SendCommand(SSD1306_LCDWIDTH - 1);

	SSD1306_SendData(buffer_oled, SSD1306_BUF_SIZE);
}

uint8_t SSD1306_display_page(void)
{
	static uint8_t page = 0;

	SSD1306_SendCommand(SSD1306_PAGEADDR);
	SSD1306_SendCommand(page);
	SSD1306_SendCommand(page);
	SSD1306_SendCommand(SSD1306_COLUMNADDR);
	SSD1306_SendCommand(0);
	SSD1306_SendCommand(SSD1306_LCDWIDTH - 1);

	SSD1306_SendData(buffer_oled + (page * SSD1306_LCDWIDTH), SSD1306_LCDWIDTH);

	if (++page > 7)
	{
		page = 0;
		return SSD1306_SENDALL;
	}
	else
	{
		return SSD1306_SENDPAGE;
	}
}

void SSD1306_Init(I2C_HandleTypeDef *i2c)
{
	oled_i2c = i2c;
	SSD1306_SendCommand(SSD1306_DISPLAYOFF);
	SSD1306_SendCommand(SSD1306_SETDISPLAYCLOCKDIV);
	SSD1306_SendCommand(0x80);
	SSD1306_SendCommand(SSD1306_SETMULTIPLEX);
	SSD1306_SendCommand(SSD1306_LCDHEIGHT - 1);

	SSD1306_SendCommand(SSD1306_SETDISPLAYOFFSET);
	SSD1306_SendCommand(0x0);
	SSD1306_SendCommand(SSD1306_SETSTARTLINE | 0x0);
	SSD1306_SendCommand(SSD1306_CHARGEPUMP);

	SSD1306_SendCommand(0x14);

	SSD1306_SendCommand(SSD1306_MEMORYMODE);
	SSD1306_SendCommand(0x00);
	SSD1306_SendCommand(SSD1306_SEGREMAP | 0x1);
	SSD1306_SendCommand(SSD1306_COMSCANDEC);

	uint8_t comPins = 0x02;
	uint8_t contrast = 0x8F;

	if ((SSD1306_LCDWIDTH == 128) && (SSD1306_LCDHEIGHT == 32)) {
		comPins = 0x02;
		contrast = 0x0F;
	} else if ((SSD1306_LCDWIDTH == 128) && (SSD1306_LCDHEIGHT == 64)) {
		comPins = 0x12;
		contrast = 0xCF;
	} else if ((SSD1306_LCDWIDTH == 96) && (SSD1306_LCDHEIGHT == 16)) {
		comPins = 0x2; // ada x12
		contrast = 0xAF;
	}

	SSD1306_SendCommand(SSD1306_SETCOMPINS);
	SSD1306_SendCommand(comPins);
	SSD1306_SendCommand(SSD1306_SETCONTRAST);
	SSD1306_SendCommand(contrast);

	SSD1306_SendCommand(SSD1306_SETPRECHARGE); // 0xd9
	SSD1306_SendCommand(0xF1);

	SSD1306_SendCommand(SSD1306_SETVCOMDETECT);
	SSD1306_SendCommand(0x40);
	SSD1306_SendCommand(SSD1306_DISPLAYALLON_RESUME);
	SSD1306_SendCommand(SSD1306_NORMALDISPLAY);
	SSD1306_SendCommand(SSD1306_DEACTIVATE_SCROLL);

	SSD1306_SendCommand(SSD1306_DISPLAYON);


}

void SSD1306_set_pixel(uint8_t x, uint8_t y, uint8_t bw)
{
	if (x > SSD1306_LCDWIDTH || y > SSD1306_LCDHEIGHT) return;

	switch (bw)
	{
	case WHITE:
		buffer_oled[(y/8) * SSD1306_LCDWIDTH + x] |= (1<<(y%8));
		break;
	case BLACK:
		buffer_oled[(y/8) * SSD1306_LCDWIDTH + x] &= ~(1<<(y%8));
		break;
	case INVERSE:
		buffer_oled[(y/8) * SSD1306_LCDWIDTH + x] ^= (1<<(y%8));
		break;
	}
}

typedef struct 
{
	uint16_t bitmap_max_idx;
	uint8_t buf_row_first;
	uint8_t buf_row_last;
	uint8_t buf_col_first;
	uint8_t buf_col_last;
	uint8_t buf_mask_top;
	uint8_t buf_mask_bottom;
	uint8_t bitmap_col;
	uint8_t bitmap_row_first;
	uint8_t bitmap_row_last;
	uint8_t bitmap_shift;
}buf_bitmap_boundry_t;

static void get_boundry (buf_bitmap_boundry_t* boundry, uint8_t bitmap_width, uint8_t bitmap_height, int8_t pos_x, int8_t pos_y)
{
	if (pos_x < 0) {
		boundry->bitmap_col = pos_x * -1;
		boundry->buf_col_first = 0;
	} else {
		boundry->bitmap_col = 0;
		boundry->buf_col_first = pos_x;
	}

	if (pos_y < 0) {
		boundry->bitmap_shift = 8 + (pos_y % 8) ;
		boundry->bitmap_row_first = (pos_y / 8) * (-1) + 1;
		boundry->buf_row_first = 0;
		boundry->buf_mask_top = 0;
	} else {
		boundry->bitmap_shift = pos_y % 8;
		boundry->bitmap_row_first = 0;
		boundry->buf_row_first = pos_y / 8;
		boundry->buf_mask_top = 0xFF >> (8 - boundry->bitmap_shift);
	}
	boundry->buf_mask_bottom = 0xFF << ((pos_y + bitmap_height) % 8);
	if (boundry->buf_mask_bottom == 0xFF) {
		boundry->buf_mask_bottom = 0;
	}

	if ((bitmap_width + pos_x) > SSD1306_LCDWIDTH) {
		boundry->buf_col_last = SSD1306_LCDWIDTH;
	} else {
		boundry->buf_col_last = bitmap_width + pos_x;
	}
	
	if (bitmap_height + pos_y > SSD1306_LCDHEIGHT) {
		boundry->buf_row_last = SSD1306_LCDHEIGHT / 8;
	} else {
		boundry->buf_row_last = (bitmap_height + pos_y + 7) / 8;
	}
	
	boundry->bitmap_row_last = (pos_y + bitmap_height) / 8;
	boundry->bitmap_max_idx = bitmap_width * ((bitmap_height + 7) / 8);
}

static inline uint8_t get_bitmap_byte (const uint8_t* bitmap, uint16_t index, uint8_t color)
{
	switch (color)
	{
		case INVERSE:
			return ~(bitmap[index]);
		case WHITE:
			return 0xFF;
		case BLACK:
			return 0x00;
		default:
			return bitmap[index];
	}
}
/**
 * @brief A function that writes a bitmap into the buffer at the given position.
 * 			0,0 -------->x
 * 			 |
 * 			 |
 * 			\ /
 * 			 y
 * @param bitmap A pointer to bitmap array.
 * @param bitmap_width Bitmap witdh in pixels.
 * @param bitmap_height Bitmap height in pixels.
 * @param pos_x Position x in the display
 * @param pos_y Position y in the display
 * @param color NORMAL (2) normal mode or INVERSE mode for bitmap
 * 				WHITE (0) or black (1) for fill screen
 */
void SSD1306_write_to_buffer(const uint8_t* bitmap, uint8_t bitmap_width, uint8_t bitmap_height, int8_t pos_x, int8_t pos_y, uint8_t mode)
{
	if (bitmap_width + pos_x < 0 || bitmap_height + pos_y < 0) return;

	uint16_t tmp_buf16, bitmap_idx, buf_idx;
	uint8_t tmp_bitmap, bitmap_row;

	buf_bitmap_boundry_t b;
	get_boundry(&b, bitmap_width, bitmap_height, pos_x, pos_y);

	for(uint8_t col = b.buf_col_first; col < b.buf_col_last; col++, b.bitmap_col++)
	{
		tmp_buf16 = 0;
		bitmap_row = b.bitmap_row_first;

		if (b.bitmap_row_first > 0) {
			tmp_buf16 = get_bitmap_byte(bitmap, bitmap_width * (b.bitmap_row_first - 1) + b.bitmap_col, mode) >> (8 - b.bitmap_shift);
		} else {
			tmp_buf16 = buffer_oled[b.buf_row_first * SSD1306_LCDWIDTH + col] & b.buf_mask_top;
		}
		
		for( uint8_t buf_row = b.buf_row_first; buf_row < b.buf_row_last; buf_row++, bitmap_row++ )
		{
			bitmap_idx = bitmap_width * bitmap_row + b.bitmap_col;
			buf_idx = buf_row * SSD1306_LCDWIDTH + col;

			if (bitmap_idx < b.bitmap_max_idx) {
				tmp_bitmap = get_bitmap_byte(bitmap, bitmap_idx, mode);
				tmp_buf16 |= tmp_bitmap << b.bitmap_shift;
			}

			if ( b.bitmap_row_last == buf_row) {
				buffer_oled[buf_idx] = (buffer_oled[buf_idx] & b.buf_mask_bottom) | (tmp_buf16 & ~(b.buf_mask_bottom));
			} else {
				buffer_oled[buf_idx] = (uint8_t) tmp_buf16;
			}
			tmp_buf16 = tmp_buf16 >> 8;
		}
	}
}

void SSD1306_clear_buffer(uint8_t width, uint8_t height, int8_t pos_x, int8_t pos_y, uint8_t color)
{
	SSD1306_write_to_buffer(NULL, width, height, pos_x, pos_y, color);
}

