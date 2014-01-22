#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "portdefs.h"
#include "lib/usart.h"
#include "lib/DHT11.c"

int cnt;

void main()
{
	USART_Init(25);
	DDRC=0xFF;	
	PORTC=1<<PC4;
	sei();
	
	USSendString("Ready\n");
	while (1){
		_delay_ms(1000);
		every_second();
	}
}

// Things which do every second
void every_second(){
	cnt++;
	USSendByte(' ');
	USSendNumber(DHTgetHum());
	USSendByte(' ');
	USSendNumber(DHTgetTemp());
	USSendByte(' ');
	USSendNumber(DHTgetCS());
	USSendByte('\n');
	//USSendString("Measuring\n");
	DHTmeasure();
}
