#ifndef LCD5110_H_INCLUDED
#define LCD5110_H_INCLUDED

#include <avr/pgmspace.h>

////////////////////////////////////////////////////////////////////////////////////////////
// Definicja komend LCD
// H = X
#define LCDC_FS 0x20
	#define LCDC_FS_BASIC 0
	#define LCDC_FS_EXTENDED 0x01
	#define LCDC_FS_HORADDR 0
	#define LCDC_FS_VERTADDR 0x02
	#define LCDC_FS_PD 0x04
// H = 0 (BASIC)
#define LCDC_DC 0x08
	#define LCDC_DC_BLANK 0
	#define LCDC_DC_NORMAL 0x04
	#define LCDC_DC_ALLON 0x01
	#define LCDC_DC_INVERT 0x05
	#define LCDC_XADR 0x80
// 0-83
#define LCDC_YADR 0x40
// 0-5
// H = 1 (EXTENDED)
#define LCDC_TEMP 0x04
// 0-3 - zwykle 2 jest ok
#define LCDC_BIAS 0x10
// 0-7, dla naszego wyswietlacza powinno to byc 3
#define LCDC_VOP 0xC0
// teoretycznie 0-127, nie przekraczac 32-88
// Koniec definicji komend
////////////////////////////////////////////////////////////////////////////////////////////////

void N5110_Cmnd(char DATA);
void N5110_Data(char *DATA);
void N5110_Reset();
void N5110_init();
void N5110_clear();
void N5110_image(const unsigned char *image_data);
void lcd_setXY(char x, char y);

#endif /* LCD5110_H_INCLUDED */