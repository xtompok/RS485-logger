#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "lib/usart.h"

void main()
{
	//USART_Init(25);
	DDRD|=1<<PD2;
	PORTD|=1<<PD2;
	DDRC=0xFF;	
	PORTC=1<<PC4;
	
	UBRR0H=0x00;
	UBRR0L=25;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);

	
	while (1){
		for (int i=0;i<256;i++){
	
		char ch;

		while(!(UCSR0A & (1<<RXC0))){}
		
		ch=UDR0;

		_delay_ms(10);
		
		while(!(UCSR0A & (1<<UDRE0))){}	

		UDR0 = ch;

		while(!(UCSR0A & (1<<RXC0))){}
		
		ch=UDR0;
		}
	
	}
	return;

}
