#ifndef _RFM69_H
#define _RFM69_H
#include <arduino.h>
#include <math.h>
#include "rfm69_reg.h"
#include "rfm69_def.h"
#include "spi_DIY.h"

#define VERSION 1.3


void rfmSetOPMode(uint8_t mode);
void rfmSetDataMode(uint8_t mode);
void rfmSetModulation(uint8_t modulation);
void rfmSetDeviation(uint32_t deviation);
void rfmSetCarrierFrequency(uint32_t frequency);
void rfmSetOCP(bool enable, uint8_t current);
void rfmSetPower(int8_t powerLevel);


uint8_t rfmGetOPMode();
uint8_t rfmGetDataMode();
uint8_t rfmGetModulation();


bool rfmIsPacketSent(void);
bool rfmIsPayloadReady(void);
bool rfmIsCrcOK(void);

// HARDWARE DEPENDANT FUNCTION START 
void rfmPrintRegister(uint8_t reg);
void rfmPrintRegisters(void);



/****************************************
 * void rfmSetOPMode(uint8_t mode);
 *
 * Set transceiver mode to given mode
 * Modes are defined in rfm69_def
 * Datasheet specified that for RX, PA1 and 2 should be in off state
 * For this reason all transition to RX state disable theses amplifier.
 * 
 ****************************************/
void rfmSetOPMode(uint8_t mode)
{
    if(OP_MODE_RX == mode)
    {
        spiWriteRegister(RFM69_REG_PA1_MODE, 0x55);
        spiWriteRegister(RFM69_REG_PA2_MODE, 0x70);
    }
    spiWriteRegister(RFM69_REG_OP_MODE, (spiReadRegister(RFM69_REG_OP_MODE) & OP_MODE_MASK) | mode); 
}


/****************************************
 * uint8_t rfmGetOPMode();
 *
 * Get the rfm operating mode and return it as defined in rfm69_def*
 * 
 ****************************************/
uint8_t rfmGetOPMode()
{
	return spiReadRegister(RFM69_REG_OP_MODE) & OP_MODE_MSEL;
}


/****************************************
 * void rfmSetDataMode(uint8_t mode);
 *
 * Set transceiver data mode
 * Data modes are defined in rfm69_def
 * 
 ****************************************/
void rfmSetDataMode(uint8_t dataMode)
{
    spiWriteRegister(RFM69_REG_DATA_MOD_MODE, (spiReadRegister(RFM69_REG_DATA_MOD_MODE) & DATA_MODE_MASK) | dataMode); 
}


/****************************************
 * uint8_t rfmGetDataMode();
 *
 * Get the rfm data mode and return it as defined in rfm69_def*
 * 
 ****************************************/
uint8_t rfmGetDataMode()
{
	return spiReadRegister(RFM69_REG_DATA_MOD_MODE) & DATA_MODE_MSEL;
}


/****************************************
 * void rfmSetModulation(uint8_t modulation);
 *
 * Set transceiver modulation type
 * Modulations are defined in rfm69_def
 * 
 ****************************************/
void rfmSetModulation(uint8_t modulation)
{
    spiWriteRegister(RFM69_REG_DATA_MOD_MODE, (spiReadRegister(RFM69_REG_DATA_MOD_MODE) & MODULATION_MASK) | modulation); 
}


/****************************************
 * uint8_t rfmSGetModulation();
 *
 * Get the rfm modulation mode and return it as defined in rfm69_def*
 * 
 ****************************************/
uint8_t rfmGetModulation()
{
    return spiReadRegister(RFM69_REG_DATA_MOD_MODE) & MODULATION_MASK;
}


/****************************************
 * void rfmSetDeviation(uint32_t deviation);
 *
 * Set frequency deviation "deviation" 
 * "deviation" is rounded by "SYNTHESIZER_STEP" steps
 * Frequency deviation should be of at least 600Hz
 *
 * Writing in Burst Mode, make this function 2 times faster 
 * than writing each of the 2 deviation freq registers
 * 
 ****************************************/
void rfmSetDeviation(uint32_t deviation)
{
    if(MIN_F_DEVIATION < deviation && deviation <= MAX_F_DEVIATION)
    {
        deviation = round((float)deviation/(float)SYNTHESIZER_STEP);
		uint8_t deviationA[2] = {(uint8_t)(deviation >> 8), (uint8_t)deviation};
        
		spiBurstWriteRegister(RFM69_REG_FDEV_MSB, &deviationA, 2);
    }
}


/****************************************
 * void rfmSetCarrierFrequency(uint32_t frequency);
 *
 * Set carrier frequency  "frequency" 
 * "frequency" is rounded by "SYNTHESIZER_STEP" steps
 * Writing in Burst Mode, make this function 3 times faster 
 * than writing each of the 3 carrier freq registers
 * 
 ****************************************/
void rfmSetCarrierFrequency(uint32_t frequency)
{
    frequency = round((float)frequency/(float)SYNTHESIZER_STEP);
	uint8_t frequencyA[3] = {(uint8_t)(frequency >> 16), (uint8_t)(frequency >> 8), (uint8_t)frequency};
    
	spiBurstWriteRegister(RFM69_REG_CARR_FREQ_MSB, &frequencyA, 3);

}


/****************************************
 * void rfmSetOCP(bool enable, uint8_t current);
 *
 * Enable or disable the Over Current Protection
 * true  => enabling
 * false => disabling 
 * Current is rounded by 5mA inside RFM 
 * Current should be [0 to 15]
 * current useless if OCP disabled
 * OCP Current : Imax(mA) = 45 + 5*current
 * 
 ****************************************/
void rfmSetOCP(bool enable, uint8_t current)
{
    if(enable)
    {
        spiWriteRegister(RFM69_REG_OCP, 0x10 | (0x0F & current));
    }
    else
    {
        spiWriteRegister(RFM69_REG_OCP, 0x00);
    }
}


/****************************************
 * void rfmSetPower(int8_t powerLevel);
 *
 * Set the register and power amplifiers to requested power level
 * The minimal configuration (less power amplifier ON) will be choosen
 * 
 ****************************************/

 //////////////////////////////////////////////////////////////////////////// TODO
 // Another way of switching to 20dBm mode should be though of
 // IS masking data with 0x1F really useful ?
 // 
void rfmSetPower(int8_t powerLevel)
{
    if(-18 <= powerLevel && powerLevel < -2)
    {
        powerLevel += 18;
        spiWriteRegister(RFM_69_REG_PA_LEVEL, 0x80 | (0x1F & powerLevel));
        spiWriteRegister(RFM69_REG_PA1_MODE, 0x55);
        spiWriteRegister(RFM69_REG_PA2_MODE, 0x70);  
    }
    else if(-2 <= powerLevel && powerLevel <= 13)
    {
        powerLevel +=18;
        spiWriteRegister(RFM_69_REG_PA_LEVEL, 0x40 | (0x1F & powerLevel));
        spiWriteRegister(RFM69_REG_PA1_MODE, 0x55);
        spiWriteRegister(RFM69_REG_PA2_MODE, 0x70); 
    }
    else if(13 < powerLevel && powerLevel <= 17)
    {
        powerLevel +=14;
        spiWriteRegister(RFM_69_REG_PA_LEVEL, 0x60 | (0x1F & powerLevel));
        spiWriteRegister(RFM69_REG_PA1_MODE, 0x55);
        spiWriteRegister(RFM69_REG_PA2_MODE, 0x70); 
    }
    else if(17 < powerLevel && powerLevel <=20)
    {
        powerLevel +=11;
        spiWriteRegister(RFM_69_REG_PA_LEVEL, 0x60 | (0x1F & powerLevel));
        spiWriteRegister(RFM69_REG_PA1_MODE, 0x5D);
        spiWriteRegister(RFM69_REG_PA2_MODE, 0x7C);
    }
}


/****************************************
 * void rfmSetBR(uint16_t bitRate);
 *
 * set the 0x03 and 0x04 bitrate register to the corresponding 
 * value defined in rfm69_def.h
 * 
 ****************************************/
void rfmSetBR(uint16_t bitRate)
{
	spiWriteRegister(RFM69_REG_BITRATE_MSB, (uint8_t)(bitRate >> 8));
	spiWriteRegister(RFM69_REG_BITRATE_LSB, (uint8_t)bitRate);
}


/****************************************
 * bool rfmIsPacketSent(void);
 *
 * Check the corresponding bit in the RFM module to know :
 * if the packet have been sent
 * return true on packet sent
 * 
 ****************************************/
bool rfmIsPacketSent(void)
{
	return ((spiReadRegister(RFM69_REG_IRQ2) & 0x04) > 0);	
}
	

/****************************************
 * bool rfmIsPayloadReady(void);
 *
 * Check the corresponding bit in the RFM module to know
 * if the payload is ready
 * return true on payload ready in fifo
 * 
 ****************************************/
bool rfmIsPayloadReady(void)
{
	return ((spiReadRegister(RFM69_REG_IRQ2) & 0x02) > 0);
}


/****************************************
 * bool rfmIsCrcOK(void);
 *
 * Check the corresponding bit in the RFM module to know
 * if the CRC is valid or not
 * return true on crc valid
 * 
 ****************************************/
bool rfmIsCrcOK(void)
{
	return ((spiReadRegister(RFM69_REG_IRQ2) & 0x01) > 0);
}


/*******************************************************************************************************************
 *
 *
 *									HARDWARE DEPENDANT SECTION
 *
 * 
 ******************************************************************************************************************/



/**************************************** WARNING HARDWARE DEPENDANT FUNCTION
 * void rfmPrintRegister(uint8_t reg);
 *
 * Print the register specified in parameter
 * 
 ****************************************/
void rfmPrintRegister(uint8_t reg)
{
    Serial.print(reg, HEX);
    Serial.print(" ");
    Serial.println(spiReadRegister(reg), HEX);
}


/**************************************** WARNING HARDWARE DEPENDANT FUNCTION
 * void rfmPrintRegisters(void);
 *
 * The 's' is not silent
 * This function will print all RFM69 registers
 ****************************************/
void rfmPrintRegisters(void)
{
	uint8_t i;
	
	for (i = 1; i < 0x50; i++)
	{
		rfmPrintRegister(i);
	}
	
    // Non-contiguous registers
    rfmPrintRegister(RFM69_REG_TEST_LNA);
    rfmPrintRegister(RFM69_REG_PA1_MODE);
    rfmPrintRegister(RFM69_REG_PA2_MODE);
	rfmPrintRegister(RFM69_REG_TEST_DAGC);
	rfmPrintRegister(RFM69_REG_TEST_AFC);	
}

#endif
