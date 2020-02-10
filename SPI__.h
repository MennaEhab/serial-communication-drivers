/*
 * SPI__.h
 *
 * Created: 2/10/2020 6:54:43 PM
 *  Author: MENA
 */ 


#ifndef SPI___H_
#define SPI___H_


#include "std_types.h"
#include "registers.h"
#include "gpio.h"

typedef enum SPI_clk{
	Fosc4 = 0x00 ,
	Fosc16 = 0x01 ,
	Fosc64 = 0x02 ,
	Fosc128 = 0x03 ,
	}SPI_clk;

#define  Enable_SPI 0x40 

#define  Master_SPI 0x10

#define Slave_SPI 0x00

extern void _SPIInitMaster(SPI_clk clock );
extern void _SPIInitSlave(SPI_clk clock );


extern void _SPITrancevier(char* data);




#endif /* SPI___H_ */