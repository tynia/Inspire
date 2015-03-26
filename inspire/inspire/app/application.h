#ifndef _INSPIRE_APPLICATION_H_
#define _INSPIRE_APPLICATION_H_

namespace inspire {

   enum modType
   {
      MOD_APP,
      MOD_LOG,
      MOD_NET,
      MOD_CTRL,
   };

   class IApplication
   {
   public:
      IApplication(modType id) : _id(id)
      {}
      virtual ~IApplication() {}

      const modType id() const
      {
         return _id;
      }

      virtual void initialize() = 0;

      virtual void run() = 0;

      virtual void destroy() = 0;

   private:
      modType _id;
   };

   typedef IApplication IControl;
}
#endif