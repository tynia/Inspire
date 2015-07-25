#ifndef _INSPIRE_NET_BASE_STREAM_H_
#define _INSPIRE_NET_BASE_STREAM_H_

#include "refStream.h"

namespace inspire {

   struct binData
   {
      binData() : owned(false), _data(NULL), _len(0)
      {}
      binData(const char *data, const unsigned len) : owned(false),
                                                      _data(const_cast<char*>(data)),
                                                      _len(len)
      {}

      ~binData()
      {
         if (owned)
         {
            delete [] _data;
            owned = false;
         }
         _data = NULL;
         _len = 0;
      }

      void reverse(const unsigned size)
      {
         if (_len > size)
         {
            return;
         }
         else
         {
            if (owned)
            {
               delete [] _data;
               _data = NULL;
            }
            else
            {
               _data = NULL;
            }

            owned = true;
            _data = new char[ size + 1 ];
            _data[size] = '\0';
         }
      }

      bool     owned;
      unsigned _len;
      char    *_data;
   };

   class baseStream : virtual public refStream
   {
   public:
      baseStream();
      baseStream(const char* data, const size_t len);
      baseStream(const baseStream* bs);
      baseStream(const baseStream& bs);
      virtual ~baseStream();

      baseStream& operator= (const baseStream& rhs);
      const size_t size() const;
      bool empty() const;
      bool readable() const;
      bool writeable() const;

   protected:
      void _skipRead(const size_t size);
      const size_t _seekToRead(const size_t size);
      void _read(char* data, const size_t size, bool align = false, const int bytes = 4);

      void _skipWrite(const size_t size);
      const size_t _seekToWrite(const size_t size);
      void _write(const char* data, const size_t size, bool align = false, const int bytes = 4);

   private:
      bool   _writeable;
      size_t _wOffset;
      size_t _rOffset;
   };

}
#endif