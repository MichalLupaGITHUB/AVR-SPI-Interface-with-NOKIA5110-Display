#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "Tesla_Logo.h"
#include "Apple_Logo.h"


#include "LCD5110.h"
#include "SPI_Config.h"
#include "makra.h"
#include "Harddef.h"
#include "Font.h"

int main()
{
	SPI_Init();
	N5110_init();
	N5110_clear();
	lcd_setXY(LCDC_YADR,LCDC_XADR);
	
	while(1)
	{
		N5110_image(Apple_Logo);
		_delay_ms(1500);
		N5110_image(Tesla_Logo);
		_delay_ms(1500);	
	}
		
	return 0;
}

