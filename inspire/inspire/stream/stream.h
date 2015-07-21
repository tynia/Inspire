#ifndef _INSPIRE_NET_STREAM_H_
#define _INSPIRE_NET_STREAM_H_

namespace inspire {

#ifndef _INSPIRE_SERVER_
   static bool g_endian = false;

   inline void setEndian(bool endian)
   {
      g_endian = endian;
   }
#endif
}
#endif