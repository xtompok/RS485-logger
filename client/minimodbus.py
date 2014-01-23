#!/usr/bin/python

import minimalmodbus as mb

mb.BAUDRATE=38400
inst = mb.Instrument('/dev/ttyUSB1',1)
print inst.read_register(0x0100,1)


