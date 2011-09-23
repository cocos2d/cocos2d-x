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

#include "CCCommon.h"

NS_CC_BEGIN;

#if CC_SUPPORT_MULTITHREAD
/**
@brief	The object for mutual-exclusion synchronization.

@warning Don't enter a CCLock twice in the same thread.
*/
class CC_DLL CCLock
{
public:
    CCLock();
    ~CCLock();

    void lock();
    void unlock();

private:
    class Impl;
    CCLock::Impl * m_pImp;
};
#else   // CC_SUPPORT_MULTITHREAD

class CC_DLL CCLock
{
public:
    CCLock() {}
    ~CCLock() {}

    void lock() {}
    void unlock() {}
};

#endif  // CC_SUPPORT_MULTITHREAD

NS_CC_END;

#endif	// __CC_PLATFORM_THREAD_H__
