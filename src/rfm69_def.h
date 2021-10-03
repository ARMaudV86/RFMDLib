#ifndef _RFM69_DEF_H
#define _RFM69_DEF_H

/*  This File contain all the defines for register values
*/

// GENERAL PURPOSE VALUES
    #define SYNTHESIZER_STEP    61.03515625 // Frequency synthesizer step in Hz Fosc/2^19
    #define MIN_F_DEVIATION     600
    #define MAX_F_DEVIATION     300000


//OP_MODE_REGISTER VALUES
    #define OP_MODE_MASK        0xE3
	#define OP_MODE_MSEL		0x1C
	
    #define OP_MODE_SLEEP       0x00
    #define OP_MODE_STDBY       0x04
    #define OP_MODE_FS          0x08
    #define OP_MODE_TX          0x0C
    #define OP_MODE_RX          0x10

//DATA_MODULATION_REGISTER
    #define DATA_MODE_MASK      0x9F
	#define DATA_MODE_MSEL		0x60
    #define DATA_MODE_PCK       0x00
    #define DATA_MODE_CONT_WS   0x40    // Continuous Mode with bit synchronizer
    #define DATA_MODE_CONT      0x60

    #define MODULATION_MASK     0xE7
	#define MODULATION_MSEL     0x18
    #define MODULATION_FSK      0x00
    #define MODULATION_OOK      0x08
    // TODO MODULATION SHAPING
	
//AUTO MODE SETTINGS
	#define AUTO_MODE_SLEEP		0x00
	#define AUTO_MODE_STDBY		0x01
	#define AUTO_MODE_RX		0x02
	#define AUTO_MODE_TX		0x03
	
	// #define AUTO_MODE_NONE 			0x00
	// #define AUTO_MODE_FIFO_NT_EMPT	0x01
	// #define AUTO_MODE_FIFO_LVL 		0x02
	// #define AUTO_MODE_CRC_OK			0x03
	// #define AUTO_MODE_PYLD_RDY		0x04
	// #define AUTO_MODE_SYNC_ADDR		0x05
	// #define AUTO_MODE_PCK_SENT		0x06
	// #define AUTO_MODE_FIFO_EMPTY		0x07
	// #define AUTO_MODE_TIMEOUT		0x07
	





#endif _RFM69_DEF_H
