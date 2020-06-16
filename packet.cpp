#include "packet.h"

#define STX 0x02
#define ETX 0x03
#define ESC 0x23
#define DLE 0x40

#define DEFAULT_CRC    0xff

Packet::Packet(on_packet_complete_handler_t completion_handler, packet_write_handler_t write_handler)
{
    m_completion_handler       = completion_handler;
      m_write_handler = write_handler;

    reset();
}

Packet::~Packet()
{
    
}

void Packet::reset()
{
  m_pos   = 0;
    m_state = PS_STX;
    m_crc   = DEFAULT_CRC;
}

void Packet::add_data(uint8_t ch)
{
    if (m_pos >= MAX_PACKET_LEN)
    {
        reset();
        return;
    }

    m_crc ^= ch;                    // update crc
    m_buffer[m_pos++] = ch;            // add ch to buffer
}

void Packet::add(uint8_t ch)
{
    if (ch == STX)
    {
        reset();
    }
    
    switch (m_state)
    {
        case PS_STX:
          m_state = PS_DATA;
        break;
        case PS_DATA:
            if (ch == ETX)
            {
                        m_state = PS_STX;
                
                if (m_pos >= 2 && m_crc == 0)
                        {
                            m_pos--;
                 
                            if (m_completion_handler)
                                m_completion_handler(m_buffer, m_pos);
                            return;
                        }
            }
            else if (ch == ESC)
            {
                m_state = PS_ESC;
            }
            else
            {
                if (ch < ETX)
                {
                    reset();
                }
                else
                {
                    add_data(ch);
                }
            }
            break;
        case PS_ESC:
            if (ch == ESC)
            {
               m_state = PS_DATA;
                add_data(ch);
            }
            else
            {
                m_state = PS_DATA;
                add_data(ch ^ DLE);
            }
            break;
        default:
            break;
    }
}

void Packet::write_byte(uint8_t ch)
{
    if (ch <= ETX)
    {
        m_write_handler(ESC);
        ch = ch ^ DLE;
    }
    else if (ch == ESC)
    {
        m_write_handler(ESC);
    }
    m_write_handler(ch);
}

void Packet::send_packet(uint8_t* buf, uint16_t len)
{
    if (m_write_handler == NULL)
        return;

    m_write_handler(STX);

    uint8_t crc = DEFAULT_CRC, ch;
    while (len-- != 0)
    {
        ch = *buf++;
        write_byte(ch);
        crc ^= ch;
    }
    //write_byte(packet, crc);
    write_byte(crc);

    m_write_handler(ETX);
}
