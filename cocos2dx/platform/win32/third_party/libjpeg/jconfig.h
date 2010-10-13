#ifndef __JCONFIG_H__
#define __JCONFIG_H__

#if defined(WIN32) || defined(_WIN32)
#include "jconfig_win.h"
#else
#include "jconfig_linux.h"
#endif	// WIN32

#endif /* __JCONFIG_H__ */