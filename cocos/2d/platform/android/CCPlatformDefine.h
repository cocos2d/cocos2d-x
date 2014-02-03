/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#include "CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "android/log.h"

#define CC_DLL

#define CC_NO_MESSAGE_PSEUDOASSERT(cond)                        \
    if (!(cond)) {                                              \
        __android_log_print(ANDROID_LOG_ERROR,                  \
                            "cocos2d-x assert",                 \
                            "%s function:%s line:%d",           \
                            __FILE__, __FUNCTION__, __LINE__);  \
    }

#define CC_MESSAGE_PSEUDOASSERT(cond, msg)                          \
    if (!(cond)) {                                                  \
        __android_log_print(ANDROID_LOG_ERROR,                      \
                            "cocos2d-x assert",                     \
                            "file:%s function:%s line:%d, %s",      \
                            __FILE__, __FUNCTION__, __LINE__, msg); \
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

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif /* __CCPLATFORMDEFINE_H__*/
