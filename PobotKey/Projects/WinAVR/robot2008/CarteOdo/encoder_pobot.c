/*! \file encoder.c \brief Quadrature Encoder reader/driver. */
//*****************************************************************************
//
// File Name	: 'encoder.c'
// Title		: Quadrature Encoder reader/driver
// Author		: Pascal Stang - Copyright (C) 2003-2004
// Created		: 2003.01.26
// Revised		: 2004.06.25
// Version		: 0.3
// Target MCU	: Atmel AVR Series
// Editor Tabs	: 4
//
// NOTE: This code is currently below version 1.0, and therefore is considered
// to be lacking in some functionality or documentation, or may not be fully
// tested.  Nonetheless, you can expect most functions to work.
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

#include <avr/io.h>
#include <avr/interrupt.h>

#include "global.h"
#include "encoder_pobot.h"

// Program ROM constants

// Global variables
volatile EncoderStateType EncoderState[NUM_ENCODERS];

// Functions

// encoderInit() initializes hardware and encoder position readings
//		Run this init routine once before using any other encoder functions.
void encoderInit(void)
{
	u08 i;

	// initialize/clear encoder data
	for(i=0; i<NUM_ENCODERS; i++)
	{
		EncoderState[i].position = 0;
		//EncoderState[i].velocity = 0;		// NOT CURRENTLY USED
	}

	// configure direction and interrupt I/O pins:
	// - for input
	// - apply pullup resistors
	// - any-edge interrupt triggering
	// - enable interrupt

	#ifdef ENC0_SIGNAL
		// set interrupt pins to input and apply pullup resistor
		cbi(ENC0_PHASEA_DDR, ENC0_PHASEA_PIN);
		sbi(ENC0_PHASEA_PORT, ENC0_PHASEA_PIN);
		// set encoder direction pin for input and apply pullup resistor
		cbi(ENC0_PHASEB_DDR, ENC0_PHASEB_PIN);
		sbi(ENC0_PHASEB_PORT, ENC0_PHASEB_PIN);
		// configure interrupts for any-edge triggering
		sbi(ENC0_ICR, ENC0_ISCX0);
		sbi(ENC0_ICR, ENC0_ISCX1);
		// enable interrupts
		sbi(IMSK, ENC0_INT);	// ISMK is auto-defined in encoder.h
	#endif
	#ifdef ENC1_SIGNAL
		// set interrupt pins to input and apply pullup resistor
		cbi(ENC1_PHASEA_DDR, ENC1_PHASEA_PIN);
		sbi(ENC1_PHASEA_PORT, ENC1_PHASEA_PIN);
		// set encoder direction pin for input and apply pullup resistor
		cbi(ENC1_PHASEB_DDR, ENC1_PHASEB_PIN);
		sbi(ENC1_PHASEB_PORT, ENC1_PHASEB_PIN);
		// configure interrupts for any-edge triggering
		sbi(ENC1_ICR, ENC1_ISCX0);
		sbi(ENC1_ICR, ENC1_ISCX1);
		// enable interrupts
		sbi(IMSK, ENC1_INT);	// ISMK is auto-defined in encoder.h
	#endif
	
	// enable global interrupts
	sei();
}

// encoderOff() disables hardware and stops encoder position updates
void encoderOff(void)
{
	// disable encoder interrupts
	#ifdef ENC0_SIGNAL
		// disable interrupts
		sbi(IMSK, INT0);	// ISMK is auto-defined in encoder.h
	#endif
	#ifdef ENC1_SIGNAL
		// disable interrupts
		sbi(IMSK, INT1);	// ISMK is auto-defined in encoder.h
	#endif
}

// encoderGetPosition() reads the current position of the encoder 
s16 encoderGetPosition(u08 encoderNum)
{
	// sanity check
	if(encoderNum < NUM_ENCODERS)
		return EncoderState[encoderNum].position;
	else
		return 0;
}

// encoderSetPosition() sets the current position of the encoder
void encoderSetPosition(u08 encoderNum, s16 position)
{
	// sanity check
	if(encoderNum < NUM_ENCODERS)
		EncoderState[encoderNum].position = position;
	// else do nothing
}

#ifdef ENC0_SIGNAL
//! Encoder 0 interrupt handler
SIGNAL(ENC0_SIGNAL)
{
	sbi(PORTB,4);
	// encoder has generated a pulse
	// check the relative phase of the input channels
	// and update position accordingly
	
	if( (inb(ENC0_PHASEB_PORTIN) & (1<<ENC0_PHASEB_PIN)) == 0)
	{
	/*
	if( ((inb(ENC0_PHASEA_PORTIN) & (1<<ENC0_PHASEA_PIN)) == 0) ^
		((inb(ENC0_PHASEB_PORTIN) & (1<<ENC0_PHASEB_PIN)) == 0) )
	{
	*/
		EncoderState[0].position++;		
	}
	else
	{
		EncoderState[0].position--;
	}
	
	cbi(PORTB,4);
}
#endif

#ifdef ENC1_SIGNAL
//! Encoder 1 interrupt handler
SIGNAL(ENC1_SIGNAL)
{
	sbi(PORTB,5);
	// encoder has generated a pulse
	// check the relative phase of the input channels
	// and update position accordingly
	if( (inb(ENC1_PHASEB_PORTIN) & (1<<ENC1_PHASEB_PIN)) == 0)
	{
		EncoderState[1].position++;
	}
	else
	{
		EncoderState[1].position--;
	}
	cbi(PORTB,5);
}
#endif
