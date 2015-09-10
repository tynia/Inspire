#ifndef _INSPIRE_NET_STREAM_H_
#define _INSPIRE_NET_STREAM_H_

#include "inspire.h"
#include "noncopyable.h"
#include "binData.h"

namespace inspire {

   static const uint64 BLOCK_SIZE = 4 * 1024;

   class IStream : public noncopyable
   {
      IStream();
      IStream(char* buffer, uint64 len);
      virtual ~IStream();

      const char* data() const
      {
         return _data;
      }

      const uint64 size() const
      {
         return _size;
      }

      IStream& operator>> (const bool& val);
      IStream& operator>> (const char& val);
      IStream& operator>> (const unsigned char& val);
      IStream& operator>> (const float& val);
      IStream& operator>> (const double& val);
      IStream& operator>> (const int& val);
      IStream& operator>> (const unsigned int& val);
      IStream& operator>> (const int64& val);
      IStream& operator>> (const uint64& val);
      IStream& operator>> (const std::string& str);
      IStream& operator>> (const binData& ctx);

   private:
      const char* _data;
      const char* _rOffset;
      uint64      _size;
      uint64      _capacity;
   };

   class OStream : public noncopyable
   {
   public:
      OStream();
      OStream(char* buffer, uint64 len);
      virtual ~OStream();

      const char* data() const
      {
         return _data;
      }

      const uint64 size() const
      {
         return _size;
      }

      OStream& operator<< (const bool& val);
      OStream& operator<< (const char& val);
      OStream& operator<< (const unsigned char& val);
      OStream& operator<< (const float& val);
      OStream& operator<< (const double& val);
      OStream& operator<< (const int& val);
      OStream& operator<< (const unsigned int& val);
      OStream& operator<< (const int64& val);
      OStream& operator<< (const uint64& val);
      OStream& operator<< (const std::string& str);
      OStream& operator<< (const binData& ctx);

   protected:
      const uint64 capacity() const
      {
         return _capacity;
      }

   private:
      const char* _data;
      const char* _wOffset;
      uint64      _size;
      uint64      _capacity;
   };
}
#endif