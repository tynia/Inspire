#ifndef _INSPIRE_CONTROL_INTERFACE_H_
#define _INSPIRE_CONTROL_INTERFACE_H_

namespace inspire {

   enum modType
   {
      MOD_APP,
      MOD_LOG,
      MOD_NET,
      MOD_CTRL,
   };

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