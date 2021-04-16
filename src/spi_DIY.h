#ifndef _SPI_DIY_H
#define _SPI_DIY_H
#include <SPI.h>
#include <arduino.h>

static int slaveSelectPin;
static int segmentationDelay;


void spiSet(int slaveSelectPin);
byte spiFrame8(bool Write, byte address);
int  spiFrame(bool Write, byte address, byte data);
void spiSegmentationStart();
void spiSegmentationEnd();
void spiWriteRegister(uint8_t address, uint8_t data);
uint8_t spiReadRegister(uint8_t address);



void spiSet(int slaveSelectPinP, int segmentationDelayP)
{
      slaveSelectPin = slaveSelectPinP;
      segmentationDelay = segmentationDelayP;
      pinMode(slaveSelectPin, OUTPUT);
      digitalWrite(slaveSelectPin, HIGH);
      delay(10);
      SPI.begin();
      SPI.setBitOrder(MSBFIRST);
}

byte spiFrame8(bool Write, byte address)
{
      byte retour =0;
      retour = Write << 7;
      retour += (address&0x7F);
      return retour;
}

int spiFrame(bool Write, byte address, byte data)
{
      int retour =0;
      retour = Write << 15;
      retour += (address&0x7F) << 8;
      retour += data;
      return retour;
}

void spiSegmentationStart()
{
      digitalWrite(slaveSelectPin, LOW);
      delay(2*segmentationDelay);
}

void spiSegmentationEnd()
{
      delay(segmentationDelay);
      digitalWrite(slaveSelectPin, HIGH);
}

void spiWriteRegister(uint8_t address, uint8_t data)
{
    spiSegmentationStart();
	SPI.transfer16(spiFrame(1, address, data));
    spiSegmentationEnd();
}


uint8_t spiReadRegister(uint8_t address)
{
    uint8_t retour = 0;
    spiSegmentationStart();
    SPI.transfer(spiFrame8(false,address));
    retour = SPI.transfer(0);
    spiSegmentationEnd();
    return retour;
}

#endif SPI_DIY_H
