#ifndef packet_h
#define packet_h

#include <Arduino.h>

#define MAX_PACKET_LEN 512

#include <inttypes.h>

typedef enum
{
    PS_STX,
    PS_DATA,
    PS_ESC
} PacketState;

typedef void (*on_packet_complete_handler_t)(uint8_t *buf, int len);
typedef void (*packet_write_handler_t)(uint8_t ch);

class Packet
{
private:
    PacketState m_state;
    int m_pos;
    uint8_t m_crc;
    uint8_t m_buffer[MAX_PACKET_LEN];
    on_packet_complete_handler_t m_completion_handler;
    packet_write_handler_t m_write_handler;

public:
    Packet(on_packet_complete_handler_t completion_handler, packet_write_handler_t write_handler);
    virtual ~Packet();

protected:
    void add_data(uint8_t ch);

public:
    void add(uint8_t ch);
    void reset();

public:
    //          void write_byte(uint8_t ch,   write_handler);
    void write_byte(uint8_t ch);

    void send_packet(uint8_t *buf, uint16_t len);
};
extern Packet packet;
#endif
