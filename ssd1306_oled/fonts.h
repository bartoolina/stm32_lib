#ifndef FONTS_H_
#define FONTS_H_

#include "main.h"

// ==========================================================================
// structure definition
// ==========================================================================

// This structure describes a single character's display information
typedef struct
{
	const uint8_t widthBits;					// width, in bits (or pixels), of the character
	const uint16_t offset;					// offset of the character's bitmap, in bytes, into the the FONT_INFO's data array

} FONT_CHAR_INFO;

// Describes a single font
typedef struct
{
//	uint8_t DownSpace;	// Downs Space in pixels
	uint8_t heightPixels;	// height, in pages (8 pixels), of the font's characters
	uint8_t startChar;	// the first character in the font (e.g. in charInfo and data)
	uint8_t endChar;
	uint8_t interspacePixels;	// number of pixels of interspace between characters 
	// uint8_t spacePixels;	// number of pixels of space character 
	const FONT_CHAR_INFO * charInfo;	// pointer to array of char information
	const uint8_t* data;		// pointer to generated array of character visual representation
//        char * FontFileName;    // (Pointer) Font filename saved on SD card or 0 (null) otherwise
//        uint8_t bitOrientation;  // bits and byte orientation 0-T2B, 1-L2R
} FONT_INFO;
 
// Font data for Arial 8pt 
extern const uint8_t arial_12ptBitmaps[];
extern const FONT_CHAR_INFO arial_12ptDescriptors[];
extern const FONT_INFO arial_12ptFontInfo;

extern const uint8_t arial_8ptBitmaps[];
extern const FONT_CHAR_INFO arial_8ptDescriptors[];
extern const FONT_INFO arial_8ptFontInfo;



uint8_t font_print_str(const FONT_INFO * font, uint8_t * text, uint8_t pos_x, uint8_t pos_y, uint8_t mode);
uint8_t font_string_lenght_px(const FONT_INFO * font, uint8_t * text);
#endif /* MK_FONTX_H_ */
