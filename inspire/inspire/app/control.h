#ifndef _INSPIRE_CONTROL_INTERFACE_H_
#define _INSPIRE_CONTROL_INTERFACE_H_

namespace inspire {

   enum modType
   {
      MOD_APP    = (1 << 16) | 1 << 0,
      MOD_LOG    = (1 << 17) | 1 << 0,
      MOD_NET    = (1 << 18) | 1 << 0,
      MOD_CTRL   = (1 << 19) | 1 << 0,
   };

//    inline bool isApp(IControl* ctrl)
//    {
//       return ctrl->id() & (1 << 16) ;
//    }

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