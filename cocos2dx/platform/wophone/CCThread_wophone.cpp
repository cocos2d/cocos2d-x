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

#include "TG3.h"
#include "CCThread.h"

NS_CC_BEGIN;

class CCLock::Impl
{
public:
    Impl()
    {
        CriticalSectionInit(m_pLock);
    }

    ~Impl()
    {
        CriticalSectionDestroy(m_pLock);

        if (m_pLock)
        {
            delete m_pLock;
            m_pLock = NULL;
        }
    }

    SS_LOCK_t *m_pLock;
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
        CriticalSectionLock(m_pImp->m_pLock);
    }
}

void CCLock::unlock()
{
    if (m_pImp)
    {
        CriticalSectionUnLock(m_pImp->m_pLock);
    }
}

NS_CC_END;

#endif  // CCX_SUPPORT_MULTITHREAD
