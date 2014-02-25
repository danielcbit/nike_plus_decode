/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>
 Copyright (C) 2014 Daniel Bittencourt <danielcbit@gmail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example Nike+ reader with NRF24L01+
 *
 * This is an example of how to use the RF24 class to receive signals from the
 * Nike+ iPod sensor using a NRF20L01+ receiver from Nordic.
 *
 */

#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"
#include "printf.h"
#include <nike_plus_dec.h>

//
// Hardware configuration
//

// Set up nRF24L01+ radio on SPI bus plus pins 8 & 9

RF24 radio(8, 9);

bool runned = false;
char buffer[50];

//
// Setup
//

void setup(void) {
  //
  // Print preamble
  //

  Serial.begin(9600);
  delay(3000);
 #if defined(__AVR__)
  printf_begin();
 #endif
  printf("START");
  printf("\r\nRF24/examples/nordic_fob/\r\n");

  //
  // Setup and configure rf radio according to the built-in parameters
  // of the Nike+ iPod sensor.
  //

  radio.begin();

  radio.setChannel(25);
  radio.setDataRate(RF24_250KBPS);
  radio.setPayloadSize(27);
  radio.setAutoAck(false);
  radio.setCRCLength(RF24_CRC_16);
  radio.setAddressSize(3);
  radio.openReadingPipe(0, 0xC2BD0D);

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
}

//
// Loop
//

void loop(void) {
  //
  // Receive each packet, dump it out
  //

  int i;
  // if there is data ready
  if ( radio.available() ) {
    printf("\r Received sensor data\n");
    // Get the packet from the radio
    uint8_t packet[radio.getPayloadSize()+1];
    // Add 0D leading byte to the payload.
    
    packet[0] = 0x0D;
    
    // Read the rest of the payload
    radio.read( &packet[1], radio.getPayloadSize() );

    // Print raw playload data
    for (i = 0; i < radio.getPayloadSize()+1; i++)
      printf("%02x ", packet[i]);

    printf("\nProcess Packet Payload:\n");
    process(packet);
    printf("\n Ended Packet Processing\n");
  }
}

