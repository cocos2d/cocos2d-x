#ifndef _GET_TIME_OF_DAY_H
#define _GET_TIME_OF_DAY_H

#ifdef  __MINGW64__
#else
#ifdef  __MINGW32__
#else
#include < time.h >
#endif
#endif

#include <windows.h> //I've ommited context line.
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 
#ifndef WP8
struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};
 
int gettimeofday(struct timeval *tv, struct timezone *tz);
#endif


#endif
