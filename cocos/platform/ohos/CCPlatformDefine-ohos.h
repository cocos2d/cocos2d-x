#ifndef __CCPLATFORMDEFINE_OHOS_H__
#define __CCPLATFORMDEFINE_OHOS_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include <assert.h>
#include "CCLogOhos.h"

#define CC_DLL

#define CC_NO_MESSAGE_PSEUDOASSERT(cond)                        \
    if (!(cond)) {                                              \
        OHOS_LOGI("[cocos2d-x assert] %s function:%s line:%d",  __FILE__, __FUNCTION__, __LINE__); \
    }

#define CC_MESSAGE_PSEUDOASSERT(cond, msg)                          \
    if (!(cond)) {                                                  \
        OHOS_LOGI("[cocos2d-x assert] file:%s function:%s line:%d, %s", __FILE__, __FUNCTION__, __LINE__, msg); \
    }


#define CC_ASSERT(cond) CC_NO_MESSAGE_PSEUDOASSERT(cond)

#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#endif /* __CCPLATFORMDEFINE_OHOS_H__*/
