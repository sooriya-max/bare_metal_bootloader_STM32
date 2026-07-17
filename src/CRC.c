#include "CRC.h"

uint32_t crc32_compute(uint8_t uart_bytes[], uint32_t length)
{
    uint32_t CRC = 0xFFFFFFFF, CRC_polynomial = 0xEDB88320;
    for(uint32_t iterator = 0; iterator < length; iterator++)
    {
        CRC ^= uart_bytes[iterator];
        for(uint8_t i = 0; i < 8; i++)
        {
            if(CRC & 1)
                CRC = (CRC >> 1) ^ CRC_polynomial;
            else
                CRC = (CRC >> 1);
        }
    }
    
    return (CRC ^ 0xFFFFFFFF);    
}