/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#ifndef __EXPORT_COMMON__
#define __EXPORT_COMMON__

#if defined(SHP)
    #include <FBaseConfig.h>
    #define EXPORT_DLL  _EXPORT_
#elif defined(_WIN32)
    #if defined(CC_STATIC)
        #define EXPORT_DLL
    #else
        #if defined(_EXPORT_DLL_)
            #define EXPORT_DLL      __declspec(dllexport)    
        #else         /* use a DLL library */
            #define EXPORT_DLL     __declspec(dllimport)
        #endif
    #endif
#else
    #if defined(_SHARED_)
    #define EXPORT_DLL     __attribute__((visibility("default")))
    #elif defined(IGNORE_EXPORT)
    #define EXPORT_DLL
    #else
    #define EXPORT_DLL
    #endif
#endif 

#endif    // end of __EXPORT_COMMON__
