#include "elio.h"

int8_t g_dc1 = 0, g_dc2 = 0, g_sv1 = 0, g_sv2 = 0,
       g_v3 = 0, g_v5 = 0, g_io1 = 0, g_io2 = 0, g_io3 = 0, g_io4 = 0,
       g_line1 = 0, g_line2 = 0;

int8_t g_sonic = 9999;
Packet packet(on_packet_complete_handler, packet_write_handler);

void send_command(uint8_t cmd, const void *data, uint8_t len)
{
    command_t p;
    p.cmd = cmd;
    p.len = len;
    memcpy(p.data, data, len);

    packet.send_packet((uint8_t *)&p, len + 2);
}

void decideToUseSensor(String ultra, String line1, String line2)
{
    byte buffer[1];
    memset(buffer, 0x00, sizeof(buffer));
    byte mask = 0;

    if (ultra == "ON")
        mask |= sensor_sonic;

    if (line1 == "ON")
        mask |= sensor_line1;

    if (line2 == "ON")
        mask |= sensor_line2;

    buffer[0] = mask;

    send_command(0xf4, buffer, sizeof(buffer));
}

void sendIO(String which_io, byte value)
{
    byte buffer[10];
    memset(buffer, -128, sizeof(buffer));

    buffer[0] = g_dc1;
    buffer[1] = g_dc2;

    buffer[2] = g_sv1;
    buffer[3] = g_sv2;

    buffer[4] = g_v3;
    buffer[5] = g_v5;
    buffer[6] = g_io1;
    buffer[7] = g_io2;
    buffer[8] = g_io3;
    buffer[9] = g_io4;

    if (which_io == "3V")
        g_v3 = buffer[4] = value;
    else if (which_io == "5V")
        g_v5 = buffer[5] = value;
    else if (which_io == "IO1")
        g_io1 = buffer[6] = value;
    else if (which_io == "IO2")
        g_io2 = buffer[7] = value;
    else if (which_io == "IO3")
        g_io3 = buffer[8] = value;
    else if (which_io == "IO4")
        g_io4 = buffer[9] = value;

    send_command((uint8_t)'M', buffer, 10);
}

void sendIOS(byte v3, byte v5, byte io1, byte io2, byte io3, byte io4)
{
    byte buffer[10];
    memset(buffer, -128, sizeof(buffer));

    buffer[0] = g_dc1;
    buffer[1] = g_dc2;

    buffer[2] = g_sv1;
    buffer[3] = g_sv2;

    g_v3 = buffer[4] = v3;
    g_v5 = buffer[5] = v5;
    g_io1 = buffer[6] = io1;
    g_io2 = buffer[7] = io2;
    g_io3 = buffer[8] = io3;
    g_io4 = buffer[9] = io4;

    send_command((uint8_t)'M', buffer, 10);
}

void sendDC(String which_dc, byte dc)
{
    byte buffer[10];
    memset(buffer, -128, sizeof(buffer));

    buffer[0] = g_dc1;
    buffer[1] = g_dc2;

    buffer[2] = g_sv1;
    buffer[3] = g_sv2;

    buffer[4] = g_v3;
    buffer[5] = g_v5;
    buffer[6] = g_io1;
    buffer[7] = g_io2;
    buffer[8] = g_io3;
    buffer[9] = g_io4;

    if (which_dc == "DC1")
        g_dc1 = buffer[0] = dc;
    else if (which_dc == "DC2")
        g_dc2 = buffer[1] = dc;

    send_command((uint8_t)'M', buffer, 10);
}

void sendDCS(byte dc1, byte dc2)
{
    byte buffer[10];
    memset(buffer, -128, sizeof(buffer));

    g_dc1 = buffer[0] = dc1;
    g_dc2 = buffer[1] = dc2;

    buffer[2] = g_sv1;
    buffer[3] = g_sv2;

    buffer[4] = g_v3;
    buffer[5] = g_v5;
    buffer[6] = g_io1;
    buffer[7] = g_io2;
    buffer[8] = g_io3;
    buffer[9] = g_io4;

    send_command((uint8_t)'M', buffer, 10);
}

void sendServo(String which_sv, byte sv)
{
    byte buffer[10];
    memset(buffer, -128, sizeof(buffer));

    buffer[0] = g_dc1;
    buffer[1] = g_dc2;
    buffer[2] = g_sv1;
    buffer[3] = g_sv2;
    buffer[4] = g_v3;
    buffer[5] = g_v5;
    buffer[6] = g_io1;
    buffer[7] = g_io2;
    buffer[8] = g_io3;
    buffer[9] = g_io4;

    if (which_sv == "SV1")
        g_sv1 = buffer[2] = sv;
    else if (which_sv == "SV2")
        g_sv2 = buffer[3] = sv;
    send_command((uint8_t)'M', buffer, 10);
}

void sendServos(byte sv1, byte sv2)
{
    byte buffer[10];
    memset(buffer, -128, sizeof(buffer));
    buffer[0] = g_dc1;
    buffer[1] = g_dc2;

    g_sv1 = buffer[2] = sv1;
    g_sv2 = buffer[3] = sv2;

    buffer[4] = g_v3;
    buffer[5] = g_v5;
    buffer[6] = g_io1;
    buffer[7] = g_io2;
    buffer[8] = g_io3;
    buffer[9] = g_io4;

    send_command((uint8_t)'M', buffer, 10);
}

void sendAllPower(byte dc1, byte dc2,
                  byte sv1, byte sv2,
                  byte v3, byte v5,
                  byte io1, byte io2, byte io3, byte io4)
{
    byte buffer[10];
    memset(buffer, -128, sizeof(buffer));

    g_dc1 = buffer[0] = dc1;
    g_dc2 = buffer[1] = dc2;

    g_sv1 = buffer[2] = sv1;
    g_sv2 = buffer[3] = sv2;

    g_v3 = buffer[4] = v3;
    g_v5 = buffer[5] = v5;
    g_io1 = buffer[6] = io1;
    g_io2 = buffer[7] = io2;
    g_io3 = buffer[8] = io3;
    g_io4 = buffer[9] = io4;

    send_command((uint8_t)'M', buffer, 10);
}

int getDC(String which_dc)
{
    if (which_dc == "DC1")
        return g_dc1;
    else if (which_dc == "DC2")
        return g_dc2;
    return -1;
}

int getIO(String which_io)
{
    if (which_io == "IO1")
        return g_io1;
    else if (which_io == "IO2")
        return g_io2;
    else if (which_io == "IO3")
        return g_io3;
    else if (which_io == "IO4")
        return g_io4;
    else if (which_io == "3V")
        return g_v3;
    else if (which_io == "5V")
        return g_v5;
    return -1;
}

int getServo(String which_sv)
{
    if (which_sv == "SV1")
        return g_sv1;
    else if (which_sv == "SV2")
        return g_sv2;
    return -1;
}

int getLine1()
{
    return g_line1;
}

int getLine2()
{
    return g_line2;
}

int getSonic()
{
    return g_sonic;
}

void assembleData()
{
    char buffer[100];

    if (Serial.available())
    {
        byte recv_len = Serial.readBytes(buffer, sizeof(buffer));
        for (int i = 0; i < recv_len; i++)
        {
            packet.add(buffer[i]);
        }
    }
}

void on_packet_complete_handler(uint8_t *data, int len)
{
    char szMsg[256];
    memset(szMsg, 0x00, sizeof(szMsg));

    command_t *command = (command_t *)data;
    app_uart_status_t *status_packet = (app_uart_status_t *)(command->data);

    Serial.println("-------------------------------------------------------");
    sprintf(szMsg, "(cmd=%02x, len=%d \n", command->cmd, command->len);
    Serial.println(szMsg);

    g_dc1 = status_packet->dc1;
    g_dc2 = status_packet->dc2;

    g_sv1 = status_packet->servo1;
    g_sv2 = status_packet->servo2;

    g_v3 = status_packet->v3;
    g_v5 = status_packet->v5;

    g_io1 = status_packet->io[0];
    g_io2 = status_packet->io[1];
    g_io3 = status_packet->io[2];
    g_io4 = status_packet->io[3];

    g_sonic = status_packet->sonic_cm;

    g_line1 = status_packet->line1;
    g_line2 = status_packet->line2;

    sprintf(szMsg, "(%d,%d) [%d,%d]  {%d,%d, %d,%d,%d,%d} --> %d \n", g_dc1, g_dc2, g_sv1, g_sv2, g_io1, g_io2, g_io3, g_io4, g_v3, g_v5, status_packet->sensor_mask);
    Serial.println(szMsg);
    sprintf(szMsg, "[%d,%d,%d]  ", g_sonic, g_line1, g_line2);
    Serial.println(szMsg);
}

void packet_write_handler(uint8_t ch)
{
    Serial.write(ch);
}
