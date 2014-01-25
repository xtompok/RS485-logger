// Modbus processing library
//
//

#include <ctype.h>
#include <avr/eeprom.h>

uint8_t * MBmsg;
uint8_t MBaddr;

void MBinit(uint8_t addr)
{
	MBaddr = addr;
}

void MBprocessMessage(uint8_t * message,uint8_t len){
	// Discard messages which don't belong to us
	if (message[0]!=MBaddr){
		return;
	}

	// Check CRC
	uint16_t crc;
	crc = 0xffff;
	for (uint8_t i=0;i<len;i++){
		crc = _crc16_update(crc,message[i]);
	}
	if (crc != 0)
		return;

	MBmsg = message;

	// Process message
	uint8_t sensCnt;
	uint8_t addr;
	uint8_t	cnt;
	sensCnt=0;
	switch (MBmsg[1]){
		case MB_F_READ_HOLDING_REGISTERS:	// Read analog output holding registers
			{
				switch(MBmsg[2]){
					case MB_ADDR_DHT11_H: // Read DHT11 humidity
						sensCnt=eeprom_read_byte((uint8_t *)MB_ADDR_DHT11_H);
						addr = MBmsg[3];
						cnt = MBmsg[5];
						if ((addr+cnt)>sensCnt){
							MBerror(MB_EXC_OUT_OF_RANGE);
							return;
						}	
						MBmsg[2]=2*cnt;
						for (uint8_t i=0; i<cnt;i++){
							MBmsg[3+(2*i)]=0;
							MBmsg[4+(2*i)]=MB_DATA_DHT11_H(addr+i);
						}
						MB_SEND(MBmsg,3+(2*cnt));
						break;
					case MB_ADDR_DHT11_T:
						sensCnt=eeprom_read_byte((uint8_t *)MB_ADDR_DHT11_T);
						addr = MBmsg[3];
						cnt = MBmsg[5];
						if ((addr+cnt)>sensCnt){
							MBerror(MB_EXC_OUT_OF_RANGE);
							return;
						}	
						MBmsg[2]=cnt*2;
						for (uint8_t i=0; i<cnt;i++){
							MBmsg[3+(2*i)]=0;
							MBmsg[4+(2*i)]=MB_DATA_DHT11_T(addr+i);
						}
						MB_SEND(MBmsg,3+(2*cnt));
						break;

				
				
				
				
					
				}
			}
			break;
	
	}
}

void MBerror(uint8_t errType){
	MBmsg[1]+=80;
	MBmsg[2]=errType;
	MB_SEND(MBmsg,3);
	return; 
}
