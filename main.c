#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "portdefs.h"
#include "lib/usart.h"
#include "lib/quadenc.h"

volatile char interrupted;
volatile struct encoder enc1;
volatile struct encoder enc2;

int main()
{

	USART_Init(25);
	quad_init();
	
	sei();

	while(1){
////		USSendString("Ready\n");
		if (interrupted){
			USSendString("\nINT");
			USSendByte('\n');
			USSendNumber(enc1.steps);
			USSendByte(',');
			USSendNumber(enc2.steps);
			USSendByte(' ');
			interrupted = 0;
		}else {
		}
	}
}

ISR(PCINT1_vect){
	cli();
	char state;
	state = ((!!(QUAD1_PIN & QUAD1_A))|((!!(QUAD1_PIN & QUAD1_B))<<1)); 
	step(&enc1,state);
	state = ((!!(QUAD2_PIN & QUAD2_A))|((!!(QUAD2_PIN & QUAD2_B))<<1)); 
	step(&enc2,state);
	interrupted = 1;
	sei();
	
}
