#ifndef _SPI_DIY_H
#define _SPI_DIY_H
#include <SPI.h>
#include <arduino.h>

static int slaveSelectPin;
static int segmentationDelay;


void spiSet(int slaveSelectPin);
uint8_t spiFrame8(bool Write, byte address);
uint16_t  spiFrame(bool Write, byte address, byte data);
void spiSegmentationStart(void);
void spiSegmentationEnd(void);
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

uint8_t spiFrame8(bool Write, byte address)
{
      uint8_t retour =0;
      retour = Write << 7;
      retour += (address&0x7F);
      return retour;
}

uint16_t spiFrame(bool Write, byte address, byte data)
{
      uint16_t retour =0;
      retour = Write << 15;
      retour += (address&0x7F) << 8;
      retour += data;
      return retour;
}

void spiSegmentationStart(void)
{
      digitalWrite(slaveSelectPin, LOW);
      delayMicroseconds(2*segmentationDelay);
}

void spiSegmentationEnd(void)
{
      delayMicroseconds(segmentationDelay);
      digitalWrite(slaveSelectPin, HIGH);
}

void spiWriteRegister(uint8_t address, uint8_t data)
//Optimisable SPECIAL CASE OF BURST WRITE
{
    spiSegmentationStart();
	SPI.transfer16(spiFrame(1, address, data));
    spiSegmentationEnd();
}


void spiBurstWriteRegister(uint8_t address, void *data, size_t dataSize)
{
	void *dataBis = malloc(dataSize * sizeof(void));
	memcpy(dataBis, data, dataSize* sizeof(void));
	// Theses sausages are used to compensate for the arduino library modifying the data array
	// find a way to compensate for multiple malloc ? having a part of memory just for BurstWrite ?
	
	spiSegmentationStart();
	SPI.transfer(spiFrame8(true, address));
	SPI.transfer(dataBis, dataSize);
	spiSegmentationEnd();
	free(dataBis);
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