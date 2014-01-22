#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lib/usart.h"

void main()
{
	USART_Init(25);
	DDRC=0xFF;	
	PORTC=1<<PC4;
	sei();
	
	USSendByte('a');
	while (1){}

	
}
