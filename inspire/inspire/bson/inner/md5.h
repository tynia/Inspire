#ifndef _INSPIRE_BSON_MD5_H_
#define _INSPIRE_BSON_MD5_H_

#include "inspire.h"

namespace inspire {

   namespace bson {

      typedef unsigned char md5_byte_t;
      typedef uint          md5_word_t;

      struct md5_state_t
      {
         md5_word_t count[2];
         md5_word_t a;
         md5_word_t b;
         md5_word_t c;
         md5_word_t d;
         md5_byte_t buf[64];
      };

      static
      inline void md5_init();

      inline void genMD5(const char* out, const char* in, const uint len)
      {
         INSPIRE_ASSERT(NULL != out, "buffer to store md5 value cannot be NULL");
         INSPIRE_ASSERT(NULL != in, "buffer to crypted cannot be NULL");

      }
   }
}
#endif
