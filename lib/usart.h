/*
 *  usart.h
 *  servo-serial
 *
 *  Created by Tomáš Pokorný on 30.12.10.
 *  Copyright 2010 Jaroška. All rights reserved.
 *
 */

#ifndef USART_H
#define USART_H
void USART_Init( unsigned int ubrr );
void USSendByte(unsigned char data);
void USSendNumber(unsigned char cislo);
void USSendString(char string[]);
void USART_Transmit( unsigned char data );
void USSendMessage(uint8_t * message, uint8_t len);

#endif
