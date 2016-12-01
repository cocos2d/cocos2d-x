#pragma once

#define QUEUEBUFFER_NUM (3)
#define QUEUEBUFFER_TIME_STEP (0.1f)

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
#define ALOGV(fmt, ...) printf("V/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#else
#define ALOGV(fmt, ...) do {} while(false)
#endif
#define ALOGD(fmt, ...) printf("D/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#define ALOGI(fmt, ...) printf("I/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#define ALOGW(fmt, ...) printf("W/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)
#define ALOGE(fmt, ...) printf("E/" LOG_TAG " (" QUOTEME(__LINE__) "): " fmt "\n", ##__VA_ARGS__)

#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
#define CHECK_AL_ERROR_DEBUG() \
do { \
    GLenum __error = alGetError(); \
    if (__error) { \
        ALOGE("OpenAL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
    } \
} while (false)
#else
#define CHECK_AL_ERROR_DEBUG()
#endif

#define RETURN_IF(condition, message) \
do {\
    if (!!(condition)) { \
        ALOGE("(%s) failed, message: %s", QUOTEME(condition), message); \
        return; \
    } \
} while(false)

#define RETURN_VAL_IF(condition, val, fmt, ...) \
do {\
    if (!!(condition)) { \
        ALOGE("(" QUOTEME(condition) ") failed, message: " fmt, ##__VA_ARGS__); \
        return val; \
    } \
} while(false)

#define BREAK_IF(condition) \
do {\
    if (!!(condition)) { \
    break; \
    } \
} while(false)

#define BREAK_IF_ERR_LOG(condition, fmt, ...) \
do {\
    if (!!(condition)) { \
        ALOGE("(" QUOTEME(condition) ") failed, message: " fmt, ##__VA_ARGS__); \
        break; \
    } \
} while(false)
