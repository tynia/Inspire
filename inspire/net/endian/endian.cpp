#include "endian.h"

namespace inspire {

   static bool g_endian = false;

   void setEndian(bool endian)
   {
      g_endian = endian;
   }
}