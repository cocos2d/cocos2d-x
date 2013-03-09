#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#include <string.h>

#if defined(_USRDLL)
#define CC_DLL __attribute__ ((visibility ("default")))
#else         /* use a DLL library */
#define CC_DLL __attribute__ ((visibility ("default")))
#endif

#include <assert.h>
#define CC_ASSERT(cond)    assert(cond)
#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif



#endif /* __CCPLATFORMDEFINE_H__*/
