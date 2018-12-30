/*
  PrintPB.h - Library for flashing PrintPB code.
  (C) Copyright 2018 (GNU GENERAL PUBLIC LICENSE, Version 3) - Chris Drake <cdrake@cpan.org>
*/

#ifndef PrintPB_h
#define PrintPB_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class PrintPB
{
  public:
    PrintPB(HardwareSerial *port);
    uint16_t print(uint8_t *pbuf, uint16_t plen);
    uint16_t println(uint8_t *pbuf, uint16_t plen);
    uint16_t print(uint8_t *pbuf, uint16_t plen, uint32_t flags);
    uint16_t println(uint8_t *pbuf, uint16_t plen, uint32_t flags);
  private:
    HardwareSerial *_port;
    uint16_t showfield(uint8_t *pbuf, uint16_t *pchr, uint8_t *id, uint8_t *field);
};

#endif

