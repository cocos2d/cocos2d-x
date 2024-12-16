#ifndef __CC_STD_C_H__
#define __CC_STD_C_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/CCPlatformMacros.h"
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <cassert>
#include <memory.h>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#endif  // __CC_STD_C_H__
