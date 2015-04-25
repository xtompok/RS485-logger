/*
 *  usart.c
 *  servo-serial
 *
 *  Created by Tomáš Pokorný on 30.12.10.
 *  Copyright 2010 Jaroška. All rights reserved.
 *
 */

#include "circular.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/crc16.h>

volatile CQUEUE USTxbuf;
volatile CQUEUE USRxbuf;

//********* USART functions *******//
void USART_Init( unsigned int ubrr )
{
	
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0);
	/* Set frame format: 8data, 1 stop bit */
	UCSR0C = /*(1<<USBS)|*/(3<<UCSZ00);
	// Initialize TX_Enable pin on RS-485 driver
	DDRD|=1<<PD2;
	PORTD|=1<<PD2;
}

#define USSTARTTX {\
	PORTD |= 1<<PD2;\
	UCSR0B &= ~(1<<RXEN0); \
	UCSR0B |=   1<<UDRIE0;} 

void USSendByte(unsigned char data)
{
	CQpush(data, &USTxbuf);
	USSTARTTX	
	return;
}

void USSendString(char string[])
{
	unsigned char i;
	i=0;
	while (string[i]!=0) {
		CQpush(string[i], &USTxbuf);
		i++;
	}
	USSTARTTX	
}
void USSendNumber(unsigned char cislo)
{
	unsigned char d1,d2;
	d1=cislo%10;
	cislo /=10;
	d2 = cislo%10;
	cislo /=10;
	CQpush((cislo%10)+'0',&USTxbuf);
	CQpush(d2+'0',&USTxbuf);
	CQpush(d1+'0',&USTxbuf);
	USSTARTTX	

}
void USSendMessage(uint8_t * message, uint8_t len)
{
	uint16_t crc;
	crc=0xFFFF;

	for (uint8_t i = 0;i<len;i++){
		CQpush(message[i],&USTxbuf);
		crc = _crc16_update(crc,message[i]);
	}
	CQpush((uint8_t)(crc&0xFF),&USTxbuf);
	CQpush((uint8_t)(crc>>8),&USTxbuf);

	USSTARTTX
}

ISR(USART_UDRE_vect)
{
	unsigned char data;
	data = CQpop(&USTxbuf);
	UDR0 = data;
	if (USTxbuf.state==2){ 
		UCSR0B&=~(1<<UDRIE0);
	}
}

unsigned char USGetByte()
{
	return CQpop(&USRxbuf);
}

unsigned char USisByte()
{
	return (USRxbuf.state==2)?0:1;
}

ISR(USART_RX_vect)
{
	
	unsigned char data;
	data = UDR0;
	CQpush(data	, &USRxbuf);

/*	if ((data>32)&&(data<128))
	{
	USSendByte(data);
	}
*/	
}

ISR(USART_TX_vect)
{
	PORTD &= ~(1<<PD2);
	UCSR0B|=1<<RXEN0;
}
