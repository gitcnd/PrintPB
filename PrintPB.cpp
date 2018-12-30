/*
  PrintPB.cpp - Library for printing PB strings-encoded datablocks
  (C) Copyright 2018 (GNU GENERAL PUBLIC LICENSE, Version 3) - Chris Drake <cdrake@cpan.org>
*/

#include "PrintPB.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <PicoPB.h>
PicoPB PicoPB(0);	// 0 does nothing - we might need some switch in future?



PrintPB::PrintPB(HardwareSerial *port) {
  _port = port;
}

uint16_t PrintPB::print(uint8_t *pbuf, uint16_t plen) {
  return PrintPB::print(pbuf, plen, 0);
}
uint16_t PrintPB::print(uint8_t *pbuf, uint16_t plen, uint32_t flags) {
  uint16_t pchr=0;		// pbuf character we are processing
  uint32_t nest=flags>>30;	// get the nest level
  uint8_t maxnest=nest;nest=0;	// remember how deep we go, and where we are at now
  uint16_t nest_pchr[4]={0,0,0,0}; // So we know when we get to the end of a nest level

  while(pchr<plen) {
    if((nest>0)&&(pchr>=nest_pchr[nest]))nest--;
    //for(int n=0;n<nest;n++) _port->print(F("    "));	// Indent the nesting levels
    _port->print(F("0x")); _port->print(pbuf[pchr],HEX);// Print the PB value in hex
    int id=pbuf[pchr] >>3;
    int field=pbuf[pchr] &0b111; // wire type. (wire varint=0, 64bit=1, string=2, startgroup=3, endgrp=4, 32bit=5)
    _port->print(F("(id")); _port->print(id);		// Show the ID too
    _port->print(F(" w")); _port->print(field);		// And the field number
    _port->print(F(") "));
    pchr++;

    if(field==2) {		// Wire type 2 is a string
      for(int n=0;n<nest;n++) _port->print(F("    "));	// Indent the nesting levels
      unsigned int maxlen;pchr+=PicoPB.decode_varint(&pbuf[pchr],&maxlen); // Get the string length
      if(nest<maxnest) {
	nest++;			// New nest level
	nest_pchr[nest]=pchr+maxlen; // Remember when this will end
      } else {
	_port->print(F("\""));
	while(maxlen-->0)_port->print(pbuf[pchr++],0); // Print it out
	_port->print(F("\", "));
      }
    } else if(field==0) {	// Wire type 0 is a varint
      uint32_t vflag=1<<id;
      if(flags&vflag) {		// Signed
	int32_t val;pchr+=PicoPB.decode_svarint(&pbuf[pchr],&val);
	_port->print(val);
      } else {			// Unsigned
	uint32_t val;pchr+=PicoPB.decode_varint(&pbuf[pchr],&val);
	_port->print(val);
      }
      _port->print(F(", "));
    } else if(field==5) {	// Wire type 0 is a varint
      uint32_t vflag=1<<id;
      if(flags&vflag) {		// unsigned int instead of a float
	int32_t val;pchr+=PicoPB.decode_fixed32(&pbuf[pchr],(float *)&val);
	_port->print(val);
      } else {
	float val;pchr+=PicoPB.decode_fixed32(&pbuf[pchr],&val);
	_port->print(val);
      }
    } else {
      _port->print(F("Unknown wire type:"));
      _port->println(field);
    }

  } // while

} // print

uint16_t PrintPB::println(uint8_t *pbuf, uint16_t plen) {
  uint16_t ret=print(pbuf,plen,0);
  _port->println();
  return ret;
} // println

uint16_t PrintPB::println(uint8_t *pbuf, uint16_t plen, uint32_t flags) {
  uint16_t ret=print(pbuf,plen,flags);
  _port->println();
  return ret;
} // println


uint16_t PrintPB::showfield(uint8_t *pbuf, uint16_t *pchr, uint8_t *id, uint8_t *field) { // unused
  int flen=0;
  _port->print(F("0x")); _port->print(pbuf[*pchr],HEX); *id=pbuf[*pchr] >>3; *field=pbuf[*pchr] &0b111; _port->print(F("(id")); _port->print(*id); _port->print(F(" w")); _port->print(*field); _port->print(F(") ")); flen++;
  if(*field==0) { // varint
    uint32_t val=0;
    // Serial.print(F("grr:"));Serial.print(*pchr+flen); Serial.print(F(" B=0x"));Serial.println(pbuf[*pchr+flen],HEX);
    flen+=PicoPB.decode_varint(&pbuf[*pchr+flen],&val);
    _port->print(F("l("));_port->print(flen);
    _port->print(F(")"));
    _port->print(F("v="));
    _port->print(val);  _port->print(F(" "));
  }
  return flen;
}

