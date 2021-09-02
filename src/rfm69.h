#ifndef _RFM69_H
#define _RFM69_H
#include <arduino.h>
#include <math.h>
#include "rfm69_reg.h"
#include "rfm69_def.h"
#include "spi_DIY.h"

#define VERSION 1.1


void rfmSetOPMode(uint8_t mode);
void rfmSetDataMode(uint8_t mode);
void rfmSetModulation(uint8_t modulation);
void rfmSetDeviation(uint32_t deviation);
void rfmSetCarrierFrequency(uint32_t frequency);
void rfmSetOCP(bool enable, uint8_t current);
void rfmSetPower(int8_t powerLevel);

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
 * void rfmSetDeviation(uint32_t deviation);
 *
 * Set frequency deviation "deviation" 
 * "deviation" is rounded by "SYNTHESIZER_STEP" steps
 * Frequency deviation should be of at least 600Hz
 * 
 ****************************************/
void rfmSetDeviation(uint32_t deviation)
{
    if(MIN_F_DEVIATION < deviation && deviation <= MAX_F_DEVIATION)
    {
        deviation = round((float)deviation/(float)SYNTHESIZER_STEP);
        
        spiWriteRegister(RFM69_REG_FDEV_LSB, (uint8_t)deviation);
        spiWriteRegister(RFM69_REG_FDEV_MSB, (uint8_t)(deviation >> 8)); 
    }
}


/****************************************
 * void rfmSetCarrierFrequency(uint32_t frequency);
 *
 * Set carrier frequency  "frequency" 
 * "frequency" is rounded by "SYNTHESIZER_STEP" steps
 * 
 ****************************************/
void rfmSetCarrierFrequency(uint32_t frequency)
{
    frequency = round((float)frequency/(float)SYNTHESIZER_STEP);
    
    spiWriteRegister(RFM69_REG_CARR_FREQ_LSB, (uint8_t)frequency);
    spiWriteRegister(RFM69_REG_CARR_FREQ_MID, (uint8_t)(frequency >> 8));
    spiWriteRegister(RFM69_REG_CARR_FREQ_MSB, (uint8_t)(frequency >> 16)); 
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
    else if(-2 <= powerLevel && powerLevel < 2)
    {
        powerLevel +=18;
        spiWriteRegister(RFM_69_REG_PA_LEVEL, 0x40 | (0x1F & powerLevel));
        spiWriteRegister(RFM69_REG_PA1_MODE, 0x55);
        spiWriteRegister(RFM69_REG_PA2_MODE, 0x70); 
    }
    else if(2 <= powerLevel && powerLevel <= 17)
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



#endif
