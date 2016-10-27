#include "istream.h"
#include "ostream.h"
#include <string.h>

int main(int argc, char** argv)
{
    COStream os;
    binData b;
    char* p = new char[10];
    memcpy(p, "vs code#", 9);
    b.pData = p;
    b.len = strlen(b.pData);
    os << "stream test: " << 1 << 'c' << true << short(10) << 3.1415926f << double(2.34566) << b;
    CIStream is(os.data(), os.length());
    std::string str;
    int i;
    char c;
    bool flag;
    short s;
    double d;
    float f;
    binData bin;

    is >> str >> i >> c >> flag >> s >> f >> d >> bin;

    std::cout << str << std::endl;
    std::cout << i << std::endl;
    std::cout << c << std::endl;
    std::cout << flag << std::endl;
    std::cout << s << std::endl;
    std::cout << f << std::endl;
    std::cout << d << std::endl;
    std::cout << toString(bin) << "   " << bin.len << std::endl;
    //std::cout << is.c_str() << std::endl;

    return 0;
}