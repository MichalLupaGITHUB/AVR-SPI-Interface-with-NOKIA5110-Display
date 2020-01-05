/*
 * SPI_Config.c
 *
 * Created: 2019-12-12 19:33:20
 *  Author: lupa
 */ 

#include <avr/io.h>
#include "Harddef.h"
#include "makra.h"
#include "SPI_Config.h"

void SPI_SS_Enable()												/* Enable the SS pin to logic zero */
{
	PORT(SPI_INTERFACE) &= ~(1<<SS);
}

void SPI_SS_Disable()												/* disable the SS pin to logic one */
{
	PORT(SPI_INTERFACE) |= (1<<SS);
}

void SPI_Init()
{
	DDR(SPI_INTERFACE) = (1<<MOSI)|(1<<SCK)|(1<<SS)|(1<<RST)|(1<<DC);				/* Set MOSI and SCK output, all others input */
	PORT(SPI_INTERFACE) |= (1<<RST);												/* define reset pin as a output */
	DDR(SPI_INTERFACE) &= ~(1<<MISO);												/* define MISO pin as a input */
	PORT(SPI_INTERFACE) |= (1<<SS);												/* Make SS pin as a output */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); // wlaczenie SPI, ustawienie Mastera, ustawienie predkosci						/* Enable SPE, MSTR and SPR0 bit in SPI control register */
}

char SPI_Read()
{
	SPDR = 0xFF; // SPDR - SPI data register
	while(!(SPSR & (1<<SPIF)));	// kiedy transmisja jest kompleta pojawia sie bit SPIF									/* wait here while SPIF flag set */
	return(SPDR);													/* Return the SPDR value */
}

void SPI_Write(char write_data)
{
	SPDR = write_data;
	while(!(SPSR & (1<<SPIF)));	 // SPSR - SPI status register									/* wait here while SPIF flag set */
}