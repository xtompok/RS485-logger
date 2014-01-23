#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/crc16.h>
#include <avr/eeprom.h>
#include "portdefs.h"
#include "lib/usart.h"
#include "lib/DHT11.c"

#define MB_SEND(MSG,LEN) USSendMessage(MSG,LEN)
#define MB_DATA_DHT11_H(addr) DHTgetHum()
#define MB_DATA_DHT11_T(addr) DHTgetTemp()
#include "lib/modbus.h"


#define EE_ADDRESS 0x00

volatile uint8_t address;
volatile uint64_t clock;

uint8_t message[32];

uint8_t DHT11_H[1];
uint8_t DHT11_T[1];

void clockInit();
void everySecond();
void every10ms();
void processMessage(uint8_t len);

inline uint8_t DHT11_H_read(uint8_t idx){
	return DHTgetHum();
}
inline uint8_t DHT11_T_read(uint8_t idx){
	return DHTgetTemp();
}


int main()
{

	USART_Init(25);
	clockInit();
	address = eeprom_read_byte(EE_ADDRESS);
	MBinit(address);
	
	sei();

	USSendNumber(address);
	USSendString("Ready\n");

	enum {IDLE,RECV,TIMEOUT,PROCESS} msgStatus;
	uint8_t msgIdx;
	uint64_t memclock;
	uint8_t secDone;

	while (1)
	{
		if (clock!=memclock)
		{
			every10ms();

			switch (msgStatus){
				case RECV:
					if (!USisByte())
						msgStatus=TIMEOUT;
					break;
				case TIMEOUT:
					msgStatus=PROCESS;
					break;
			}

			memclock=clock;	
		}
		if ((clock%100) == 0)
		{
			if (!secDone){
				everySecond();
				secDone = 1;
			}
		} else
			secDone = 0 ;
		
		
		if (msgStatus == PROCESS)
		{
			MBprocessMessage(message,msgIdx);
			msgStatus = IDLE;
		}

		while (USisByte()){
			if (msgStatus==IDLE)
				msgIdx=0;
			msgStatus=RECV;
			message[msgIdx]=USGetByte();
			msgIdx++;
		}
	}
	return 0;
}

void clockInit(){
	clock=0;
	// CTC mode, output disconnected
	TCCR0A = (1<<WGM01);
	// 16MHz/1024/156 ~ 100Hz
	OCR0A = 156;
	// Prescaler 1024
	TCCR0B = (1<<CS02)|(1<<CS00);
	TIMSK0 = (1<<OCIE0A);
}

// Things which do every second
void everySecond(){
/*	USSendByte(' ');
	USSendNumber(DHTgetHum());
	USSendByte(' ');
	USSendNumber(DHTgetTemp());
	USSendByte(' ');
	USSendNumber(DHTgetCS());
	USSendByte('\n');
*/	//USSendString("Measuring\n");
	DHTmeasure();
}

void every10ms(){

}

ISR(TIMER0_COMPA_vect){
	clock++;
}
