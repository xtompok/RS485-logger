/*
 *  usart.h
 *  servo-serial
 *
 *  Created by Tomáš Pokorný on 30.12.10.
 *  Copyright 2010 Jaroška. All rights reserved.
 *
 */

inline void USART_Init( unsigned int ubrr );
inline void USSendByte(unsigned char data);
void USSendString(char string[]);
void USART_Transmit( unsigned char data );

#include "usart.c"

