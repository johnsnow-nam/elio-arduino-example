#include "packet.h"



#pragma pack(1)
typedef struct
{ 
  byte cmd;
  byte len;
  byte data[256];
} command_t;
#pragma pack()


#define UDP  0x30
#define CMD_EXECUTE  0x01

byte  g_dc1= 0, g_dc2= 0, g_sv1= 0, g_sv2 = 0, 
      g_v3= 0, g_v5= 0, g_io1= 0, g_io2= 0, g_io3= 0, g_io4= 0, 
      g_sonic= 0 , g_line1= 0, g_line2 = 0 ;


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


void decideToUseSensor( byte ultra, byte line1, byte line2)
{
  byte buffer[15];
  memset(buffer, 0x00, sizeof(buffer));
  
  buffer[0] = UDP;
  buffer[1] = CMD_EXECUTE;

  buffer[2] = g_dc1;
  buffer[3] = g_dc2;
  buffer[4] = g_sv1;
  buffer[5] = g_sv2;
  buffer[6] = g_v3;
  buffer[7] = g_v5;
  buffer[8] = g_io1;
  buffer[9] = g_io2;
  buffer[10] = g_io3;
  buffer[11] = g_io4;

  buffer[12] = ultra;
  buffer[13] = line1;
  buffer[14] = line2;
  
  packet.send_packet(buffer, 15);

}

void sendIO(String which_io, byte value){


  byte buffer[10];
  memset(buffer, 0x00, sizeof(buffer));

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

}


void sendIOS(byte v3, byte v5, byte io1, byte io2, byte io3, byte io4){
  byte buffer[10];
  memset(buffer, 0x00, sizeof(buffer));
  
  buffer[4] = v3; 
  buffer[5] = v5; 
  buffer[6] = io1; 
  buffer[7] = io2; 
  buffer[8] = io3; 
  buffer[9] = io4; 

  send_command((uint8_t) 'M', buffer,  10);
}



void sendDC(String which_dc, byte dc)
{
  byte buffer[10];
  memset(buffer, 0x00, sizeof(buffer));
  
  if (which_dc == "DC1")
    buffer[0] = dc; 
  else if (which_dc == "DC2")
    buffer[1] = dc; 

  send_command((uint8_t) 'M', buffer, 10);

}


void sendDCS(byte dc1, byte dc2){
  byte buffer[10];
  memset(buffer, 0x00, sizeof(buffer));

    buffer[0] = dc1; 
    buffer[1] = dc2; 

  send_command((uint8_t) 'M', buffer,  10);

}

void sendServo(String which_sv, byte sv){
  byte buffer[10];
  memset(buffer, 0x00, sizeof(buffer));

  if (which_sv == "SV1")
    buffer[2] = sv; 
  else if (which_sv == "SV2")
    buffer[3] = sv; 
  send_command((uint8_t) 'M', buffer, 10);
  
}

void sendServos(byte sv1, byte sv2){
    byte buffer[10];
  memset(buffer, 0x00, sizeof(buffer));

  buffer[2] = sv1; 
  buffer[3] = sv2;
  send_command((uint8_t) 'M', buffer, 10);

}

void sendAllPower(  byte dc1, byte dc2, 
          byte sv1, byte sv2,
          byte v3, byte v5,
          byte io1, byte io2, byte io3, byte io4){

  byte buffer[10];
  memset(buffer, 0x00, sizeof(buffer));
  
  buffer[0] = dc1; 
  buffer[1] = dc2;

  buffer[2] = sv1; 
  buffer[3] = sv2;

  
  buffer[4] = v3; 
  buffer[5] = v5; 
  buffer[6] = io1; 
  buffer[7] = io2; 
  buffer[8] = io3; 
  buffer[9] = io4; 

  send_command((uint8_t) 'M', buffer, 10);
  
}

int getDC(String which_dc){
  if (which_dc == "DC1")
    return g_dc1; 
  else if (which_dc == "DC2")
    return g_dc2; 
}

int getIO(String which_io){
  if (which_io == "IO1")
    return g_io1; 
  else if (which_io == "IO2")
    return g_io2; 
  else if (which_io == "IO3")
    return g_io3; 
  else if (which_io == "IO4")
    return g_io3; 
  else if (which_io == "3V")
    return g_v3; 
  else if (which_io == "5V")
    return g_v5; 
}

int getServo(String which_sv){
  if (which_sv == "SV1")
    return g_sv1; 
  else if (which_sv == "SV2")
    return g_sv2; 
}


int getLine1(){
  return g_line1;
}

int getLine2() {
  return g_line1;
}

int getSonic() {
  return g_sonic;
}

void on_packet_complete_handler(uint8_t* data, int len) {

        byte cmd = data[0];
        byte udp = data[1];

        g_dc1 = data[2];
        g_dc2 = data[3];

        g_sv1 = data[4];
        g_sv2 = data[5];

        g_v3 = data[6];
        g_v5 = data[7];

        g_io1 = data[8];
        g_io2 = data[9];
        g_io3 = data[10];
        g_io4 = data[11];

        g_sonic = (data[12] | data[13] << 8);

        g_line1 = (data[14] | data[15] << 8) == 0 ? 1 : 0;
        g_line2 = (data[16] | data[17] << 8) == 0 ? 1 : 0;
}

void packet_write_handler(uint8_t ch) {
      Serial.write(ch); 
}
