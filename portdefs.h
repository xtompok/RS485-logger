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

#define QUAD1_DIR	DDRC// DDR  
#define QUAD1_PORT	PORTC// PORT 
#define QUAD1_PIN	PINC// PORT 
#define QUAD1_A		1<<PC0// pin A
#define QUAD1_B		1<<PC1// pin B
#define QUAD1_IEBIT	1<<PCIE1// bit in PCICR for pins A and B
#define QUAD1_IMSK	PCMSK1// PCIMSK register for pins A and B
#define QUAD1_AMSK	1<<PCINT8// PCIMSK bit for A
#define QUAD1_BMSK	1<<PCINT9// PCIMSK bit for B

#define QUAD2_DIR	DDRC// DDR  
#define QUAD2_PORT	PORTC// PORT 
#define QUAD2_PIN	PINC// PORT 
#define QUAD2_A		1<<PC2// pin A
#define QUAD2_B		1<<PC3// pin B
#define QUAD2_IEBIT	1<<PCIE1// bit in PCICR for pins A and B
#define QUAD2_IMSK	PCMSK1// PCIMSK register for pins A and B
#define QUAD2_AMSK	1<<PCINT10// PCIMSK bit for A
#define QUAD2_BMSK	1<<PCINT11// PCIMSK bit for B










#endif
