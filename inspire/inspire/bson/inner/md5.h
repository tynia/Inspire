#ifndef _INSPIRE_BSON_MD5_H_
#define _INSPIRE_BSON_MD5_H_

namespace inspire {

   namespace bson {

      inline void genMD5(const char* out, const char* in, const unsigned int len)
      {
         INSPIRE_ASSERT(NULL != out, "buffer to store md5 value cannot be NULL");
         INSPIRE_ASSERT(NULL != in, "buffer to crypted cannot be NULL");

      }
   }
}
#endif
