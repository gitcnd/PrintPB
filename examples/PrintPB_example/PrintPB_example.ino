#include <PrintPB.h>

#include <SerialID.h>
SerialIDset("\n#\tv2.01 " __FILE__ "\t" __DATE__ " " __TIME__);



PrintPB PrintPB(&Serial);

uint8_t pbuf[]={ 0xA,0x58,0xE0,0x8F,0x7,0xE8,0xD0,0xF5,0xCD,0x2,0xF0,0xE0,0xC8,0x8B,0x4,0x40,0x91,0x7,0x48,0xA1,0xFE,0xFF,0xFF,0xF,0x50,0xA5,0x2,0x58,0xDF,0xFD,0xFF,0xFF,0xF,0x60,0x91,0x7,0x80,0x68,0x88,0x23,0x90,0x81,0x10,0xB0,0xD5,0x20,0x98,0xF7,0xFF,0x3,0xA0,0x8,0xA8,0x6,0x68,0x80,0x90,0x1,0x70,0x0,0x78,0x0,0xB8,0x91,0x7,0xC0,0xFE,0xC3,0xFE,0xFF,0xF,0xC8,0x80,0xE4,0xFE,0xFF,0xF,0xD0,0x80,0xA4,0xFF,0xFF,0xF,0xD8,0x3E,0xFD,0xB0,0xD,0xFC,0x4E };

uint8_t pbuf2[]={ 0xA,0x4B,0x40,0xAF,0xA,0x48,0x99,0xFE,0xFF,0xFF,0xF,0x50,0xA7,0x2,0x58,0xDB,0xFD,0xFF,0xFF,0xF,0x60,0xB1,0xA,0x80,0x61,0x88,0x22,0x90,0x83,0x10,0xB0,0xF8,0x20,0x98,0xFA,0xFF,0x3,0xA0,0x9,0xA8,0x8,0x68,0x80,0x90,0x1,0x70,0x0,0x78,0x0,0xB8,0xB1,0xA,0xC0,0xFE,0xBB,0xFE,0xFF,0xF,0xC8,0x80,0xD2,0xFE,0xFF,0xF,0xD0,0x80,0x9A,0xFF,0xFF,0xF,0xD8,0x3E,0xFD,0x4,0x3F,0xE2,0x4E};
 


void setup(){
  SerialIDshow(9600);  // initializes serial port

  PrintPB.println(pbuf,sizeof(pbuf),0b01000011100000000000000111000000);
  Serial.println();
  PrintPB.println(pbuf2,sizeof(pbuf2));

}

void loop()
{
  Serial.print(millis());
  Serial.println(" over.");
  delay(10000);
}
