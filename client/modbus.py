#!/usr/bin/python

from pymodbus.client.sync import ModbusSerialClient as ModbusClient

def connect():
	try:
	    client = None
	    client = ModbusClient(retries = 0, method='rtu', port='/dev/ttyUSB1', baudrate=38400, stopbits=1, parity='N', bytesize=8, timeout=1)
	    client.connect()
	    return client
	
	except Exception as e:
	    print "Error while connecting client: \n"+e.__str__()

client = connect()
print client.read_holding_registers(0x0101,count=1,unit=0x01)
print client.read_coils(0x0201,count=1,unit=0x01)
