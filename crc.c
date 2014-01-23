#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t
crc16_update(uint16_t crc, uint8_t a)
{
    int i;

    crc ^= a;
    for (i = 0; i < 8; ++i)
    {
        if (crc & 1)
            crc = (crc >> 1) ^ 0xA001;
        else
            crc = (crc >> 1);
    }

    return crc;
}

int main(int argc, char ** argv){
	uint8_t msg []={0xFF,0x03,0x01,0x00,0x01,0x00};
	int crc;
	crc = 0xFFFF;
	for (int i =0 ; i < sizeof msg; i++){
		crc = crc16_update(crc,msg[i]);
	}

	printf("%x %x\n",(uint8_t)(crc&0xFF),(uint8_t)(crc>>8));

	return 0;
}

