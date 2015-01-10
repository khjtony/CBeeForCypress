#include "CBeeArduinoLib.h"


//				common function/tools
uint8_t _get_char_len(char* msg){
	uint8_t i=0;
	while (msg[i]!='\0' && i<ZISE_OF_UINT8_T){
		i++;
	}
	return i;
}

uint8_t _get_byte_len(byte* msg){
	uint8_t i=0;
	while (msg[i]!='\0' && i<ZISE_OF_UINT8_T){
		i++; 
	}
	return i;
}

byte _checksum(byte* msg,uint8_t msg_len){
  	uint8_t cksum=0;
  	uint8_t i=0;
  	for (i=0;i<msg_len;i++){
  		cksum+=msg[i];
  	}
  	return (0xff-cksum);
}


//				for xbee struct
void XBee_init(struct XBee_t* this){
	this->_get_all_char=&get_all_char;
	this->_frame_compile=&frame_compile;
	this->_set_XBee_addr64=&set_XBee_addr64;
	this->_set_request=&set_request;
}

uint8_t (frame_compile)(struct XBee_t* this){return;}		//may not need this function, because get all char it self should do the compile job
byte* (get_all_char)(struct XBee_t* this){
	uint8_t i=0;
	this->all_len=3+((this->xbee_request)->data_len)+1;
	this->api_all=(byte*)malloc(sizeof(byte)*(this->all_len));
	this->api_all[0]=START_CHAR;
	this->api_all[1]=(this->xbee_request->data_len)>>4;
	this->api_all[2]=(this->xbee_request->data_len)&0x0F;
	printf("All len is: %d\n", this->all_len);
	for (i=0;i<this->xbee_request->data_len;i++){
		this->api_all[i+3]=this->xbee_request->api_content[i];
	}
	this->api_all[(this->all_len)-1]=_checksum(this->xbee_request->api_content,this->xbee_request->data_len);
	printf("checksum is %#02x\n",this->api_all[this->all_len]);
	i=0;
	for (i=0;i<(this->all_len);i++){
		printf("%#02x(%c)(%d) ", this->api_all[i],this->api_all[i],i);
	}
	printf("\n");

	return this->api_all;
}

void (set_XBee_addr64)(struct XBee_t* this, char* addr64){
	 int i=0;
	 for (i=0;i<8;i++){
	 	this->api_self64_addr[i]=(byte)addr64[i];
	 }
	return;
}
void (set_request)(struct XBee_t* this, struct XBee_request_t* in_request){
	// printf("prepare set request in %c to incoming request\n",in_request->api_content[5]);
	this->xbee_request=in_request;

	return;
}


//				for Xbee request struct 
void XBee_request_init(struct XBee_request_t* this){
	this->_get_frame_length=&get_frame_length;
	this->_set_target_addr=&set_target_addr;
	this->_append_content=&append_content;
	this->_addn_content=&addn_content;
	this->_zb_tx_rq=&zb_tx_rq;
	return;
}

uint8_t (get_frame_length)(struct XBee_request_t* this){
	uint8_t len;
	len=1+1+1+1+8+2;
	len+=_get_byte_len(this->api_content);
	return len;
}

void (set_target_addr)(struct XBee_request_t* this, byte* addr64){
	return;
}

void (append_content)(struct XBee_request_t* this, byte* msg){
	uint8_t old_len;
	uint8_t msg_len=_get_byte_len(msg);
	uint8_t new_len;
	byte*	temp;
	uint8_t i;
	old_len=_get_byte_len(this->api_content);
	new_len=_get_byte_len(msg)+old_len;
	if (this->api_content==NULL){
		// this->api_content=(byte*)malloc(sizeof(char)*new_len);
		this->api_content=msg;

	}else{
		old_len=_get_byte_len(this->api_content);  

		new_len=old_len+msg_len;
		temp=(byte*)malloc(sizeof(byte)*(new_len));
		for(i=0;i<old_len;i++){
			temp[i]=this->api_content[i];
		}
		for (i=0;i<msg_len;i++){
			temp[i+old_len]=msg[i];
		}
		temp[new_len-1]='\0';
		this->api_content=temp;
		temp=NULL;
	}
	return;
}

void (addn_content)(struct XBee_request_t* this, byte* msg){
	return;
}
//functions below are tons of avaliable cmd: addr64,addr16,broadcast radius,options,data. ALSO DO LENGTH CHECK
void zb_tx_rq(struct XBee_request_t* this, struct XBee_addr64_t* addr64, struct XBee_addr16_t* addr16, byte radius,byte options,char* msg){
	uint8_t msg_len=_get_byte_len(msg);
	this->data_len=1+1+8+2+1+1+msg_len;
	uint8_t i=0;
	this->api_content=(byte*)malloc(sizeof(byte)*(this->data_len));
	this->api_frame_type=ZB_TX_RQ;
	this->api_frame_id=0x01;
	this->api_content[0]=ZB_TX_RQ;
	this->api_content[1]=0x01;
	addr64->_copy_to(addr64,(this->api_content)+2);
	addr16->_copy_to(addr16,(this->api_content)+10);
	this->api_content[12]=radius;
	this->api_content[13]=options;
	for(i=0;i<msg_len;i++){
		this->api_content[i+2+8+2+2]=msg[i];
	}
	printf("this->data_len = %d\n", this->data_len);
	return;
}







//				for xbee addr64 struct
void XBee_addr64_init(struct XBee_addr64_t* this){
	this->_set_addr=set_addr64;
	this->_copy_to=&copy64_to;
	return;
}

void (set_addr64)(struct XBee_addr64_t* this, byte* addr64){
	uint8_t i=0;
	for (i=0;i<8;i++){
		this->api_frame_addr[i]=addr64[i];
	}
	return;
}

void (copy64_to)(struct XBee_addr64_t* this, byte* addr64){
	uint8_t i=0;
	for (i=0;i<8;i++){
		addr64[i]=this->api_frame_addr[i];
	}
	return;
}


//				for xbee addr16 struct
void XBee_addr16_init(struct XBee_addr16_t* this){
	this->_set_addr=set_addr16;
	this->_copy_to=&copy16_to;
	return;
}

void (set_addr16)(struct XBee_addr16_t* this, byte* addr16){
	this->api_frame_addr[0]=addr16[0];
	this->api_frame_addr[1]=addr16[1];
	return;
}

void (copy16_to)(struct XBee_addr16_t* this, byte* addr16){
	addr16[0]=this->api_frame_addr[0];
	addr16[1]=this->api_frame_addr[1];
	return;
}