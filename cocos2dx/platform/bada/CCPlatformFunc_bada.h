#ifndef __CC_PLATFORMFUNC_BADA_H__
#define __CC_PLATFORMFUNC_BADA_H__

#include "CCPlatformMacros.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CC_BADA_2_0

#define printf(...) AppLog(__VA_ARGS__)

extern int CC_DLL sprintf(char* buf, const char *format, ...);
extern int CC_DLL sscanf (const char *s,const char *format, ...);

#endif

extern void CC_DLL badaAssert(const char* pFunction, int lineNumber, const char* pszContent);

#ifdef __cplusplus
}
#endif

#endif /* __CC_PLATFORMFUNC_BADA_H__ */
