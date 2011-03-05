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

// pre configure
#ifdef _TRANZDA_VM_                             // under uphone
    #define CC_PLATFORM_UPHONE
#elif   defined (WIN32) && defined (_WINDOWS)   // under win32pc
    #define CC_PLATFORM_WIN32
#elif   defined (ANDROID)
    #define CC_PLATFORM_ANDROID
#elif defined (TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    #define CC_PLATFORM_IPHONE
#elif defined (TARGET_OS_MAC)
    #define CC_PLATFORM_MAC
#endif

// user configure

// use these macros to set compiling environment if needed

// #define CC_UNDER_UPHONE
// #define CC_UNDER_WIN32
// #define CC_UNDER_ANDROID
// #define CC_UNDER_IPHONE

// post configure

// check user set platform
#if defined(CC_UNDER_UPHONE) || defined(CC_UNDER_WIN32) || defined(CC_UNDER_ANDROID) || defined(CC_UNDER_IPHONE)
    #undef CC_PLATFORM_UPHONE
    #undef CC_PLATFORM_WIN32
    #undef CC_PLATFORM_ANDROID
    #undef CC_PLATFORM_IPHONE

    #if defined(CC_UNDER_UPHONE)
        #define CC_PLATFORM_UPHONE	// under uphone
    #elif defined(CC_UNDER_WIN32)
        #define CC_PLATFORM_WIN32
    #elif defined(CC_UNDER_ANDROID)
        #define CC_PLATFORM_ANDROID
    #elif defined(CC_UNDER_IPHONE)
        #define CC_PLATFORM_IPHONE
    #endif
#endif

// distinguish mobile platforms and pc platforms
#if defined(CC_PLATFORM_UPHONE) || defined(CC_PLATFORM_WIN32) || defined(CC_PLATFORM_ANDROID) || defined(CC_PLATFORM_IPHONE)
    #define CC_PLATFORM_MOBILE
#elif defined (CC_PLATFORM_MAC)
    #define CC_PLATFORM_PC
#endif

// check compiling platform
#if ! defined(CC_PLATFORM_UPHONE) && ! defined(CC_PLATFORM_WIN32) && ! defined(CC_PLATFORM_ANDROID) && ! defined(CC_PLATFORM_IPHONE)
    #error "no platform macro defined!"
#endif
