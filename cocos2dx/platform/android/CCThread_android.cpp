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

#if CCX_SUPPORT_MULTITHREAD

#include <semaphore.h>
#include "CCThread.h"

NS_CC_BEGIN;

class CCLock::Impl
{
public:
    Impl()
    {
        sem_init(&m_sMutex, 0, 0);
    }

    ~Impl()
    {
        sem_destroy(&m_sMutex);
    }

	sem_t m_sMutex;
};

CCLock::CCLock()
: m_pImp(new CCLock::Impl)
{
}

CCLock::~CCLock()
{
    CC_SAFE_DELETE(m_pImp);
}

void CCLock::lock()
{
    if (m_pImp)
    {
        sem_wait(&m_pImp->m_sMutex);
    }
}

void CCLock::unlock()
{
    if (m_pImp)
    {
		sem_post(&m_pImp->m_sMutex);
    }
}

NS_CC_END;

#endif  // CCX_SUPPORT_MULTITHREAD
