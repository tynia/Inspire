#include "iostream.h"
#include <cstring>

#include "inspire.h"

namespace inspire {

   const size_t CIStream::seekTo(const size_t size)
   {
      return _seekToRead(size);
   }

   void CIStream::skip(const size_t size)
   {
      _skipRead(size);
   }

   // operator>>
   CIStream& CIStream::operator>> (bool& var)
   {
      _read((char*)&var, sizeof(bool), true);

      return *this;
   }

   CIStream& CIStream::operator>> (char& var)
   {
      _read((char*)&var, sizeof(char), true);

      return *this;
   }

   CIStream& CIStream::operator>> (unsigned char& var)
   {
      _read((char*)&var, sizeof(char), true);

      return *this;
   }

   CIStream& CIStream::operator>> (float& var)
   {
      float tmp = 0;
      _read((char*)&tmp, sizeof(float), true);
      var = ENDIAN::N2H(tmp);

      return *this;
   }

   CIStream& CIStream::operator>> (double& var)
   {
      double tmp = 0;
      _read((char*)&tmp, sizeof(double), true);
      var = ENDIAN::N2H(tmp);

      return *this;
   }

   CIStream& CIStream::operator>> (int& var)
   {
      int tmp = 0;
      _read((char*)&tmp, sizeof(int), true);
      var = ENDIAN::N2H(tmp);

      return *this;
   }

   CIStream& CIStream::operator>> (unsigned int& var)
   {
      unsigned int tmp = 0;
      _read((char*)&tmp, sizeof(unsigned int), true);
      var = ENDIAN::N2H(tmp);

      return *this;
   }

   CIStream& CIStream::operator>> (int64& var)
   {
      int64 tmp = 0;
      _read((char*)&tmp, sizeof(int64), true);
      var = ENDIAN::N2H(tmp);

      return *this;
   }

   CIStream& CIStream::operator>> (binData& ctx)
   {
      int len = 0;
      _read((char*)&len, sizeof(int), true);
      ctx._len = ENDIAN::N2H(len);

      ctx.reverse(ctx._len);
      _read(ctx._data, ctx._len, true);

      return *this;
   }

   //////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////
   const size_t COStream::seekTo(const size_t size)
   {
      return _seekToWrite(size);
   }

   void COStream::skip(const size_t size)
   {
      _skipWrite(size);
   }

   COStream& COStream::operator<< (const bool& val)
   {
      _write((const char*)&val, sizeof(bool), true);

      return *this;
   }

   COStream& COStream::operator<< (const char& val)
   {
      _write((const char*)&val, sizeof(char), true);

      return *this;
   }

   COStream& COStream::operator<< (const unsigned char& val)
   {
      _write((const char*)&val, sizeof(unsigned char), true);
      return *this;
   }

   COStream& COStream::operator<< (const float& val)
   {
      float tmp = ENDIAN::H2N(val);
      _write((const char*)&tmp, sizeof(float), true);

      return *this;
   }

   COStream& COStream::operator<< (const double& val)
   {
      double tmp = ENDIAN::H2N(val);
      _write((const char*)&tmp, sizeof(double), true);

      return *this;
   }

   COStream& COStream::operator<< (const int& val)
   {
      int tmp = ENDIAN::H2N(val);
      _write((const char*)&tmp, sizeof(int), true);

      return *this;
   }

   COStream& COStream::operator<< (const unsigned int& val)
   {
      unsigned int tmp = ENDIAN::H2N(val);
      _write((const char*)&tmp, sizeof(unsigned int), true);

      return *this;
   }

   COStream& COStream::operator<< (const int64& val)
   {
      int64 tmp = ENDIAN::H2N(val);
      _write((const char*)&tmp, sizeof(int64), true);

      return *this;
   }

   COStream& COStream::operator<< (const binData& ctx)
   {
      unsigned int len = ENDIAN::H2N(ctx._len);
      _write((const char *)&len, sizeof(int), true);
      _write(ctx._data, ctx._len, true);

      return *this;
   }

}
