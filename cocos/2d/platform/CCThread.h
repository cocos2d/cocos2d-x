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

#ifndef __CC_PLATFORM_THREAD_H__
#define __CC_PLATFORM_THREAD_H__

#include <functional>
#include <list>
#include <mutex>
#include "platform/CCCommon.h"
#include "CCPlatformMacros.h"
#include "CCDirector.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/* On iOS, should create autorelease pool when create a new thread
 * and release it when the thread end.
 */

class CC_DLL ThreadHelper
{
public:
    friend DisplayLinkDirector;

    /** Create an autorelease pool for objective-c codes.
     * @js NA
     * @lua NA
     */
    static void* createAutoreleasePool();
    
    /**
     * @js NA
     * @lua NA
    */
    static void releaseAutoreleasePool(void *autoreleasePool);

    /** To run a function in gl thread.
     * @js NA
     * @lua NA
     @since v3.0
     */
    static void runOnGLThread(std::function<void(void)> f);
    
    /** Set how many callback functions being invoked per frame. Default value is 5.
     * @js NA
     * @lua NA
     @since v3.0
     */
    static void setCallbackNumberPerFrame(int callbackNumberPerFrame);

private:
    // This function will be call by Director to call some call back function on gl thread
    static void doCallback();
    
    static std::list<std::function<void(void)>> *_callbackList;
    static std::mutex *_mutex;
    // How many callback functions invoked per frame
    static int _callbackNumberPerFrame;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_PLATFORM_THREAD_H__
