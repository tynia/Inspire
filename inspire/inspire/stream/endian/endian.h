#ifndef _INSPIRE_NET_ENDIAN_H_
#define _INSPIRE_NET_ENDIAN_H_

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
#endif
   extern void setEndian(bool endian);
}

#define CONVERT_ENDIAN_2(value, to, condition)  \
do                                              \
{                                               \
   if (condition)                               \
   {                                            \
      const char *in = (const char*)&value;     \
      char *out = (char*)&to;                   \
      out[0] = in[1];                           \
      out[1] = in[0];                           \
   }                                            \
   else                                         \
   {                                            \
      to = value;                               \
   }                                            \
} while (false);

#define CONVERT_ENDIAN_4(value, to, condition)  \
do                                              \
{                                               \
   if (condition)                               \
   {                                            \
      const char *in = (const char*)&value;     \
      char *out = (char*)&to;                   \
      out[0] = in[3];                           \
      out[1] = in[2];                           \
      out[2] = in[1];                           \
      out[3] = in[0];                           \
   }                                            \
   else                                         \
   {                                            \
      to = value;                               \
   }                                            \
} while (false);

#define CONVERT_ENDIAN_8(value, to, condition)  \
do                                              \
{                                               \
   if (condition)                               \
   {                                            \
      const char *in = (const char*)&value;     \
      char *out = (char*)&to;                   \
      out[0] = in[7];                           \
      out[1] = in[6];                           \
      out[2] = in[5];                           \
      out[3] = in[4];                           \
      out[4] = in[3];                           \
      out[5] = in[2];                           \
      out[6] = in[1];                           \
      out[7] = in[0];                           \
   }                                            \
   else                                         \
   {                                            \
      to = value;                               \
   }                                            \
} while (false);

#define CONVERT_ENDIAN(value, to, condition)    \
do                                              \
{                                               \
   if (2 == sizeof(value))                      \
   {                                            \
      CONVERT_ENDIAN_2(value, to, condition);   \
   }                                            \
   else if (4 == sizeof(value))                 \
   {                                            \
      CONVERT_ENDIAN_4(value, to, condition);   \
   }                                            \
   else if (8 == sizeof(value))                 \
   {                                            \
      CONVERT_ENDIAN_8(value, to, condition);   \
   }                                            \
} while (false);

// Endian used for server
// client convert the data to match server
// so server do not need to convert any data
#include "stream.h"

namespace inspire {

   extern bool g_endian;
   class Endian
   {
      // do not handle endian, use local
   public:
      // bool
      static const bool N2H(const bool& v)
      {
         return v;
      }
      static const bool H2N(const bool& v)
      {
         return v;
      }
      // char
      static const char N2H(const char& v)
      {
         return v;
      }
      static const char H2N(const char& v)
      {
         return v;
      }
      // short
      static const short N2H(const short& v)
      {
         return v;
      }
      static const short H2N(const short& v)
      {
         return v;
      }
      // unsigned short
      static const unsigned short N2H(const unsigned short& v)
      {
         return v;
      }
      static const unsigned short H2N(const unsigned short& v)
      {
         return v;
      }
      // int
      static const int N2H(const int& v)
      {
         return v;
      }
      static const int H2N(const int& v)
      {
         return v;
      }
      // unsigned int
      static const unsigned int N2H(const unsigned int& v)
      {
         return v;
      }
      static const unsigned int H2N(const unsigned int& v)
      {
         return v;
      }
      // long
      static const long N2H(const long& v)
      {
         return v;
      }
      static const long H2N(const long& v)
      {
         return v;
      }
      // unsigned long
      static const unsigned long N2H(const unsigned long& v)
      {
         return v;
      }
      static const unsigned long H2N(const unsigned long& v)
      {
         return v;
      }
      // int64
      static const int64 N2H(const int64& v)
      {
         return v;
      }
      static const int64 H2N(const int64& v)
      {
         return v;
      }
      // float
      static const float N2H(const float& v)
      {
         return v;
      }
      static const float H2N(const float& v)
      {
         return v;
      }
      // double
      static const double N2H(const double& v)
      {
         return v;
      }
      static const double H2N(const double& v)
      {
         return v;
      }
   };

   // FixedEndian will to be used in client
   // it hopes to compatible with server endpoint
   class FixedEndian
   {
   public:
      // bool
      static const bool N2H(const bool& v)
      {
         return v;
      }
      static const bool H2N(const bool& v)
      {
         return v;
      }
      // char
      static const char N2H(const char& v)
      {
         return v;
      }
      static const char H2N(const char& v)
      {
         return v;
      }
      // short
      static const short N2H(const short& v)
      {
         short out = 0;
         CONVERT_ENDIAN_2(v, out, g_endian);
         return out;
      }
      static const short H2N(const short& v)
      {
         short out = 0;
         CONVERT_ENDIAN_2(v, out, g_endian);
         return out;
      }
      // unsigned short
      static const unsigned short N2H(const unsigned short& v)
      {
         unsigned short out = 0;
         CONVERT_ENDIAN_2(v, out, g_endian);
         return out;
      }
      static const unsigned short H2N(const unsigned short& v)
      {
         unsigned short out = 0;
         CONVERT_ENDIAN_2(v, out, g_endian);
         return out;
      }
      // int
      static const int N2H(const int& v)
      {
         int out = 0;
         CONVERT_ENDIAN_4(v, out, g_endian);
         return out;
      }
      static const int H2N(const int& v)
      {
         int out = 0;
         CONVERT_ENDIAN_4(v, out, g_endian);
         return out;
      }
      // unsigned int
      static const unsigned int N2H(const unsigned int& v)
      {
         unsigned int out = 0;
         CONVERT_ENDIAN_4(v, out, g_endian);
         return out;
      }
      static const unsigned int H2N(const unsigned int& v)
      {
         unsigned int out = 0;
         CONVERT_ENDIAN_4(v, out, g_endian);
         return out;
      }
      // long
      static const long N2H(const long& v)
      {
         long out = 0;
         CONVERT_ENDIAN(v, out, g_endian);
         return out;
      }
      static const long H2N(const long& v)
      {
         long out = 0;
         CONVERT_ENDIAN(v, out, g_endian);
         return out;
      }
      // unsigned long
      static const unsigned long N2H(const unsigned long& v)
      {
         unsigned long out = 0;
         CONVERT_ENDIAN(v, out, g_endian);
         return out;
      }
      static const unsigned long H2N(const unsigned long& v)
      {
         unsigned long out = 0;
         CONVERT_ENDIAN(v, out, g_endian);
         return out;
      }
      // int64
      static const int64 N2H(const int64& v)
      {
         int64 out = 0;
         CONVERT_ENDIAN_8(v, out, g_endian);
         return out;
      }
      static const int64 H2N(const int64& v)
      {
         int64 out = 0;
         CONVERT_ENDIAN_8(v, out, g_endian);
         return out;
      }
      // float
      static const float N2H(const float& v)
      {
         float out = 0.0f;
         CONVERT_ENDIAN(v, out, g_endian);
         return out;
      }
      static const float H2N(const float& v)
      {
         float out = 0.0f;
         CONVERT_ENDIAN(v, out, g_endian);
         return out;
      }
      // double
      static const double N2H(const double& v)
      {
         double out = 0.0f;
         CONVERT_ENDIAN_8(v, out, g_endian);
         return out;
      }
      static const double H2N(const double& v)
      {
         double out = 0.0f;
         CONVERT_ENDIAN_8(v, out, g_endian);
         return out;
      }
   };

}
#endif