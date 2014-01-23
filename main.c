#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/crc16.h>
#include <avr/eeprom.h>
#include "portdefs.h"
#include "lib/usart.h"
#include "lib/DHT11.c"


#define EE_ADDRESS 0x00

#define MSG_IDLE 	0
#define MSG_RECV	1
#define MSG_TIMEOUT 2
#define MSG_PROCESS 3

volatile uint8_t address;
volatile uint64_t clock;

uint8_t message[32];

void clockInit();
void everySecond();
void every10ms();
void processMessage(uint8_t len);

int main()
{
	USART_Init(25);
	clockInit();
	address = eeprom_read_byte(EE_ADDRESS);
	
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
			processMessage(msgIdx);
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
	// Presclaer 1024
	TCCR0B = (1<<CS02)|(1<<CS00);
	TIMSK0 = (1<<OCIE0A);
}

// Things which do every second
void everySecond(){
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

void every10ms(){

}

void processMessage(uint8_t len){
	if (message[0]!=address){
		return;
	}

	USSendMessage(message,len);

	uint16_t crc;
	crc = 0xffff;
	for (uint8_t i=0;i<len;i++){
		crc = _crc16_update(crc,message[i]);
	}
	if (crc != 0)
	{
		USSendByte(0xEE);
		return;
	}

	switch (message[1]){
		case 0x03:	// Read analog output holding registers
			{
				uint16_t regAddr;
				regAddr = (uint16_t)message[2];
				uint16_t regCnt;
				regCnt = (uint16_t)message[4];
				if (regAddr == 0x01 && regCnt == 1){
					message[2]=1;
					message[3]=DHTgetHum();
					message[4]=0;
					USSendMessage(message,5);
				}
			}
			break;
	
	}


}

ISR(TIMER0_COMPA_vect){
	clock++;
}
