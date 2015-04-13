#ifndef _INSPIRE_CONTROL_INTERFACE_H_
#define _INSPIRE_CONTROL_INTERFACE_H_

namespace inspire {

   enum modType
   {
      MOD_APP,
      MOD_KERNEL,
      MOD_LOG,
      MOD_NET,
      MOD_THREAD,
   };

   inline const char* moduleTypeString(modType t)
   {
      switch (t)
      {
      case MOD_APP:
         return "Application";
      case MOD_KERNEL:
         return "Kernel module";
      case MOD_LOG:
         return "Log module";
      case MOD_NET:
         return "Net module";
      case MOD_THREAD:
         return "Thread module";
      default:
         return "Unknown module";
      }
   }

   class IControl
   {
   public:
      IControl(modType id) : _id(id)
      {}
      virtual ~IControl() {}

      const modType id() const
      {
         return _id;
      }

      virtual void initialize() = 0;

      virtual void active() = 0;

      virtual void destroy() = 0;

   private:
      modType _id;
   };
}
#endif