#ifndef SPI_CONFIG_H_INCLUDE
#define SPI_CONFIG_H_INCLUDE

void SPI_SS_Enable();
void SPI_SS_Disable();
void SPI_Init();
void SPI_Write(char write_data);
char SPI_Read();

#endif /* SPI_CONFIG_H_INCLUDE */