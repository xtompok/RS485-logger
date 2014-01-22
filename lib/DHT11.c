// Library for reading DHT11 temperature sensor
//
//

#include <avr/interrupt.h>
#include <avr/io.h>
#include <ctype.h>


volatile uint8_t DHTstatus;
volatile uint8_t DHTRHint;
volatile uint8_t DHTRHdec;
volatile uint8_t DHTTint;
volatile uint8_t DHTTdec;
volatile uint8_t DHTCS;
volatile uint8_t DHTbitc;

// Setup Timer 2 to tick every 1us
inline void DHTinitTimer(){
	TCCR2A = 0; // Normal mode, output disconnected
	TCCR2B = 1<<CS21; // 0.5us per tick
	TIMSK2 |= 1<<TOIE2;
}

// Reset timer value
inline void DHTresetTimer(){
	TCNT2=0;
}


void DHTmeasure(){

	// Pull down for >=18ms
	DDB |= 1<<CHB0;
	CHB &= ~(1<<CHB0);
	_delay_ms(20);
	// Pull up for >=20us
	DHTinitTimer();
	CHB |= 1<<CHB0;
	DDB &= ~(1<<CHB0);

	PCICR |= 1<<PCICHB;
	MSKCHB |= 1<<PCICHB0;	

	DHTstatus=1;

} 

uint8_t DHTgetHum(){
	if (DHTstatus==4)
		return DHTRHint;
	else
		return 255;
}

uint8_t DHTgetTemp(){
	if (DHTstatus==4)
		return DHTTint;
	else
		return 255;
}

uint8_t DHTgetCS(){
	return DHTRHint+DHTRHdec+DHTTint+DHTTdec-DHTCS;
}


ISR(PCCHB_vect){

	
	if (PINCHB & (1<<CHB0)){
		DHTresetTimer();
		return;
	}
//	USSendByte('i');

	switch (DHTstatus){
		case 0:
			return;
			break;
		case 1:
			if (TCNT2>160){
				DHTstatus=3;
				break;
			}
			DHTstatus++;
			break; 
		case 2:
			DHTstatus++;
			DHTbitc=0;
			break;
		case 255:
			return;
			break;
		default:
			if (TCNT2<40){
				DHTstatus=255;
				return;
			}
			if (TCNT2<70){
				switch (DHTbitc>>3){
					case 0:
						DHTRHint <<=1;
						break;
					case 1:
						DHTRHdec <<=1;
						break;
					case 2:
						DHTTint <<=1;
						break;
					case 3:
						DHTTdec <<=1;
						break;
					case 4:
						DHTCS <<=1;
						break;

				}
			}
			if (TCNT2>120){
				switch (DHTbitc>>3){
					case 0:
						DHTRHint <<=1;
						DHTRHint |=1;
						break;
					case 1:
						DHTRHdec <<=1;
						DHTRHdec |=1;
						break;
					case 2:
						DHTTint <<=1;
						DHTTint |=1;
						break;
					case 3:
						DHTTdec <<=1;
						DHTTdec |= 1;
						break;
					case 4:
						DHTCS <<=1;
					    DHTCS |=1;
						break;

				}
			}
			if (DHTbitc >=39)
			{
				DHTstatus=4;
				PCICR &= ~(1<<PCICHB);
			}
			DHTbitc++;
			break;

	}

}

ISR(TIMER2_OVF_vect)
{
//	DHTstatus=255;
//	TCCR2B=0;
}
