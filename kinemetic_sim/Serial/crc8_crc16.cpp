#include "crc8_crc16.h"

CRC8_CRC16::CRC8_CRC16(uint8_t CRC8_base, uint16_t CRC16_base)
{
    this->CRC8_base = CRC8_base;
    this->CRC16_base = CRC16_base;
}

uint8_t CRC8_CRC16::CRC8_Calc(uint8_t *data, uint32_t len)
{
    uint8_t CRC8 = this->CRC8_base;
    uint32_t index;
    while(len--)
    {
        index = CRC8 ^ (*data++);
        CRC8 = CRC8_table[index];
    }
    return CRC8;
}

uint16_t CRC8_CRC16::CRC16_Calc(uint8_t *data, uint32_t len)
{
    uint16_t CRC16 = this->CRC16_base;
    uint8_t index;
    while(len--)
    {
        index = (uint8_t)((CRC16 ^ (uint16_t)(*data++)) & 0xff);
        CRC16 = (CRC16 >> 8) ^ CRC16_table[index];
    }
    return CRC16;
}

bool CRC8_CRC16::CRC8_Verify(uint8_t *data, uint32_t len)
{
    if(sizeof(data) < len || len <= 2)
    {
        return false;
    }
    uint8_t data_CRC8;
    memcpy(&data_CRC8, &data[len-1], 1);
    return (this->CRC8_Calc(data, len-1) == data_CRC8);
}

bool CRC8_CRC16::CRC16_Verify(uint8_t *data, uint32_t len)
{
    uint16_t data_CRC16;
    memcpy(&data_CRC16, (uint8_t *)data+len-2, 2);
    return (this->CRC16_Calc(data, len-2) == data_CRC16);
}

uint8_t* CRC8_CRC16::CRC8_Append(uint8_t *data, uint32_t len)
{
    if(data == NULL || len <= 2)
    {
        return data;
    }
    uint8_t CRC8 = this->CRC8_Calc(data, len-1);
    memcpy(&data[len-1], &CRC8, 1);
    return data;
}

uint8_t* CRC8_CRC16::CRC16_Append(uint8_t *data, uint32_t len)
{
    if(data == NULL || len <= 2)
    {
        return data;
    }
    uint16_t CRC16 = this->CRC16_Calc(data, len-2);
    memcpy(&data[len-2], &CRC16, 2);
    return data;
}
