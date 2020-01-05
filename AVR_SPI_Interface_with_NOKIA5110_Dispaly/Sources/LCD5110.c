/*
 * LCD5110.c
 *
 * Created: 2019-12-05 23:44:06
 *  Author: lupa
 */ 

#include <avr/io.h>
#include <inttypes.h>
#include <string.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "LCD5110.h"
#include "Harddef.h"
#include "makra.h"
#include "Font.h"
#include "SPI_Config.h"


// Wysylanie komend - ustawienie bitu DC na 0 -> to jest wysylanie komend do wyswietlacza
void N5110_Cmnd(char DATA)
{
	PORT(SPI_INTERFACE) &= ~(1<<DC);  /* make DC pin to logic zero for command operation */
	SPI_SS_Enable();  /* enable SS pin to slave selection */
	SPI_Write(DATA);  /* send data on data register */
	PORT(SPI_INTERFACE) |= (1<<DC);  /* make DC pin to logic high for data operation */
	SPI_SS_Disable();
}

void N5110_Data(char *DATA)
{
	PORT(SPI_INTERFACE) |= (1<<DC);  /* make DC pin to logic high for data operation */
	SPI_SS_Enable();  /* enable SS pin to slave selection */
	int lenan = strlen(DATA);  /* measure the length of data */
	for (int g=0; g<lenan; g++)
	{
		for (int index=0; index<5; index++)
		{
			SPI_Write(ASCII[DATA[g] - 0x20][index]);  /* send the data on data register */
		}
		SPI_Write(0x00);
	}
	SPI_SS_Disable();
}

// 100 ms impuls na wejscie RESET -> przygotowanie do przyjecia instrukcji
void N5110_Reset()  /* reset the Display at the beginning of initialization */
{
	PORT(SPI_INTERFACE) &= ~(1<<RST);
	_delay_ms(100);
	PORT(SPI_INTERFACE) |= (1<<RST);
}

void N5110_init()
{
	//N5110_Reset();  /* reset the display */
	//N5110_Cmnd(0x21);  /* command set in addition mode */
	//N5110_Cmnd(0xC0);  /* set the voltage by sending C0 means VOP = 5V */
	//N5110_Cmnd(0x07);  /* set the temp. coefficient to 3 */
	//N5110_Cmnd(0x13);  /* set value of Voltage Bias System */
	//N5110_Cmnd(0x20);  /* command set in basic mode */
	//N5110_Cmnd(0x0C);  /* display result in normal mode */
	
	N5110_Reset();  /* reset the display */
	N5110_Cmnd(LCDC_FS|LCDC_FS_EXTENDED);  /* command set in addition mode */
	N5110_Cmnd(LCDC_VOP);  /* set the voltage by sending C0 means VOP = 5V */
	N5110_Cmnd(0xC0); 
	N5110_Cmnd(LCDC_TEMP|2);  /* set the temp. coefficient to 3 */
	N5110_Cmnd(LCDC_BIAS|3);  /* set value of Voltage Bias System */
	N5110_Cmnd(LCDC_FS|LCDC_FS_BASIC|LCDC_FS_HORADDR);  /* command set in basic mode */
	N5110_Cmnd(LCDC_DC|LCDC_DC_NORMAL);  /* display result in normal mode */
}

// ustawienie ilosci komumn i wierszy wyswietlacza
void lcd_setXY(char x, char y)  /* set the column and row */
{
	N5110_Cmnd(x);
	N5110_Cmnd(y);
}

// Wypelnienie pamieci zerami - wyczyszczenie wyswietlacza
void N5110_clear()  /* clear the Display */
{
	SPI_SS_Enable();
	PORT(SPI_INTERFACE) |= (1<<DC);
	for (int k=0; k<=503; k++)
	{
		SPI_Write(0x00);
	}
	PORT(SPI_INTERFACE) &= ~(1<<DC);
	SPI_SS_Disable();
}

void N5110_image(const unsigned char const *image_data)  /* clear the Display */
{
	SPI_SS_Enable();
	PORT(SPI_INTERFACE) |= (1<<DC);
	for (int k=0; k<=503 ; k++)
	{
		SPI_Write(image_data[k]);
	}
	PORT(SPI_INTERFACE) &= ~(1<<DC);
	SPI_SS_Disable();
}