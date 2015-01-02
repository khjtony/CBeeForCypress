#ifndef CBeeArduinoLib_H
#define CBeeArduinoLib_H

#include "Arduino"


//*************************************************//
//					API Frame names & ID
//*************************************************//
#define		AT_CMD			0x08		//AT command
#define		AT_CMD_QPV		0x09		//AT command--queue parameter value
#define		ZB_TM_RQ		0X10		//ZigBee Transmit Request	
#define 	ZB_ADD_CMD		0X11		//Explicit Add ZigBee command Frame
#define 	RMT_CMD_RQ		0X17		//Remote Command Remote request
#define		CRT_SRC_RUT		0X21		//Create Source Route
#define		AT_CMD_RSP		0X88		//AT command Response
#define		MOD_STA			0X8A		//Modem Status
#define 	ZB_TM_STA		0x8B		//ZigBee Transmit Status
#define		ZB_REC_PCT		0x90		//ZigBee Receive Packet(AO=0)
#define		ZB_RX_IND		0x91		//ZigBee Explicit Rx Indicator (AO=1)
#define		ZB_IO_RX_IND	0x92		//ZigBee IO data sample Rx indicator
#define		XB_SEN_IND		0x94		//XBee Sensor Read Indicator (AO=0)
#define		NODE_ID_IND		0x95		//Node Identification Indicator
#define		RMT_CMD_RSP		0x97		//Remote Command Response
#define		ON_AIR_UPDATE	0xA0		//Over the air Firmware Update status
#define		RUT_REC_IND		0xA1		//Route Record indicator
#define		MANY_TO_ONE_IND	0xA3		//Many to one route request indicator


typedef struct _apiFrameUnion{
	Byte api_id;
	Byte api_len_L;
	Byte api_len_H;
	Byte*api_data;
	Byte api_frameType;
	Byte api_frameID;
	Byte api_checksum;
	Byte api_hdAdd[8];
	Byte api_netAdd[2];
	Byte*api_pkg;
} XBeeDataPKG;


void _escapeCheck();
void _calChecksum();
void _verifyChecksum();
int  _msgLength();










