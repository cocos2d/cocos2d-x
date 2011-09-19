#ifndef __CC_PLATFORMFUNC_BADA_H__
#define __CC_PLATFORMFUNC_BADA_H__

#ifdef __cplusplus
extern "C" {
#endif

#define printf(...) AppLog(__VA_ARGS__)

int sprintf(char* buf, const char *format, ...);
int sscanf (const char *s,const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* __CC_PLATFORMFUNC_BADA_H__ */
