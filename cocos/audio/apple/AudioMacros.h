/****************************************************************************
 Copyright (c) 2016-2017 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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

#define BREAK_IF(condition) \
    if (!!(condition)) { \
        break; \
    }

#define BREAK_IF_ERR_LOG(condition, fmt, ...) \
    if (!!(condition)) { \
        ALOGE("(" QUOTEME(condition) ") failed, message: " fmt, ##__VA_ARGS__); \
        break; \
    }
