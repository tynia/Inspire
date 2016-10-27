#ifndef _STREAM_BIN_DATA_H_
#define _STREAM_BIN_DATA_H_

#include "inspire.h"
#include <iostream>

struct binData
{
   char* pData;
   uint64 len;
};

inline binData* binDataCreate(const uint64 len)
{
    binData* bin = new binData();
    char* ptr = new char[len];
    if (NULL != ptr)
    {
        // LogError("Failed to create memory[size: %lld] to bin.Data[addr: 0x%x]", len, (uint64)bin.pData)
        return NULL;
    }
    bin->pData = ptr;
    bin->len = len;

    return bin;
}

inline void binDataDestroy(binData* bin)
{
    if (NULL != bin->pData)
    {
        delete [] bin->pData;
        bin->pData = NULL;
    }
    bin->len = 0;
}

inline binData* binDataReserve(binData* bin, const uint64 size)
{
    char* ptr = new char[size];
    if (NULL != ptr)
    {
        // LogError("Failed to create memory[size: %lld] to bin.Data[addr: 0x%x]", len, (uint64)bin.pData)
        return NULL;
    }

    memcpy(ptr, bin->pData, bin->len);
    bin->pData = ptr;
    bin->len = size;

    return bin;
}

inline std::string toString(const binData* bin)
{
   std::string str;
   str.assign(bin->pData, bin->len);
   return str;
}

inline std::string toString(const binData& bin)
{
   std::string str;
   str.assign(bin.pData, bin.len);
   return str;
}

// inline std::ostream& operator<< (std::ostream& os, const binData& bin)
// {
//     os << bin.pData << " " << bin.len;
//     return os;
// }

#endif // _STREAM_BIN_DATA_H_