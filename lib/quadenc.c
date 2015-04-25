#include "quadenc.h"
//#include "hardware.h"
#include <avr/io.h>
#include "../portdefs.h"


char states[4][4] = {
{0,3,1,0},
{0,1,1,2},
{2,3,1,2},
{0,3,3,2}
};

char moves[4][4] = {
{0,-1,1,0},
{-1,0,0,1},
{0,1,-1,0},
{1,0,0,-1}
};

void quad_init(void){
	QUAD1_DIR &= ~(QUAD1_A|QUAD1_B);	// Set to input
	QUAD1_PORT |= QUAD1_A|QUAD1_B;		// Enable internal pull-ups
	QUAD2_DIR &= ~(QUAD2_A|QUAD2_B);	// Set to input
	QUAD2_PORT |= QUAD2_A|QUAD2_B;		// Enable internal pull-ups
//	QUAD3_DIR &= ~(QUAD3_A|QUAD3_B);	// Set to input
//	QUAD3_PORT |= QUAD3_A|QUAD3_B;		// Enable internal pull-ups
	MCUCR &= ~(1<<PUD);			// Globally enable pull-ups

	PCICR |= QUAD1_IEBIT | QUAD2_IEBIT;// | QUAD3_IEBIT; //Enable pin-change interrupts

	QUAD1_IMSK |= QUAD1_AMSK | QUAD1_BMSK;	//Enable interrupts at encoder pins
	QUAD2_IMSK |= QUAD2_AMSK | QUAD2_BMSK;
//	QUAD3_IMSK |= QUAD3_AMSK | QUAD3_BMSK;
	

}

signed char step(volatile struct encoder * enc, char new_state){
	signed char move;
	move = moves[enc->state][new_state];
	enc->state = states[enc->state][new_state]; 
	enc->steps += move;
	return move;
}
