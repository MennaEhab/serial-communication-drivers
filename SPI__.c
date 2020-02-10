/*
 * SPI__.c
 *
 * Created: 2/10/2020 6:54:24 PM
 *  Author: MENA
 */ 

#include "SPI__.h"

extern void _SPIInitMaster(SPI_clk clockSPI ){
		//// status register
		SPSR = 0 ;
		
		/// clear control mode
		
		SPCR = 0 ;
		/// enable SPI bit 6 
		SPCR |= Enable_SPI ;
		
		// master or slave bit 4 
		SPCR |= Master_SPI ; 
		
		//set clock
		 clockSPI = Fosc16 ;
		 
		SPCR|=clockSPI ;
		
		// set phase and polarity 
		 SPCR |= 0x00;
		 
////// GPIO set output and input 
 // ss bit4
gpioPinDirection(GPIOB ,BIT4,OUTPUT) ;

//MOSI bit5

gpioPinDirection(GPIOB ,BIT5,OUTPUT) ;

//MISO bit6

gpioPinDirection(GPIOB ,BIT6,INPUT) ;

//SCK bit 7

gpioPinDirection(GPIOB ,BIT7,OUTPUT) ;
		
	
}

extern void _SPIInitSlave(SPI_clk clockSPI ){
	//// status register
	SPSR = 0 ;
	
	/// clear control mode
	
	SPCR = 0 ;
	/// enable SPI bit 6
	SPCR |= Enable_SPI ;
	
	// master or slave bit 4
	SPCR |= Slave_SPI ;
	
	//set clock
	 clockSPI = Fosc16 ;
	
	SPCR|=clockSPI ;
	
	// set phase and polarity
	SPCR |= 0x00;
	
	////// GPIO set output and input
	// ss bit4
	gpioPinDirection(GPIOB ,BIT4,INPUT) ;

	//MOSI bit5

	gpioPinDirection(GPIOB ,BIT5,INPUT) ;

	//MISO bit6

	gpioPinDirection(GPIOB ,BIT6,OUTPUT) ;

	//SCK bit 7

	gpioPinDirection(GPIOB ,BIT7,INPUT) ;
	
	
}

extern void _SPITrancevier(char* data){
	
	if(SPCR&Master_SPI){
		
		/*Select the slave By pull down the SS pin */

		gpioPinWrite(GPIOB,BIT4,0);

	}
	
	SPDR = *data;

	while (!(SPSR&(1<<7)));

	return SPDR;
	
}



