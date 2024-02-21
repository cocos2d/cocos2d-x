#ifndef __CC_LOG_OHOS_H__
#define __CC_LOG_OHOS_H__
#include <string.h>
#include <stdint.h>
#include <hilog/log.h>
#ifdef HDF_LOG_TAG
#undef HDF_LOG_TAG
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define APP_LOG_DOMAIN 0x0001
#define APP_LOG_TAG "cocos"
#define OHOS_LOGI(...) ((void)OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))
#define OHOS_LOGD(...) ((void)OH_LOG_Print(LOG_APP, LOG_DEBUG, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))
#define OHOS_LOGW(...) ((void)OH_LOG_Print(LOG_APP, LOG_WARN, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))
#define OHOS_LOGE(...) ((void)OH_LOG_Print(LOG_APP, LOG_ERROR, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))

#if 0
#undef LOG_TAG
#undef LOG_DOMAIN
#define APP_LOG_DOMAIN 0x0001
#define APP_LOG_TAG "cocos"

#ifndef DISPLAY_UNUSED
#define DISPLAY_UNUSED(x) (void)x
#endif

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#ifndef DISPLAY_DEBUG_ENABLE
#define DISPLAY_DEBUG_ENABLE 1

#endif

#ifndef OHOS_LOGD
#define OHOS_LOGD(format, ...)                                                                                     \
    do {                                                                                                              \
        if (DISPLAY_DEBUG_ENABLE) {                                                                                   \
            OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN, "[%{public}s@%{public}s:%{public}d] " format "\n",                                  \
                __FUNCTION__, __FILENAME__, __LINE__,                                                                 \
                ##__VA_ARGS__);                                                                                       \
        }                                                                                                             \
    } while (0)
#endif

#ifndef OHOS_LOGI
#define OHOS_LOGI(format, ...)                                                                                     \
    do {                                                                                                              \
        OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN, "[%{public}s@%{public}s:%{public}d] " format "\n", __FUNCTION__, __FILENAME__, __LINE__, \
            ##__VA_ARGS__);                                                                                           \
    } while (0)
#endif

#ifndef OHOS_LOGW
#define OHOS_LOGW(format, ...)                                                                                     \
    do {                                                                                                              \
        OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN, "[%{public}s@%{public}s:%{public}d] " format "\n", __FUNCTION__, __FILENAME__, __LINE__, \
            ##__VA_ARGS__);                                                                                           \
    } while (0)
#endif

#ifndef OHOS_LOGE
#define OHOS_LOGE(format, ...)                                 \
    do {                                                          \
        OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN,           \
            "\033[0;32;31m"                                       \
            "[%{public}s@%{public}s:%{public}d] " format "\033[m" \
            "\n",                                                 \
            __FUNCTION__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#endif

#ifndef CHECK_NULLPOINTER_RETURN_VALUE
#define CHECK_NULLPOINTER_RETURN_VALUE(pointer, ret)          \
    do {                                                      \
        if ((pointer) == NULL) {                              \
            OHOS_LOGE("pointer is null and return ret\n"); \
            return (ret);                                     \
        }                                                     \
    } while (0)
#endif

#ifndef CHECK_NULLPOINTER_RETURN
#define CHECK_NULLPOINTER_RETURN(pointer)                 \
    do {                                                  \
        if ((pointer) == NULL) {                          \
            OHOS_LOGE("pointer is null and return\n"); \
            return;                                       \
        }                                                 \
    } while (0)
#endif

#ifndef DISPLAY_CHK_RETURN
#define DISPLAY_CHK_RETURN(val, ret, ...) \
    do {                                  \
        if (val) {                        \
            __VA_ARGS__;                  \
            return (ret);                 \
        }                                 \
    } while (0)
#endif

#ifndef DISPLAY_CHK_RETURN_NOT_VALUE
#define DISPLAY_CHK_RETURN_NOT_VALUE(val, ...) \
    do {                                            \
        if (val) {                                  \
            __VA_ARGS__;                            \
            return;                                 \
        }                                           \
    } while (0)
#endif

#endif 
#ifdef __cplusplus
}
#endif

#endif /* __CC_LOG_OHOS_H__ */
