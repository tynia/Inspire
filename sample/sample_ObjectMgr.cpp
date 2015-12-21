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

class BObject : public inspire::iObject
{
public:
   BObject() { std::cout << "B Object constructor" << std::endl; }
   ~BObject() { std::cout << "B Object destructor" << std::endl; }

   void say() { _num = 100; std::cout << "B Object says" << _num << std::endl; }

private:
   int _num;
};

int main(int argc, char* argv)
{
   AObject* obj = INSPIRE_NEW AObject();
   INSPIRE_ASSERT(NULL != obj, "obj cannot be NULL");
   obj->say();
   INSPIRE_DEL obj;

   BObject a;
   BObject *pB = INSPIRE_NEW BObject();
   a.say();
   pB->say();
   return 0;
}