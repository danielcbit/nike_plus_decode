/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
 Copyright (C) 2014 Daniel Bittencourt <danielcbit@mail.com> 
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 
/**
 * @file printf.h
 *
 * Setup necessary to direct stdout to the Arduino Serial library, which
 * enables 'printf'
 */

#ifndef __PRINTF_H__
#define __PRINTF_H__

#if defined(__AVR__) //Arduino

int serial_putc( char c, FILE * ) 
{
  Serial.write( c );

  return c;
} 

void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

#else //PIC32
/*
 * For printf() output with PIC32
 */
extern "C"
{
  void _mon_putc(char s)
  {
   Serial.write(s);
  }
}
#endif

#endif // __PRINTF_H__
