#ifndef PORTDEFS_H
#define PORTDEFS_H

#define CHA		PORTD
#define CHB		PORTB
#define DDA		DDRD
#define DDB		DDRB
#define PINCHA	PIND
#define PINCHB	PINB
#define PCICHA	PCIE2
#define	PCICHB	PCIE0

#define	CHA0	PD5
#define CHA1	PD6
#define CHB0	PB0	
#define CHB1	PB1
#define CHB2	PB2

#define MSKCHA		PCMSK2
#define	MSKCHB		PCMSK0

#define	PCICHA0		PCINT21
#define PCICHA1		PCINT22
#define PCICHB0		PCINT0	
#define PCICHB1		PCINT1
#define PCICHB2		PCINT2

#define PCCHA_vect	PCINT2_vect
#define	PCCHB_vect	PCINT0_vect
//#define










#endif
