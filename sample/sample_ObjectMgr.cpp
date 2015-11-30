#include <iostream>
#include "util/ObjectMgr.h"
#include "util/assert.h"

class AObject
{
public:
   AObject() { std::cout << "A Object constructor" << std::endl; }
   ~AObject() { std::cout << "A Object destructor" << std::endl; }

   void say() { std::cout << "A Object says" << std::endl; }
};

int main(int argc, char* argv)
{
   inspire::ObjectMgr* mgr = inspire::ObjectMgr::instance();
   AObject* obj = INSPIRE_CREATE_OBJECT(AObject);
   INSPIRE_ASSERT(NULL != obj, "obj cannot be NULL");
   obj->say();
   INSPIRE_DESTROY_OBJECT(AObject, obj);
   return 0;
}