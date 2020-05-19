#include "packet.h"

#pragma pack(1)
typedef struct
{ 
  byte cmd;
  byte len;
  byte data[256];
} command_t;
#pragma pack()


void on_packet_complete_handler(uint8_t* buf, int len);
void packet_write_handler(uint8_t ch);
void send_command(uint8_t cmd, const void* data, uint8_t len);

Packet packet(on_packet_complete_handler,  packet_write_handler);

void send_command(uint8_t cmd, const void* data, uint8_t len)
{
  command_t p;
  p.cmd = cmd;
  p.len = len;
  memcpy(p.data, data, len);

  packet.send_packet((uint8_t*)&p, len + 2);
}

void sendIO(String which_io, byte value){
	byte* buffer = new byte[10]; 
	memset(buffer, -128, 12); 

	if (which_io == "3V")
		buffer[4] = value; 
	else if (which_io == "5V")
		buffer[5] = value; 
	else if (which_io == "IO1")
		buffer[6] = value; 
	else if (which_io == "IO2") 
		buffer[7] = value; 
	else if (which_io == "IO3") 
		buffer[8] = value; 
	else if (which_io == "IO4") 
		buffer[9] = value; 

	send_command((uint8_t) 'M', buffer,  10);

	delete[] buffer;
}






void sendDC(byte dc1, byte dc2){
  byte* buffer = new byte[10]; 
  memset(buffer, -128, 10); 
  buffer[0] = dc1; 
  buffer[1] = dc2;
  send_command((uint8_t) 'M', buffer, 10);
  delete[] buffer;

}

void sendServo(byte sv1, byte sv2){
	byte* buffer = new byte[10]; 
	memset(buffer, -128, 12); 
	buffer[2] = sv1; 
	buffer[3] = sv2;
	send_command((uint8_t) 'M', buffer, 10);
  delete[] buffer;

}



void on_packet_complete_handler(uint8_t* buf, int len) {
}

void packet_write_handler(uint8_t ch) {
      Serial.write(ch); 
}
