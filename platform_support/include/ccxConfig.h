/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __CCX_CONFIG_H_YANGWS_20100110__
#define __CCX_CONFIG_H_YANGWS_20100110__

/**
@file
@brief Config of cocos2d-x project.

There are config below:
    - build for which target platform
*/

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro which ccx uses.
#define CCX_PLATFORM_UNKNOWN            0
#define CCX_PLATFORM_IOS                1
#define CCX_PLATFORM_MAC                2
#define CCX_PLATFORM_ANDROID            3
#define CCX_PLATFORM_UPHONE             4
#define CCX_PLATFORM_WIN32              5

// Determine tartet platform by compile environment macro.
#define CCX_TARGET_PLATFORM             CCX_PLATFORM_UNKNOWN

// iphone
#if ! CCX_TARGET_PLATFORM && (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_IOS
#endif

// mac
#if ! CCX_TARGET_PLATFORM && defined(TARGET_OS_MAC)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_MAC
#endif

// android
#if ! CCX_TARGET_PLATFORM && defined(ANDROID)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_ANDROID
#endif

// uphone
#if ! CCX_TARGET_PLATFORM && defined(_TRANZDA_VM_)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_UPHONE
#endif

// win32
#if ! CCX_TARGET_PLATFORM && (defined(WIN32) && defined(_WINDOWS))
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_WIN32

    // win32 platform support multi-thread
    #define CCX_SUPPORT_MULTITHREAD     1
#endif

//////////////////////////////////////////////////////////////////////////
// user configure
//////////////////////////////////////////////////////////////////////////

// Check user assigned target platform.
#if defined(CCX_UNDER_IOS)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_IOS
#endif

#if defined(CCX_UNDER_MAC)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_MAC
#endif

#if defined(CCX_UNDER_ANDROID)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_ANDROID
#endif

#if defined(CCX_UNDER_UPHONE)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_UPHONE
#endif

#if defined(CCX_UNDER_WIN32)
    #undef  CCX_TARGET_PLATFORM
    #define CCX_TARGET_PLATFORM         CCX_PLATFORM_WIN32
#endif

// Check user assigned supportive of multi-thread
#if defined(CCX_ENABLE_MULTITHREAD)
    #undef  CCX_SUPPORT_MULTITHREAD
    #define CCX_SUPPORT_MULTITHREAD     1
#elif defined(CCX_DISABLE_MULTITHREAD)
    #undef  CCX_SUPPORT_MULTITHREAD
    #define CCX_SUPPORT_MULTITHREAD     0
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! CCX_TARGET_PLATFORM
    #error  "Can not recognize the target platform, compling under a unsupported platform?"
#endif 

// distinguish mobile platforms and pc platforms
#if defined(CCX_PLATFORM_UPHONE) || defined(CCX_PLATFORM_WIN32) || defined(CCX_PLATFORM_ANDROID) || defined(CCX_PLATFORM_IOS)
    #define CCX_PLATFORM_MOBILE
#elif defined (CCX_PLATFORM_MAC)
    #define CCX_PLATFORM_PC
#endif

// cocos2d-x havn't support multi-thread yet
#undef  CCX_SUPPORT_MULTITHREAD
#define CCX_SUPPORT_MULTITHREAD         0

// Check the supportive of platform
#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_WIN32)

#endif  // CCX_PLATFORM_WIN32

#endif  // __CCX_CONFIG_H_YANGWS_20100110__

