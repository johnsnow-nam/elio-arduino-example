#ifndef ELIO_H
#define ELIO_H

#include <Arduino.h>
#include "packet.h"

#pragma pack(1)
typedef struct
{
    byte cmd;
    byte len;
    byte data[256];
} command_t;
#pragma pack()

// 센서 마스크
typedef enum
{
    sensor_none = 0x00,  // all external device is disabled
    sensor_sonic = 0x01, // sonic sensor is enabled (5V, IO-1, IO-2)
    sensor_line1 = 0x02, // line track (3V, IO-3)
    sensor_line2 = 0x04, // line track (3V, IO-4)
    sensor_line = (sensor_line1 | sensor_line2),
} sensor_t;

#pragma pack(1)
typedef struct
{
    int8_t dc1;
    int8_t dc2;
    int8_t servo1;
    int8_t servo2;
    int8_t v3;
    int8_t v5;
    int8_t io[4];
    uint8_t sensor_mask;
    uint16_t sonic_cm;
    uint8_t line1;
    uint8_t line2;
} app_uart_status_t;
#pragma pack()

#define cmd_uart_status 0xf6 // status
#define UDP 0x30
#define CMD_EXECUTE 0x01

extern int8_t g_dc1, g_dc2, g_sv1, g_sv2, g_v3, g_v5, g_io1, g_io2, g_io3, g_io4, g_line1, g_line2;
extern int8_t g_sonic;
// extern Packet packet(on_packet_complete_handler, packet_write_handler);

void on_packet_complete_handler(uint8_t *buf, int len);
void packet_write_handler(uint8_t ch);
void send_command(uint8_t cmd, const void *data, uint8_t len);
void decideToUseSensor(String ultra, String line1, String line2);
void sendIO(String which_io, byte value);
void sendIOS(byte v3, byte v5, byte io1, byte io2, byte io3, byte io4);
void sendDC(String which_dc, byte dc);
void sendDCS(byte dc1, byte dc2);
void sendServo(String which_sv, byte sv);
void sendServos(byte sv1, byte sv2);
void sendAllPower(byte dc1, byte dc2, byte sv1, byte sv2, byte v3, byte v5, byte io1, byte io2, byte io3, byte io4);
int getDC(String which_dc);
int getIO(String which_io);
int getServo(String which_sv);
int getLine1();
int getLine2();
int getSonic();
void assembleData();

#endif // ELIO_H
