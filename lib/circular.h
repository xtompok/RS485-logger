/*
 *  circular.h
 *  servo-serial
 *
 *  Created by Tomáš Pokorný on 30.12.10.
 *  Copyright 2010 Jaroška. All rights reserved.
 *
 */
#include <stdio.h>
#include <ctype.h>
# define MAXCQSIZE 128

typedef struct{
	unsigned char array[MAXCQSIZE];
	unsigned char front;
	unsigned char rear;
	unsigned char state;	// 0 -- non empty, 1 -- full, 2 -- empty
} CQUEUE;

void CQpush(unsigned char item,volatile CQUEUE * q);
char CQstate(volatile CQUEUE * q);
unsigned char CQpop(volatile CQUEUE * q);


#include "circular.c"

