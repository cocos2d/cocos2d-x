#ifndef __CC_PLATFORMFUNC_BADA_H__
#define __CC_PLATFORMFUNC_BADA_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CC_BADA_2_0

int CC_DLL printf(const char* format, ...);
int CC_DLL sprintf(char* buf, const char *format, ...);
int CC_DLL sscanf (const char *s,const char *format, ...);

#endif

void CC_DLL badaAssert(const char* pFunction, int lineNumber, const char* pszContent);

#ifdef __cplusplus
}
#endif

#endif /* __CC_PLATFORMFUNC_BADA_H__ */
