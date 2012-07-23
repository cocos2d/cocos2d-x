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

#ifndef __CCX_COMMON_WOPHONE__
#define __CCX_COMMON_WOPHONE__

#if defined(_WIN32)
    #if defined(SS_MAKEDLL)
    #define CCX_DLL     __declspec(dllexport)
    #elif defined(SS_IGNORE_EXPORT)
    #define CCX_DLL
    #else 		/* use a DLL library */
    #define CCX_DLL     __declspec(dllimport)
    #endif
#else
    #if defined(SS_SHARED)
    #define CCX_DLL     __attribute__((visibility("default")))
    #elif defined(SS_IGNORE_EXPORT)
    #define CCX_DLL
    #else
    #define CCX_DLL
    #endif
#endif 

#endif	// end of __CCX_COMMON_WOPHONE__
