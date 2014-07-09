#include <time.h>
#include <windows.h> //I've ommited context line

#ifdef WP8
#include <winsock2.h> //I've ommited context line.
#endif

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

#ifdef __MINGW32__
#else
 #ifdef __MINGW64__
 #else
struct timezone 
{
	int  tz_minuteswest;	/* minutes W of Greenwich */
	int  tz_dsttime;	/* type of dst correction */
};
 #endif
#endif

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag;

	if (NULL != tv) {
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres /= 10;  /*convert into microseconds*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}
 
	if (NULL != tz) {
#if !defined(WP8)
		if (!tzflag) {
			_tzset();
			tzflag++;
		}
#endif
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime = _daylight;
	}

	return 0;
}
