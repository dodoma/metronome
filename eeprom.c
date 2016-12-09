#include "config.h"
#include "mcu.h"

#define CMD_READ   1
#define CMD_WRITE  2
#define CMD_ERASE  3

__sfr __at 0xE2 ISP_DATA;
__sfr __at 0xE3 ISP_ADDRH;
__sfr __at 0xE4 ISP_ADDRL;
__sfr __at 0xE5 ISP_CMD;
__sfr __at 0xE6 ISP_TRIG;
__sfr __at 0xE7 ISP_CONTR;

static uint8_t m_ea = 0;

void _enable()
{
    m_ea = EA;
    EA = 0;

    ISP_CONTR = 0x82;
}

void _disable()
{
    ISP_CONTR = 0;
    ISP_TRIG = 0;
    ISP_CMD = 0;
    ISP_ADDRH = 0xFF;
    ISP_ADDRL = 0xFF;

    EA = m_ea;
}

void _do(uint16_t addr)
{
    ISP_ADDRH = (uint8_t)(addr >> 8);
    ISP_ADDRL = (uint8_t)(addr & 0x00FF);

    ISP_TRIG = 0x46;
    ISP_TRIG = 0xB9;

    NOP;
}

void eepr_erase(uint16_t addr)
{
    ISP_CMD = CMD_ERASE;

    _enable();
    _do(addr);
    _disable();
}

void eepr_write(uint16_t addr, uint8_t *buf, uint16_t num)
{
    int i;

    _enable();

    ISP_CMD = CMD_WRITE;

    for (i = 0; i < num; i++) {
        ISP_DATA = *buf;

        _do(addr);

        addr++;
        buf++;
    }

    _disable();
}

void eepr_read(uint16_t addr, uint8_t *buf, uint16_t num)
{
    int i;

    _enable();

    ISP_CMD = CMD_READ;

    for (i = 0; i < num; i++) {
        _do(addr);

        *buf = ISP_DATA;

        addr++;
        buf++;
    }

    _disable();
}
