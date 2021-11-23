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
	
// TESTS
	#define RFM69_FIFOTHRESH_TXSTARTCONDITION_NOTEMPTY 0x80
	#define RFM69_TESTDAGC_CONTINUOUSDAGC_IMPROVED_LOWBETAOFF 0x30
	


//########  #### ########    ########     ###    ######## ######## 
//##     ##  ##     ##       ##     ##   ## ##      ##    ##       
//##     ##  ##     ##       ##     ##  ##   ##     ##    ##       
//########   ##     ##       ########  ##     ##    ##    ######   
//##     ##  ##     ##       ##   ##   #########    ##    ##       
//##     ##  ##     ##       ##    ##  ##     ##    ##    ##       
//########  ####    ##       ##     ## ##     ##    ##    ######## 
// (G)FSK/(G)MSK BITRATE ONLY UNLESS OTHERWISE SPECIFIED :

	#define BR1_2K		0x682B		//ALSO OOK BITRATE
	#define BR2_4K		0x3415		//ALSO OOK BITRATE
	#define BR4_8K		0x1A0B		//ALSO OOK BITRATE
	#define BR9_6K		0x0D05		//ALSO OOK BITRATE
	#define BR19_2K		0x0683		//ALSO OOK BITRATE
	#define BR38_4K		0x0341
	#define BR76_8K		0x01A1
	#define BR153_6K	0x00D0
	
	#define BR57_6K		0x022C
	#define BR115_2K	0x0116

	#define BR12_5K		0x0A00		//ALSO OOK BITRATE	
	#define BR25K		0x0500		//ALSO OOK BITRATE
	#define BR50K		0x0280
	#define BR100K		0x0140
	#define BR150K		0x00D5
	#define BR200K		0x00A0
	#define BR250K		0x0080
	#define BR300K		0x006B
	
	#define BR32_768K	0x03D1		//ALSO OOK BITRATE
	
	

//########  ##     ## ########  ##      ##               ######## #### ##       ######## ######## ########  
//##     ##  ##   ##  ##     ## ##  ##  ##               ##        ##  ##          ##    ##       ##     ## 
//##     ##   ## ##   ##     ## ##  ##  ##               ##        ##  ##          ##    ##       ##     ## 
//########     ###    ########  ##  ##  ##    #######    ######    ##  ##          ##    ######   ########  
//##   ##     ## ##   ##     ## ##  ##  ##               ##        ##  ##          ##    ##       ##   ##   
//##    ##   ##   ##  ##     ## ##  ##  ##               ##        ##  ##          ##    ##       ##    ##  
//##     ## ##     ## ########   ###  ###                ##       #### ########    ##    ######## ##     ## 
// (G)FSK/(G)MSK RXBW FILTER ONLY 
// FOR OOK MODULATION THE VALUE WILL BE HALF the written one

	#define RXBW2_6K	0x17
	#define RXBW3_1K	0x0F
	#define RXBW3_9K	0x07
	#define RXBW5_2K	0x16
	#define RXBW6_3K	0x0E
	#define RXBW7_8K	0x06
	#define RXBW10_4K	0x15
	#define RXBW12_5K	0x0D
	#define RXBW15_6K	0x05
	#define RXBW20_8K	0x14
	#define RXBW25K		0x0C
	#define RXBW31_3K	0x04
	#define RXBW41_7K	0x13
	#define RXBW50K		0x0B
	#define RXBW62_5K	0x03
	#define RXBW83_3K	0x12
	#define RXBW100K	0x0A
	#define RXBW125K    0x02
	#define RXBW166_7K  0x11
	#define RXBW200K    0x09
	#define RXBW250K    0x01
	#define RXBW333_3K  0x10
	#define RXBW400K    0x08
	#define RXBW500K    0x00
	
	

//########  ##     ## ########  ##      ##               ########   ######   ######  
//##     ##  ##   ##  ##     ## ##  ##  ##               ##     ## ##    ## ##    ## 
//##     ##   ## ##   ##     ## ##  ##  ##               ##     ## ##       ##       
//########     ###    ########  ##  ##  ##    #######    ##     ## ##       ##       
//##   ##     ## ##   ##     ## ##  ##  ##               ##     ## ##       ##       
//##    ##   ##   ##  ##     ## ##  ##  ##               ##     ## ##    ## ##    ## 
//##     ## ##     ## ########   ###  ###                ########   ######   ###### 
// DEFAULT VALUE OF DCC FREQ IS 4%
// THE VALUE IS IN % OF RXBW

	#define DCCF16 		0x00
	#define DCCF8 		0x20
	#define DCCF4 		0x40
	#define DCCF2 		0x60
	#define DCCF1 		0x80
	#define DCCF_5 		0xA0
	#define DCCF_25 	0xC0
	#define DCCF_125 	0xE0





#endif _RFM69_DEF_H
