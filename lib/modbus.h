// Modbus processing library
//
//

#ifndef MODBUS_H
#define MODBUS_H

#ifndef MB_SEND
#error Sending function undefined
#endif

#ifndef MB_DATA_DHT11_H
#define MB_DATA_DHT11_H(a) 0
#endif

#define MB_F_READ_HOLDING_REGISTERS 0x03


#define MB_ADDR_DHT11_H 0x01
#define MB_ADDR_DHT11_T 0x02

#define MB_EXC_FUNC_UNSUPPORTED 0x01
#define MB_EXC_WRONG_COUNT 		0x03
#define MB_EXC_OUT_OF_RANGE		0x02
#define MB_EXC_PROCESS_ERROR	0x04


void MBprocessMessage(uint8_t * message, uint8_t len);
void MBerror(uint8_t errType);

#include "modbus.c"

#endif
