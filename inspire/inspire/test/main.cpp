#include <iostream>
#include "application.h"
#include "insLog.h"

using namespace inspire;

class Application : public IApplication
{
public:
   Application() : IApplication(MOD_APP)
   {
   }

   virtual void initialize()
   {
      std::cout << "initialize: " << std::endl;
      std::cout << "===========================" << std::endl;
   }

   virtual void active()
   {
      LogInfo("enter a = %d", 100);
      std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
   }

   virtual void destroy()
   {
      LogInfo("enter a = %d", -1);
      std::cout << "########################" << std::endl;
   }

   virtual void run()
   {
      initialize();
      active();
      destroy();
   }
};

int main()
{
   Application app;
   app.run();

   return 0;
}