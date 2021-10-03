#ifndef _RFM69_REG_H
#define _RFM69_REG_H


#define ADDR_OP_MODE 7 

#define RFM69_REG_FIFO				0x00

#define RFM69_REG_OP_MODE           0x01
#define RFM69_REG_DATA_MOD_MODE     0x02

#define RFM69_REG_FDEV_MSB          0x05
#define RFM69_REG_FDEV_LSB          0x06

#define RFM69_REG_CARR_FREQ_MSB     0x07
#define RFM69_REG_CARR_FREQ_MID     0x08
#define RFM69_REG_CARR_FREQ_LSB     0x09

#define RFM_69_REG_PA_LEVEL         0x11

#define RFM69_REG_OCP               0x13

#define RFM69_REG_IRQ2				0x28

#define RFM69_REG_PYLD_LGHT			0x38
#define RFM69_REG_AUTO_MODE			0x3B
#define RFM69_REG_FIFO_TRSH			0x3C

#define RFM69_REG_PA1_MODE          0x5A
#define RFM69_REG_PA2_MODE          0x5C





#define RFM69B_ADDR_AGC2        0x6A
#define RFM69B_ADDR_MODCNTL     0x71
#define RFM69B_ADDR_FREQDEV     0x72
#define RFM69B_ADDR_BANDSEL     0x75
#define RFM69B_ADDR_CARRFREQ1   0x76
#define RFM69B_ADDR_CARRFREQ0   0x77


#endif _RFM69_REG_H
