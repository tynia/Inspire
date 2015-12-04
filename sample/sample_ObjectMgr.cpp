#include <iostream>
#include "util/assert.h"
#include "util/memory/iObject.h"

class AObject : public inspire::iObject
{
public:
   AObject() { std::cout << "A Object constructor" << std::endl; }
   ~AObject() { std::cout << "A Object destructor" << std::endl; }

   void say() { std::cout << "A Object says" << std::endl; }
};

int main(int argc, char* argv)
{
   AObject* obj = INSPIRE_NEW AObject;
   INSPIRE_ASSERT(NULL != obj, "obj cannot be NULL");
   obj->say();
   INSPIRE_DEL obj;
   return 0;
}