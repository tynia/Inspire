#include <iostream>
#include "logger/logger.h"

int main(int argc, char** argv)
{
   LogEvent("0: logger test begin");
   LogError("1: log a %s level record if a expected error occurs", "Error");
   LogDebug("the log debug will not logged in file, please check");
   LogEmerg("%d: we use LogDebug during we debugging", 2);
   LogEvent("at %s, we exit the test program by return %d", "last", 0);

   return 0;
}