#ifndef _STREAM_NET_ENDIAN_H_
#define _STREAM_NET_ENDIAN_H_

enum ENDIAN
{
   ENDIAN_BIG = 0,
   ENDIAN_LITTLE = 1,
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


#endif // _STREAM_NET_ENDIAN_H_