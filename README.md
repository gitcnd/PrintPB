# PrintPB
Display a protocol-buffers data structure over your Arduino serial monitor


# SYNOPSIS

```C
  #include <PrintPB.h>

  PrintPB PrintPB(&Serial); // Specify which serial port to print out to

  void setup(){
    PrintPB.println(protocol_buffers_data,sizeof(protocol_buffers_data),0);
  }

```

## Example Output

```text
  0xA(id1 w2) 0xE0(id28 w0) 911, 0xE8(id29 w0) 5470928, 0xF0(id30 w0) 8578144, 0x40(id8 w0) -457, 0x48(id9 w0) 4294967073, 0x50(id10 w0) 293, 0x58(id11 w0) 4294967007, 0x60(id12 w0) 913, 0x80(id16 w0) 104, 0x88(id17 w0) 35, 0x90(id18 w0) 2049, 0xB0(id22 w0) 4181, 0x98(id19 w0) 65527, 0xA0(id20 w0) 8, 0xA8(id21 w0) 6, 0x68(id13 w0) 18432, 0x70(id14 w0) 0, 0x78(id15 w0) 0, 0xB8(id23 w0) 913, 0xC0(id24 w0) 4294943230, 0xC8(id25 w0) 4294947328, 0xD0(id26 w0) 4294955520, 0xD8(id27 w0) 62, 0xFD(id31 w5) 2114377728.00
```
(Shows the tag byte, the ID and wiretype from it, followed by the data and a comma)

# FUNCTIONS

```C

  PrintPB(HardwareSerial *port);	// Specify output serial port
  print(   uint8_t *pbuf, uint16_t plen, uint32_t flags); // what to print. See below for flags info
  println( uint8_t *pbuf, uint16_t plen, uint32_t flags);

```

# FLAGS

The optional flags input is a 32bit value.  The top2 bits specify how many nested levels of strings to assume are containing additional PB-formatted data.
The rest of the 30 bits specify which (if any) of the encountered varints that are found should be considered "signed" (1) or unsigned (0).
The LSB is the first-encountered varint, bit 30 is the last it can do.

# HOW TO INSTALL

(Method 1)

1. Open a terminal (commandline, bash shell, whatever)
2. Change into your Arduino folder
```bash
   cd /Applications/Arduino.app/Contents/Java/libraries/
   (or)
   cd ~/Arduino/libraries/
```
3. grab and install this code
```bash
   git clone https://github.com/gitcnd/PrintPB.git
```
4. restart your arduino IDE
5. Choose File => Examples => PrintPB => hello
6. Hit the "build" button and enjoy!

(Method 2) - see https://www.arduino.cc/en/Guide/Libraries

1. Download the ZIP of this repo: https://github.com/gitcnd/PrintPB/archive/master.zip
2. In your IDE, select Sketch -> Include Library -> Add .ZIP Library
3. Choose File => Examples => PrintPB => hello
4. Hit the "build" button and enjoy!
