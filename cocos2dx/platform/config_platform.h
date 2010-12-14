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
    #define CCX_PLATFORM_UPHONE
#elif defined (SHP)
	#define CCX_PLATFORM_BADA
#elif   defined (WIN32) && defined (_WINDOWS)   // under win32pc
    #define CCX_PLATFORM_WIN32
#elif   defined (ANDROID)
    #define CCX_PLATFORM_ANDROID
#elif defined (TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    #define CCX_PLATFORM_IPHONE
#endif

// user configure

// use these macros to set compiling environment if needed

// #define CCX_UNDER_UPHONE
// #define CCX_UNDER_WIN32
// #define CCX_UNDER_ANDROID
// #define CCX_UNDER_IPHONE

// post configure

// check user set platform
#if defined(CCX_UNDER_UPHONE) || defined(CCX_UNDER_WIN32) || defined(CCX_UNDER_ANDROID) || defined(CCX_UNDER_IPHONE)
    #undef CCX_PLATFORM_UPHONE
    #undef CCX_PLATFORM_WIN32
    #undef CCX_PLATFORM_ANDROID
    #undef CCX_PLATFORM_IPHONE

    #if defined(CCX_UNDER_UPHONE)
        #define CCX_PLATFORM_UPHONE	// under uphone
    #elif defined(CCX_UNDER_WIN32)
        #define CCX_PLATFORM_WIN32
    #elif defined(CCX_UNDER_ANDROID)
        #define CCX_PLATFORM_ANDROID
    #elif defined(CCX_UNDER_IPHONE)
        #define CCX_PLATFORM_IPHONE
    #endif

#endif

// check compiling platform
#if ! defined(CCX_PLATFORM_UPHONE) && ! defined(CCX_PLATFORM_WIN32) && ! defined(CCX_PLATFORM_ANDROID) && ! defined(CCX_PLATFORM_IPHONE) && ! defined(CCX_PLATFORM_BADA)
    #error "no platform macro defined!"
#endif
