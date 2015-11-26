#ifndef _INSPIRE_NONE_COPYABLE_H_
#define _INSPIRE_NONE_COPYABLE_H_

class noncopyable
{
protected:
   noncopyable() {};
   virtual ~noncopyable() {};
private:
   noncopyable(const noncopyable&);
   const noncopyable& operator=(const noncopyable&);
};

#endif