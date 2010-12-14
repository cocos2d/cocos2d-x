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

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "config_platform.h"

#if defined(CCX_PLATFORM_UPHONE)
	#include "uphone/CCTime.h"
	#include "uphone/NSLock.h"
	#include "uphone/Cocos2dTypes.h"
	// #include "uphone/CCXGLExtFunc.h"
	#include "uphone/CCXBitmapDC.h"
    #include "uphone/ZipUtils.h"
#elif defined(CCX_PLATFORM_WIN32)
    #include "win32/CCTime.h"
    #include "win32/NSLock.h"
    #include "win32/Cocos2dTypes.h"
    #include "win32/CCXBitmapDC.h"
    #include "win32/ZipUtils.h"
#elif defined(CCX_PLATFORM_ANDROID)
    #include "android/CCTime.h"
    #include "android/NSLock.h"
    #include "android/Cocos2dTypes.h"
    #include "android/CCXBitmapDC.h"
    #include "android/ZipUtils.h"
#elif defined(CCX_PLATFORM_IPHONE)
    #include "iphone/CCTime.h"
    #include "iphone/NSLock.h"
    #include "iphone/Cocos2dTypes.h"
    #include "iphone/CCXBitmapDC.h"
    #include "iphone/ZipUtils.h"
#elif defined(CCX_PLATFORM_BADA)
    #include "bada/CCTime.h"
    #include "bada/NSLock.h"
    #include "bada/Cocos2dTypes.h"
    #include "bada/CCXBitmapDC.h"
    #include "bada/ZipUtils.h"
#else 
    #error
#endif

#endif // __PLATFORM_H__
