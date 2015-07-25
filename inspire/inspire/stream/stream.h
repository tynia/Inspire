#ifndef _INSPIRE_NET_STREAM_H_
#define _INSPIRE_NET_STREAM_H_

namespace inspire {

#ifdef _INSPIRE_SERVER_
   /**
   * check endian of local
   */
   inline bool isBigEndian()
   {
      union
      {
         short __sNum;
         char __ca[2];
      } endian;
      endian.__sNum = 0x0109;

      if (endian.__ca[0] == 0x09)
      {
         return false;
      }
      return true;
   }
#else
   static bool g_endian = false;

   inline void setEndian(bool endian)
   {
      g_endian = endian;
   }
#endif
}
#endif