#ifndef _INSPIRE_NET_STREAM_UTIL_H_
#define _INSPIRE_NET_STREAM_UTIL_H_

namespace inspire {

#ifndef _INSPIRE_SERVER_
   extern bool g_endian = false;

   inline void setEndian(bool endian)
   {
      g_endian = endian;
   }
#endif

   namespace util {

      inline const unsigned int roundUp(const unsigned int original,
                                        const unsigned int bytes = 4)
      {
         return ((original+(bytes-1)) - ((original+(bytes-1))%bytes));
      }

      inline const unsigned int roundDown(const unsigned int original,
                                          const unsigned int bytes = 4)
      {
         return (original/bytes) * bytes;
      }
   }
}
#endif