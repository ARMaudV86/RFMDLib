#ifndef _RFM69_REG_H
#define _RFM69_REG_H


#define ADDR_OP_MODE 7 

#define RFM69_REG_FIFO				0x00

#define RFM69_REG_OP_MODE           0x01
#define RFM69_REG_DATA_MOD_MODE     0x02
#define RFM69_REG_BITRATE_MSB		0x03
#define RFM69_REG_BITRATE_LSB		0x04
#define RFM69_REG_FDEV_MSB          0x05
#define RFM69_REG_FDEV_LSB          0x06
#define RFM69_REG_CARR_FREQ_MSB     0x07
#define RFM69_REG_CARR_FREQ_MID     0x08
#define RFM69_REG_CARR_FREQ_LSB     0x09

#define RFM_69_REG_PA_LEVEL         0x11

#define RFM69_REG_OCP               0x13

#define RFM69_REG_RX_FILTER			0x19
#define RFM69_REG_AFC_FILTER		0x1A

#define RFM69_REG_IRQ2				0x28

#define RFM69_REG_PYLD_LGHT			0x38
#define RFM69_REG_AUTO_MODE			0x3B
#define RFM69_REG_FIFO_TRSH			0x3C


// NON CONTIGUOUS REGISTERS
#define RFM69_REG_TEST_LNA			0x58
#define RFM69_REG_PA1_MODE          0x5A
#define RFM69_REG_PA2_MODE          0x5C
#define RFM69_REG_TEST_DAGC			0x6F
#define RFM69_REG_TEST_AFC			0x71









#endif _RFM69_REG_H
