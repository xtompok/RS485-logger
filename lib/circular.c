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


void CQpush(unsigned char item,volatile CQUEUE * q)
{
	q->rear++;
	q->rear = (q->rear%MAXCQSIZE);
	while(q->front == q->rear)
	{
	}
	
	
	q->state=0;
	q->array[q->rear]=item;
	
}
char CQstate(volatile CQUEUE * q)
{
	return q->state;
}
	
unsigned char CQpop(volatile CQUEUE * q)
{
	if (q->state==2) return 0;
	q->state=0;
	q->front++;
	q->front = q->front%MAXCQSIZE;
		
	if(q->front == q->rear)
	{
		// CIRCULAR STACK EMPTY
		q->state=2;
	}
	return(q->array[q->front]);
}

