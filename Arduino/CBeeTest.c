#include "CBeeArduinoLib.h"
#include "stdio.h"
#include "stdlib.h"


int main(){
	char addr[2];
	addr[0]='a';
	addr[1]='b';
	XBee coordinator;
	XBee_init(&coordinator);
	printf("This is addr64 for coordinator after init: %s\n",coordinator.api_self64_addr);
	XBee_addr16 addr16;
	XBee_addr16_init(&addr16);
	addr16._set_addr(&addr16,addr);
	printf("This is addr16 for addr16 after init: %c%c\n",addr16.api_frame_addr[0],addr16.api_frame_addr[1]);
}
