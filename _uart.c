
#include "utilities.h"
#include "registers.h"
#include "interrupts.h"
#include "gpio.h"
#include "_uart.h"

static volatile uint16_t dataCounter=0;
static volatile uint8_t dataByteTransmit;
static UART_Config uartConfig_Internal;
static uint8_t BaudRateDivisor=16;


static void _uart_BRFactor_Calc(uint32_t BaudRate){
	UBRRL = (uint8_t)((16000000.0/(BaudRateDivisor*BaudRate))-1);
}
void _uartInit(UART_Config uartConfig){
	uartConfig_Internal = uartConfig;
	/*Adjust the speed*/
	
	UCSRA |=uartConfig.Speed;
	if(uartConfig.Speed == _DOUBLE_SPEED){
		BaudRateDivisor =8;
	}
	else{
		BaudRateDivisor =16;
	}
	
	/*EN TX & RX*/
	
	UCSRB |= TXEN_MASK ;
	UCSRB |= RXEN_MASK;

	
	/*Adjust No. of data bits , Stop bits and Parity*/

	
	UCSRC |= uartConfig.DataByte|uartConfig.StopBits|uartConfig.Parity;
	
	 if (NINTH_BIT == ENABLE)
	 {
		 UCSRB |= _9BIT_DATA_B;
	 }
	 
	 if (uartConfig.InterruptStatus != _NO_POLLING)
	 {
		 EN_GLOBAL_INT;
	 }
	
	/*Adjust Baud Rate*/
	_uart_BRFactor_Calc(uartConfig.BaudRate);
	//UBRRL =51;
	UBRRH =0;
	gpioPinDirection(GPIOD,BIT0,INPUT);
	gpioPinDirection(GPIOD,BIT1,OUTPUT);
	//EN_GLOBAL_INT;
}
void _uartTransmitChar(uint8_t Data){
	if(uartConfig_Internal.InterruptStatus == _TRANSMIT_UDRIE){
		UCSRB |= _TRANSMIT_UDRIE;
		
		dataByteTransmit = Data;
	}
	else{
		while(!(UCSRA & UDRE_FLAG_MASK));
		UDR = Data;
		if(NINTH_BIT == ENABLE){
			
		}
	}
	

}
void _uartTransmitStr(uint8_t* Data){
	dataCounter =0;
	if(uartConfig_Internal.InterruptStatus == _NO_POLLING){
		while(Data[dataCounter]!='\0'){
			
			_uartTransmitChar(Data[dataCounter]);
			dataCounter++;
		}
	}
	else{
		while(Data[dataCounter]!='\0'){
		
		_uartTransmitChar(Data[dataCounter]);
		clr_bit(UCSRB,5);
	}
	}
	
}

void _uartRecieveChar(uint8_t* Data){
	while(!(UCSRA & RXC_FLAG_MASK));//lesa el buffer mana2alsh el data lel transmit shift reg
	(*Data) = UDR;
}


_ISR__(USART_UDRE_vect){
	
	UDR = dataByteTransmit;
	clr_bit(UCSRB,5);
	dataCounter++;
	
}

