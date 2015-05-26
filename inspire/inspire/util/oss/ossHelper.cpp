#include "ossHelper.h"
#include "inspire.h"
#include "util.h"
#include "insLog.h"

namespace inspire {

   bool ossAccess( const char* path, int flags = 0 )
   {
      int rc = 0;
#ifdef _WIN32
      rc = _access( path, flags );
#else
      rc = access( path, flags );
#endif
      if (rc)
      {
         int err = ossGetLastError();
         switch (err)
         {
#ifdef _WIN32
         case ERROR_FILE_NOT_FOUND:
         case ERROR_PATH_NOT_FOUND:
#else
         case ENOENT:
#endif
            LogError("Path not exist");
            break;
#ifdef _WIN32
         case ERROR_ACCESS_DENIED:
#else
         case EACCES:
#endif
            LogError("Access permission denied");
            break;
         default:
            break;
         }
      }
   }

   const int seekAndRead( ossFile& file, const int64 offset, const int toRead, const char* buffer, const int bufferLen )
   {
      if (!file.isOpened())
      {
         LogError("File is not opened, file:%s", file.filename());
         return;
      }

      file.seek(offset, INSPIRE_SEEK_SET);
      return file.read(buffer, bufferLen, toRead);
   }

   const int seekAndWrite( ossFile& file, const int64 offset, const int toWrite, const char* buffer, const int bufferLen )
   {
      if (!file.isOpened())
      {
         LogError("File is not opened, file:%s", file.filename());
         return;
      }

      file.seek(offset, INSPIRE_SEEK_SET);
      return file.write(buffer, bufferLen, toWrite);
   }


}