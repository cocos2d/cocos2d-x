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

#ifndef __CC_APPLICATION_PLATFORM_H__
#define __CC_APPLICATION_PLATFORM_H__

#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    #include "win32/CCApplication_win32.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "android/CCApplication_android.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    # include "ios/CCApplication_ios.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
    #include "wophone/CCApplication_wophone.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
	#include "marmalade/CCApplication_marmalade.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	#include "Linux/CCAplication_linux.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
	#include "bada/CCApplication_bada.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_QNX)
    #include "qnx/CCApplication_qnx.h"
#else
    #error
#endif

#endif	// __CC_APPLICATION_PLATFORM_H__
